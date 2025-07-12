Injury Prediction In Competitive Runners With Machine Learning - Datasets

This work encompasses two datasets uploaded to Dataverse:

1. day_approach_maskedID_timeseries.csv, corresponding to the day approach
2. week_approach_maskedID_timeseries.csv, corresponding to the week approach

All features are described in detail in our paper:
Lövdal, Azzopardi, den Hartigh, "Injury Prediction in Competitive Runners With Machine Learning", International journal of sports physiology and performance, 2020


The features pertaining to training load and/or recovery are expressed as a 
time series covering seven individual days for the day approach, 
and three weeks with features aggregated on a weekly level for the week approach.

####################################################################################

For the day approach the features for a specific day are the following:

nr. sessions (number of trainings completed)
total km (number of kilometers covered by running)
km Z3-4 (number of kilometers covered in intensity zones three and four,
	above the aerobic threshold but below the anaerobic)
km Z5-T1-T2 (number of kilometers covered in intensity zone five, above the
	     anaerobic threshold, or intensive track intervals 
	     (T1 for longer repetitions and T2 for shorter)
km sprinting (number of kilometers covered with sprints)
strength training (whether the day included a strength training)
hours alternative (number of hours spent on cross training)
perceived exertion (athlete's own estimation of how tired they were after 
		   completing the main session of the day. In case of of a 
		   rest day, this value will be -0.01)
perceived trainingSuccess (athlete's own estimation of how well the session went.
			   In case of of a rest day, this value will be -0.01)
perceived recovery (athlete's own estimation of how well rested they felt before
	 	    the start of the session. In case of of a 
		   rest day, this value will be -0.01)

####################################################################################

For the week approach the summarized features for a specific week are the following:

nr. sessions (total number of sessions completed)
nr. rest days (number of days without a training)
total kms (total running mileage)
max km one day (the maximum number of kilometers completed by running on a single day)
total km Z3-Z4-Z5-T1-T2 (the total number of kilometers done in Z3 or faster, corresponding to
			running above the aerobic threshold)
nr. tough sessions (effort in Z5, T1, T2, corresponding to running above the anaerobic threshold
		    and/or intensive track intervals)
nr. days with interval session (number of days that contained a session in Z3 or faster)
total km Z3-4 (number of kilometers covered in Z3-4, between the aerobic and anaerobic threshold)
max km Z3-4 one day (furthest distance ran in Z3-4 on a single day)
total km Z5-T1-T2 (total distance ran in Z5-T1-T2)
max km Z5-T1-T2 one day (furthest distance ran in Z5-T1-T2 on a single day)
total hours alternative training (total time spent on cross training)
nr. strength trainings (number of strength trainings completed)
avg exertion (the average rating in exertion based on the athlete's own perception of how
	      tough each training has been)
min exertion (the smallest rating in exertion of all trainings of the week)
max exertion (the highest rating in exertion of all trainings of the week)
avg training success (the average rating in how well each training went, according to
		      the athlete's own perception)
min training success (the smallest rating in training success of the week)
max training success (the highest rating in training success of the week)
avg recovery (the average rating in how well rested the athlete felt before each session)
min recovery (the smallest rating in how well rested the athlete felt before a session)
max recovery (the highest rating in how well rested the athlete felt before a session)

####################################################################################

The features are numbered according to how many days (or weeks) before the event 
day (injury or no injury) they occurred, starting the count from 0.
So nr. sessions indicates the number of
sessions completed the day before the event day, nr.sessions.1 the number 
of sessions completed two days before the event day, and so on.
For the week approach the suffix ".1" means the week starting two 
weeks before the injury, and the suffix ".2" the week starting three weeks before
the event day. 

Furthermore, both data sets include a binary column indicating whether 
this training setup resulted in an injury (1) or not (0). The Athlete ID 
is an indicator for different athletes, and the date column indicates the 
event day, relative to the first record in the data set.

#####################################################################################
31.1.2021/Sofie Lövdal (s.s.lovdal@gmail.com)
