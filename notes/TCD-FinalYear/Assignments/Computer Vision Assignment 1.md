---
course: csu44053
deadline: Nov 5
tags:
  - assignment
---
# Computer Vision Assignment 1
## Part 1:  Locate the table tennis ball
Using colour, regions and shape locate table tennis balls and table tennis tables in the supplied images (See [https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/balls.zip](https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/balls.zip) for the ball images with ground truth).  You can assume that the ball is either white or orange, may have some printing on it and will be spherical.  Ensure that you use techniques which can be used in general (e.g. ideally the techniques would cope with changes in lighting, etc.).  Analyse how well your approach works on the static images of the tables provided, and later on the table tennis video.  Note that in the report you may need to use some of the Learning and Evaluation section of the course, also in section 9.3 of “Computer Vision with OpenCV”  (when reporting performance).
## Part 2: Locate the table tennis table
You must now locate the corners of the table (the outside of the white lines) using edge detection, and then transform the image so that you have a plan view of the table.  Determine how well your approach works on the static images of the tables provided (See [https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/tables.zip](https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/balls.zip) for the table images with ground truth).  Ensure that you use techniques which can be used in general (e.g. ideally the techniques would cope with changes in lighting, etc.).  Analyse how well your approach works on the static images of the tables provided, and later on the table tennis video.  Note that in the report you may need to use some of the Learning and Evaluation section of the course, also in section 9.3 of “Computer Vision with OpenCV”  (when reporting performance).
## Part 3. Process the video of the table tennis game, locating the ball in each frame (if visible)
Locate all frames in which the ball changes direction.  Label each of these as (a) ball bounced on the table, (b) ball hit by player, (c) ball hit the net or (d) ball hit something else.  Determine your system accuracy on the table tennis video (See [https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/TableTennis.avi](https://www.scss.tcd.ie/Kenneth.Dawson-Howe/Vision/balls.zip)).  The ground truth is attached.

## **Each part of this assignment MUST be detailed in the final report (which can be no more than 15 pages in length).  You must detail the approach you have taken (provide theory – not code), the results achieved and give an analysis (e.g. of robustness/appropriateness/etc.).  In all parts you must illustrate your processing and results with images.  Marking will be based primarily on the report but the code may be checked to ensure consistency with what is reported.**
