# imports
import os
import pandas as pd
import xgboost as xgb
import numpy as np
import random
import csv
import matplotlib.pyplot as plt
import sklearn.metrics as metrics
from os import path
from sklearn.model_selection import cross_val_score
from sklearn.calibration import CalibratedClassifierCV, calibration_curve
from sklearn.metrics import roc_auc_score
from numpy import interp
from sklearn.metrics import confusion_matrix

# worker functions


def getPerformanceMeasurements(y_test, y_prob, in_thresh):
    """Calculate the necessary performance measurements between the predicted y_prob values and the ground truth y_test values."""
    """These are based either on the default threshold value of 0.5 or on the given threshold in_thresh"""
    if in_thresh == -1:
        cm = confusion_matrix(y_test, y_prob >= 0.5)
    else:
        cm = confusion_matrix(y_test, y_prob >= in_thresh)

    TP = cm[1][1]
    FN = cm[1][0]
    FP = cm[0][1]
    TN = cm[0][0]

    if (TP + FP) == 0 or (TP + FN) == 0 or ((TN + FP) == 0) or (TN + FN) == 0:
        PR = 0
        mcc = 0
    else:
        PR = TP / (TP + FP)
        mcc = ((TP * TN) - (FP * FN)) / \
            (np.sqrt((TP + FP) * (TP + FN) * (TN + FP) * (TN + FN)))

    RE = TP / (TP + FN)
    SP = TN / (TN + FP)
    acc = (TP + TN) / (TP + FP + FN + TN)
    F05 = getFScore(0.5, PR, RE)
    F1 = getFScore(1, PR, RE)
    F2 = getFScore(2, PR, RE)

    return PR, RE, SP, F1, F2, acc, mcc, cm, TP, FP, TN, FN


def normalize2(row, mean_df, std_df, athlete_id):
    """Perform z-score normalization for a given athlete id"""
    mu = mean_df.loc[athlete_id]
    su = std_df.loc[athlete_id]
    z = (row - mu)/su
    return z


def getMeanStd(data):
    """Calculate the means and standard deviations of all healthy events per athlete"""
    mean = data[data['injury'] == 0].groupby('Athlete ID').mean()
    std = data[data['injury'] == 0].groupby('Athlete ID').std()
    std.replace(to_replace=0.0, value=0.01, inplace=True)
    return mean, std


def getFScore(beta, PR, RE):
    """Calculate the F-score for a given beta value"""

    if PR == 0 and RE == 0:
        return 0
    else:
        return (1+(beta*beta))*(PR*RE)/((beta*beta*PR) + RE)


def getStats(y_test, y_pred, y_prob, in_thresh, show):
    """Calculate the required statistical results"""
    auc = roc_auc_score(y_test, y_prob)

    fpr = np.linspace(0, 1, 101)
    fpr_org, tpr_org, threshold = metrics.roc_curve(y_test, y_prob)
    tpr = interp(fpr, fpr_org, tpr_org)

    if not in_thresh:
        n_thresh = len(threshold)
        prlist = np.zeros(n_thresh)
        relist = np.zeros(n_thresh)
        acclist = np.zeros(n_thresh)
        mcclist = np.zeros(n_thresh)
        F2list = np.zeros(n_thresh)
        F1list = np.zeros(n_thresh)
        SPlist = np.zeros(n_thresh)
        for th in np.arange(n_thresh):
            prlist[th], relist[th], SPlist[th], F1list[th], F2list[th], acclist[th], mcclist[th], cm, TP, FP, TN, FN = getPerformanceMeasurements(
                y_test, y_prob, threshold[th])

        idx = np.argmin(np.abs(np.array(relist) - np.array(SPlist)))
        best_test_thresh = threshold[idx]

        PR, RE, SP, F1, F2, acc, mcc, cm, TP, FP, TN, FN = getPerformanceMeasurements(
            y_test, y_prob, best_test_thresh)
        stats = {"thresh": best_test_thresh, "auc": auc,
                 "fpr": fpr, "tpr": tpr, "cm": cm}
    else:
        PR, RE, SP, F1, F2, acc, mcc, cm, TP, FP, TN, FN = getPerformanceMeasurements(
            y_test, y_prob, in_thresh)
        stats = {"thresh": in_thresh, "auc": auc,
                 "fpr": fpr, "tpr": tpr, "cm": cm}

    return stats


