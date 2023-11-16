Links: [[CSU44053 Computer Vision Lectures]]
Tags: #LectureNote 
___
# Vision Lecture/Tutorial 1 (Lecture 3)
# Determine if a spoon is in a can of baby food
## Solution 1
1. RGB image
2. Take Red Channel
3. Threshold 150
4. Take % of red pixels, This can suggest number of spoons
### Issues
How do we make sure its not white
Take anything but channel
## Solution 2
1. Colour image to HSL
2. Use Hue (we want 0-30 and 235-255) + high saturation
3. Then threshold + %

## Solution 3 (The one they implemented)
1. Take greyscale image
2. Calculate average luminance
3. Luminance drops when spoon is present

# Determine if label is on bottle of glue
- Only process where top/bottom of label will be
- Sample a couple lines of the image and use standard deviation of luminance present
___
Created: 2023-09-20

