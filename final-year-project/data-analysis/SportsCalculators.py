def calcHrRatio(exercise_hr, max_hr=195, rest_hr=42) -> float:
    return (exercise_hr - rest_hr) / (max_hr - rest_hr)


def trimpMultiplier(exercise_hr=0, rpe=0) -> float:
    if exercise_hr != 0:
        return calcHrRatio(exercise_hr)
    elif rpe > 0:
        return rpe
    else:
        return 0.0


class ZoneClassifier:
    maxHr = 195
    restHr = 45

    def __init__(self, maxHr=195, restHr=45) -> None:
        if not maxHr:
            self.maxHr = maxHr
        if not restHr:
            self.restHr = restHr
        return

    def getZone(self, exercise_hr) -> int:
        hr_ratio = calcHrRatio(exercise_hr, self.maxHr, self.restHr)
        if hr_ratio < 0.6:
            return 1
        elif hr_ratio < 0.7:
            return 2
        elif hr_ratio < 0.8:
            return 3
        elif hr_ratio < 0.9:
            return 4
        else:
            return 5

    def calculateZoneTime(self, exercise_hr, zone, duration) -> float:
        calcZone = self.getZone(exercise_hr)
        if calcZone == zone:
            return duration