def loadData(approach):
    # Load the data set
    if (approach == "day"):
        df = pd.read_csv("day_approach_maskedID_timeseries.csv")
    elif (approach == "week"):
        df = pd.read_csv("week_approach_maskedID_timeseries.csv")
    return df


def trainModel(params, dftrain, X_val, mean, std, calibrate):
    """Train an XGBoost model with the given dftrain data and calibrate it with the given X_val data"""
    y_train = np.array(dftrain['injury']).astype(int)
    y_val = np.array(X_val['injury']).astype(int)

    data_train = dftrain.drop(columns=['injury', 'Date'])
    data_val = X_val.drop(columns=['injury', 'Date'])

    # Apply normalization to training set
    data_train = data_train.apply(lambda x: normalize2(
        x, mean, std, x['Athlete ID']), axis=1)
    data_val = data_val.apply(lambda x: normalize2(
        x, mean, std, x['Athlete ID']), axis=1)

    X_train = data_train.drop(
        columns=['injury', 'Date', 'Athlete ID'], errors='ignore').to_numpy()
    X_val = data_val.drop(
        columns=['injury', 'Date', 'Athlete ID'], errors='ignore').to_numpy()

    model = xgb.XGBClassifier(objective='binary:logistic', learning_rate=0.01,
                              max_depth=random.choice(
                                  params["XGBDepthList"]),
                              n_estimators=random.choice(
                                  params["XGBEstimatorsList"]),
                              importance_type='total_gain', eval_metric='auc', verbosity=1)
    model.fit(X_train, y_train)

    calib_model = CalibratedClassifierCV(
        model, method=calibrate, cv="prefit")
    calib_model.fit(X_val, y_val)

    return model, calib_model, X_val, y_val


def getBalancedSubset(X_train, samplesPerClass):
    """Sample with replacement a balanced subset from the training data"""
    healthySet = pd.DataFrame
    injuredSet = pd.DataFrame

    # determine which athletes have injured and uninjured events
    stats = pd.DataFrame(X_train[['Athlete ID', 'injury']].groupby(
        ['Athlete ID', 'injury']).size().reset_index(name='counts'))  # group by athletes and injury/non-injury, and count of each
    stats = pd.DataFrame(stats[['Athlete ID']].groupby(
        ['Athlete ID']).size().reset_index(name='counts'))  # type: ignore # group by number athletes (and get size ie. are there injured and uninjured events )
    stats.drop(stats[stats['counts'] < 2].index, inplace=True)
    athleteList = stats['Athlete ID'].unique()

    samplesPerAthlete = int(
        np.floor(samplesPerClass) / len(athleteList))

    for athlete in athleteList:
        if injuredSet.empty:
            injuredSet = X_train[(X_train['Athlete ID'] == athlete) & (
                X_train['injury'] == 0
            )].sample(samplesPerAthlete, replace=True)
        else:
            dataToAdd = X_train[(X_train['Athlete ID'] == athlete) & (
                X_train['injury'] == 0
            )].sample(samplesPerAthlete, replace=True)
            injuredSet = pd.concat(
                [injuredSet, dataToAdd])  # type: ignore

        if healthySet.empty:
            healthySet = X_train[(X_train['Athlete ID'] == athlete) & (
                X_train['injury'] == 1
            )].sample(samplesPerAthlete, replace=True)
        else:
            dataToAdd = X_train[(X_train['Athlete ID'] == athlete) & (
                X_train['injury'] == 1
            )].sample(samplesPerAthlete, replace=True)
            healthySet = pd.concat(
                [healthySet, dataToAdd])  # type: ignore

    balancedSet = pd.concat(
        [healthySet, injuredSet])  # type: ignore
    return balancedSet


