Links: [[Vision Concept Map]]
Tags:
___
# Video
## Background Models
### Static Background image
Comparing each frame with a pre-selected static background image
### Running Average
In an attempt to handle background changes (assume changing light in CCTV) a running average can be used where the last $k$ frames are averaged to provide a more adaptive background to find more current changes (ie. attempting to ignore changes in lighting but still capturing a car travelling across the scene), the learning rate can be adjusted to more accurately identify movement.

### Median Background Image
Determining the median value across frames of each pixel. Of the last $m$ frames, rotating these frames as each new frame comes in, find the median histogram value of each pixel in the scene. 

### Running Gaussian Average
Images can change frame to frame due to how the image is digitised, slight changes in lighting, real world noise, etc. Can use selectivity to avoid updating foreground items, and only updating the background. Running Gaussian average can be used to address much of the real-world noise.

### Gaussian Mixture Model
Above techniques cannot handle background objects moving slightly (eg. water rippling, trees moving in the wind, etc). This technique attempts to handle that by trying to fit multiple Gaussian distributions to the historical pixel data for each point -- including both foreground and background values. At any frame ($n$), each Gaussian distribution ($m$) has a weighting ($\pi_n(i,j,m)$) depending on how frequently it has occurred in the past frames. 
When a new frame is considered, each point $f_n(i,j)$ is compared to the Gaussian distributions currently modelling that point in order to determine a single close Gaussian (if any). A distribution is considered close if it is within 2.5 $\times$ standard distribution ($\sigma$) from the average value. If there is not Gaussian distribution close enough then a new Gaussian is initialised to model the point. If there is a distribution close enough, then the distribution is updated. For each point $f_n(i,j)$ the largest Gaussian distribution which sum to at least a set threshold (eg. 70%) are considered to represent the background. 

___
Created: 2023-12-12