def applyBagging(modelList, X_test, X_test_means, X_test_std, best_train_thresh, train_auc_list, filename):
    """Apply the bagging approach to new test data"""

    # Test the model on the test set
    y_predList = pd.DataFrame()
    y_probList = pd.DataFrame()
    fprList = pd.DataFrame()
    tprList = pd.DataFrame()
    auc_test_list = []

    y_test = np.array(X_test['injury']).astype(int)
    X_test = X_test.drop(columns=['injury', 'Date'])
    X_test = X_test.apply(lambda x: normalize2(
        x, X_test_means, X_test_std, x['Athlete ID']), axis=1)
    X_test = X_test.drop(
        columns=['injury', 'Date', 'Athlete ID'], errors='ignore').to_numpy()

    for idx, model in enumerate(modelList):
        y_pred, y_prob = predictValues(
            X_test, model)

        indices = np.where(
            np.array(y_pred) != None)
        y_test = np.array(y_test)[
            indices].astype(int)
        y_pred = np.array(y_pred)[
            indices].astype(int)
        y_prob = np.array(y_prob)[indices]
        y_predList['bag %d' % (idx+1)] = y_pred
        y_probList['bag %d' % (idx+1)] = y_prob

        stats = getStats(
            y_test, y_pred, y_prob, 0.5, False)
        fprList['bag %d' %
                (idx + 1)] = stats["fpr"]
        tprList['bag %d' %
                (idx + 1)] = stats["tpr"]
        auc_test_list.append(stats["auc"])

    y_prob = y_probList.mean(axis=1)
    y_pred = y_predList.mode(axis=1)

    plotCalibrationCurve(
        y_test, y_prob, filename)

    val_stats = getStats(np.array(y_test).astype(int), np.array(
        y_pred).astype(int), np.array(y_prob), best_train_thresh, True)
    return val_stats["thresh"], val_stats["auc"], fprList.mean(axis=1), tprList.mean(axis=1), val_stats["cm"]


def plotCalibrationCurve(y_test, y_pred, filename):
    """Plot a calibration with the given y_test and y_pred values"""

    fig = plt.figure(1, figsize=(10, 10))
    fraction_of_positives, mean_predicted_value = calibration_curve(
        y_test, y_pred, n_bins=10, strategy='quantile')

    plt.plot(mean_predicted_value, fraction_of_positives, "s-", label="XGBoost")
    plt.plot([0, 1], [0, 1], ls="--", c="0.3")
    plt.ylabel("Fraction of Positives")
    plt.xlabel("Predicted Probability")
    plt.ylim([-0.05, 1.05])
    plt.xlim([-0.05, 1.05])
    plt.legend(loc="lower right")
    plt.title('Calibration plots  (reliability curve)')
    plt.savefig(filename)
    plt.close()


def getVariablesForPrint(val_cm, test_cm):
    """Organize data in a structure that can be written to a csv file"""
    test_TP = test_cm[1][1]
    test_FN = test_cm[1][0]
    test_FP = test_cm[0][1]
    test_TN = test_cm[0][0]
    val_TP = val_cm[1][1]
    val_FN = val_cm[1][0]
    val_FP = val_cm[0][1]
    val_TN = val_cm[0][0]

    val_RE = val_TP / (val_TP + val_FN)
    test_RE = test_TP / (test_TP + test_FN)
    val_SP = val_TN / (val_TN + val_FP)
    test_SP = test_TN / (test_TN + test_FP)

    results = {"val_RE": val_RE,
               "val_SP": val_SP,
               "val_TP": val_TP,
               "val_FP": val_FP,
               "val_TN": val_TN,
               "val_FN": val_FN,
               "test_RE": test_RE,
               "test_SP": test_SP,
               "test_TP": test_TP,
               "test_FP": test_FP,
               "test_TN": test_TN,
               "test_FN": test_FN
               }
    return results


def predictValues(data_test, model):
    """Apply the given model to data_test"""
    y_pred = model.predict(data_test)
    y_prob = model.predict_proba(data_test)

    return y_pred, y_prob[:, 1]


def runExperiment(params, approach, exp):
    """Run experiment with given a parameters and approach (day or week)"""

    outdir = "%s_%d" % (approach, params["samplesPerClass"])

    # Load data set in a data frame
    df = loadData(approach)

    # Sort athletes with ID
    athletes = sorted(list(df['Athlete ID'].unique()))

    #  Choose the last N athletes that joined the club and keep them as the test set
    test_athletes = athletes[len(
        athletes) - params["nTestAthletes"]:len(athletes)]
    X_test = df[df['Athlete ID'].isin(test_athletes)]
    X_test_means, X_test_std = getMeanStd(X_test)

    # Set the training data to be the vectors of all other athletes
    X_trainval = df[~df['Athlete ID'].isin(test_athletes)]
    X_train_means, X_train_std = getMeanStd(X_trainval)

    X_trainval_org = X_trainval
    modelList = []
    featureRanking = pd.DataFrame()
    aucList = np.zeros(params["nbags"])
    best_train_thresh = np.zeros(params["nbags"])

    # Run a bagging approach
    X_valorg = getBalancedSubset(X_trainval_org, params["samplesPerClass"])
    y_val_probList = pd.DataFrame()

    for bag in np.arange(params["nbags"]):
        # print('bagging ', bag)
        X_train_bag = getBalancedSubset(
            X_trainval_org, params["samplesPerClass"])

        model, calib_model, X_val, y_val = trainModel(
            params, X_train_bag, X_valorg, X_train_means, X_train_std, params["calibrationType"])
        modelList.append(calib_model)

        y_val_prob = calib_model.predict_proba(X_val)
        plotCalibrationCurve(
            y_val, y_val_prob[:, 1], './%s/calibrate_%d_%d.png' % (outdir, exp, bag))
        y_val_probList["Bag %d" % bag] = y_val_prob[:, 1]
        featureRanking["Bag %d" % bag] = model.feature_importances_

    plotCalibrationCurve(y_val, y_val_probList.mean(
        axis=1), './%s/calibrate_bagging_%d.png' % (outdir, exp))
    y_prediction = y_val_probList.mean(axis=1)

    outValBaggingFilename = "./%s/valbagging.csv" % (outdir)
    if path.exists(outValBaggingFilename):
        with open(outValBaggingFilename, 'a', newline='') as file:
            writer = csv.writer(file)
            for idx in np.arange(0, len(y_val)):
                writer.writerow(['%s' % (outdir), '%d' %
                                (exp), y_val[idx], y_prediction[idx]])
    else:
        with open(outValBaggingFilename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["Desc", "Exp", "Y_Val", "Y_Pred"])
            for idx in np.arange(0, len(y_val)):
                writer.writerow(['%s' % (outdir), '%d' %
                                (exp), y_val[idx], y_prediction[idx]])

    # print("****** Training Results ****")
    # Remove Athletes from the training set who do not have injured and healthy events
    X_trainval_org = X_trainval_org.drop(X_trainval_org[~X_trainval_org['Athlete ID'].isin(
        X_train_bag['Athlete ID'].unique())].index, inplace=False)

    valSamples = X_trainval_org[X_trainval_org['injury'] == 0].sample(
        len(X_test[X_test['injury'] == 0]))

    valSamples = pd.concat([valSamples, X_trainval_org[X_trainval_org['injury'] == 1].sample(
        len(X_test[X_test['injury'] == 1]))])

    val_thresh, val_auc, val_fpr, val_tpr, val_cm = applyBagging(modelList, valSamples, X_train_means, X_train_std, [
    ], aucList, './%s/calibrate_validation_%d.pdf' % (outdir, exp))

    print("****** Test Results ****")
    test_thresh, test_auc, test_fpr, test_tpr, test_cm = applyBagging(
        modelList, X_test, X_test_means, X_test_std, val_thresh, aucList, './%s/calibrate_test_%d.pdf' % (outdir, exp))

    results = getVariablesForPrint(val_cm, test_cm)
    writeResults(outdir, results, params, exp, test_thresh, test_auc, val_auc)

    # Aggregate feature importance and plot them
    aggFeatureRanking = featureRanking.sum(axis=1)

    print("y_val: ", y_val)
    print("y_prediction: ", y_prediction)
    print("cm", confusion_matrix(y_val, y_prediction >= val_thresh))
    return aggFeatureRanking, X_train_bag.columns, val_fpr, val_tpr, val_auc, test_fpr, test_tpr, test_auc, y_val, y_prediction


def writeResults(outdir, results, params, exp, test_thresh, test_auc, val_auc):
    # Write results to a CSV file
    resultsFilename = "./%s/results.csv" % (outdir)
    injuries = results["val_TP"] + results["val_FN"]
    noninjuries = results["val_TN"] + results["val_FP"]

    if path.exists(resultsFilename):
        with open(resultsFilename, 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([params["nTestAthletes"], params["nbags"], exp, injuries, noninjuries, test_thresh, val_auc, results["val_RE"], results["val_SP"], results["val_TP"], results["val_FP"],
                            results["val_TN"], results["val_FN"], test_auc, results["test_RE"], results["test_SP"], results["test_TP"], results["test_FP"], results["test_TN"], results["test_FN"]])
    else:
        with open(resultsFilename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(["N", "nbags", "exp", "injuries", "non-injuries", "thresh", "Val_AUC", "Val_RE", "Val_SP", "Val_TP",
                            "Val_FP", "Val_TN", "Val_FN", "Test_AUC", "Test_RE", "Test_SP", "Test_TP", "Test_FP", "Test_TN", "Test_FN"])
            writer.writerow([params["nTestAthletes"], params["nbags"], exp, injuries, noninjuries, test_thresh, val_auc, results["val_RE"], results["val_SP"], results["val_TP"], results["val_FP"],
                            results["val_TN"], results["val_FN"], test_auc, results["test_RE"], results["test_SP"], results["test_TP"], results["test_FP"], results["test_TN"], results["test_FN"]])


def plotROC(val_fpr, val_tpr, val_auc, test_fpr, test_tpr, test_auc, filename):
    """Plot the ROC curve and save to a file"""

    linewidth = 2
    plt.figure(figsize=(20, 10))
    plt.plot(val_fpr, val_tpr, color='darkorange', lw=linewidth,
             label='Validation (AUC = %0.4f)' % val_auc)
    plt.plot(test_fpr, test_tpr, color='darkgreen',
             lw=linewidth, label='Test (AUC = %0.4f)' % test_auc)
    plt.plot([0, 1], [0, 1], color='navy', lw=linewidth, linestyle='--')
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.legend(loc="lower right")
    plt.savefig(filename)
    plt.close()


def main():
    # main

    # Initialization of the required parameters. The following are the ones used in the paper
    params = {
        # The number of the last athletese that joined the club used as the test set
        "nTestAthletes": 10,
        "nbags": 9,          # The number of XGBoost models
        "calibrationType": "sigmoid",  # The type of calibration - Platt scaling
        "nExp": 5,          # The number of experiments to run
        # The number of injury and non-injury samples taken to train each of the XGBoost models
        "samplesPerClass": 2048,
        # The two approaches (day or week) that we consider in our publication
        "approachList": ["day", "week"],
        "XGBEstimatorsList": [256, 512],
        "XGBDepthList": [2, 3]
    }

    val_fprList = pd.DataFrame()
    val_tprList = pd.DataFrame()
    test_fprList = pd.DataFrame()
    test_tprList = pd.DataFrame()
    val_auc = np.zeros(params["nExp"])
    test_auc = np.zeros(params["nExp"])

    y_val = [[0] * params["nExp"]
             for j in np.arange(0, len(params["approachList"]))]
    y_prediction = [[0] * params["nExp"]
                    for j in np.arange(0, len(params["approachList"]))]

    for approachidx, approach in enumerate(params["approachList"]):
        dirname = '%s_%d' % (approach, params["samplesPerClass"])
        if not os.path.isdir(dirname):
            os.mkdir(dirname)

        for exp in np.arange(0, params["nExp"]):
            print("Approach = %s, N = %d, nbags = %d, exp = %d" %
                  (approach, params["nTestAthletes"], params["nbags"], exp+1))
            featureRanking, featureNames, val_fpr, val_tpr, val_auc[exp], test_fpr, test_tpr, test_auc[
                exp], y_val[approachidx][exp], y_prediction[approachidx][exp] = runExperiment(params, approach, exp)
            print(val_auc)
            print(test_auc)
            if not path.exists("./%s_%d/featureranking.csv" % (approach, params["samplesPerClass"])):
                with open('./%s_%d/featureranking.csv' % (approach, params["samplesPerClass"]), 'w', newline='') as file:
                    writer = csv.writer(file)
                    writer.writerow(featureNames)

            val_fprList['exp %d' % exp] = val_fpr
            val_tprList['exp %d' % exp] = val_tpr
            test_fprList['exp %d' % exp] = test_fpr
            test_tprList['exp %d' % exp] = test_tpr

            if (exp == 0):
                aggFeatureRanking = featureRanking
            else:
                aggFeatureRanking = aggFeatureRanking.add(featureRanking)

        plotROC(val_fprList.mean(axis=1), val_tprList.mean(axis=1), np.mean(val_auc), test_fprList.mean(axis=1), test_tprList.mean(axis=1), np.mean(
            test_auc), './%s_%d/N=%d_nbags=%d_ROC.pdf' % (approach, params["samplesPerClass"], params["nTestAthletes"], params["nbags"]))

        aggFeatureRanking = aggFeatureRanking.div(aggFeatureRanking.sum())
        with open('./%s_%d/featureranking.csv' % (approach, params["samplesPerClass"]), 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(aggFeatureRanking)

        rank = np.argsort(aggFeatureRanking)
        featureNames = [col for col in featureNames if col not in (
            {'injury', 'Date', 'Athlete ID'})]
        featureNames = [featureNames[i] for i in rank]

        plt.figure(figsize=(20, 10))
        plt.barh(np.arange(20),
                 aggFeatureRanking[rank[len(rank)-20:len(rank)]])
        plt.yticks(np.arange(20), featureNames[len(
            featureNames)-20:len(featureNames)])
        plt.savefig("./%s_%d/N=%d_nbags=%d_featureranking.pdf" % (approach,
                    params["samplesPerClass"], params["nTestAthletes"], params["nbags"]))
        plt.close()

    print("Plotting the calibration curves")
    plt.figure(100, figsize=(10, 10))
    colorlist = ["darkorange", "darkgreen"]

    approachList = params["approachList"]

    for approachidx, approach in enumerate(params["approachList"]):
        fraction_of_positives_list = []
        mean_predicted_value_list = []

        for exp in np.arange(0, params["nExp"]):
            # plotCalibrationCurve(y_val[approachidx][calibrateidx][exp], y_prediction[approachidx][calibrateidx]
            #  [exp], '%s_%s_%d_calibration.pdf' % (approachList[approachidx], "sigmoid", exp))
            fraction_of_positives, mean_predicted_value = calibration_curve(
                y_val[approachidx][exp], y_prediction[approachidx][exp], n_bins=10, strategy='quantile')
            fraction_of_positives_list.append(fraction_of_positives)
            mean_predicted_value_list.append(mean_predicted_value)

        plt.plot(np.mean(mean_predicted_value_list, axis=0), np.mean(fraction_of_positives_list, axis=0), "s-",
                 color="%s" % (colorlist[approachidx]), ls="-", label="%s, %s" % (approach, params["calibrationType"]))

        plt.plot([0, 1], [0, 1], ls="-", c="0.3")
        plt.ylabel("Fraction of positives")
        plt.xlabel("Predicted Probability")
        plt.ylim([-0.05, 1.05])
        plt.xlim([-0.05, 1.05])
        plt.legend(loc="lower right")
        plt.title('Calibration plots  (reliability curve)')
    plt.savefig("calibration.pdf")
    plt.close()


if __name__ == "__main__":
    main()
