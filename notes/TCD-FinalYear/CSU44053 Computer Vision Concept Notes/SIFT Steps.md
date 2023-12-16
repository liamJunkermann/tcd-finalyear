---
tags:
  - concept
  - unfinished
---
### Scale Space Extrema Detection
In order to provide features invariant to the scale of the object viewed, a number of scales are considered simultaneously and extrema are located within the scaled images. The image is convolved with a number of Gaussians $L_n(i,j,k,\sigma) = G(i,j,k^n\sigma)^\ast f(i,j)$ where $n=0,1,2,3,...$ This is done in a number of octaves of scale space, where each octave corresponds to a doubling of the standard deviation ($\sigma$). 
To find potential stable keypoint locations a Difference of Gaussian (DoG) functions across the various scale spaces (ie. $D_n(i,j,k,\sigma) = L_{n+1}(i,j,k,\sigma)-L_n(i,j,k,\sigma)$). To then find the extrema, multiple DoG images are considered and points are located which are greater (or less) than all their neighbours both in the current scale and in the neighbouring scales.

### Accurate Keypoint Location
In the original implementation, location and scale were taken from a central point. This was determined to be inaccurate so to increase precision, the data is modelled locally using a 3D quadratic and the interpolated maximum/minimum can be found. This was determined to be robust enough so two tests were introduced to select more reliable keypoints. 
The first test considers the local contrast in an area around the keypoint. It checks the curvature of the quadratic at the keypoint, if the curvature is low the point is discarded as the contrast is low.
The second test checks the localisation of the keypoint (ie. is the it on an edge rather than a distinguishable feature). A poorly defined peak in the DoG function will have a large principal curvature across the edge but a small one in the perpendicular direction. 

### Keypoint Orientation Assignment
In order to make the features rotation invariant each feature is assigned a specific (principal) orientation. The scale of the keypoint is used to select the Gaussian smoothing image, $L_n$, with the closest scale so that all computations are performed in a scale-invariant manner.
For each image sample, $L_n(i,j,k,\sigma)$, at this scale, the gradient magnitude, $\nabla f(i,j)$, and orientation, $\phi(i,j)$, is computed:
$$
\nabla{f(i,j)} = \sqrt{(L_n(i+1,j,k,\sigma)-L_n(i-1,j,k,\sigma))^2+(L_n(i,j+1,k,\sigma)-L_n(i,j-1,k,\sigma))^2}
$$
$$
\phi(i,j) = \arctan((L_n(i+1,j,k,\sigma)-L_n(i-1,j,k,\sigma))^2,(L_n(i,j+1,k,\sigma)-L_n(i,j-1,k,\sigma))^2)
$$
An orientation histogram with 36 bins, each representing 10$\degree$, is formed from the orientations of points within a region around the keypoint. Each point added to the histogram is weighted by its gradient magnitude and by a Gaussian weight defined by the distance to the keypoint location. 

### Keypoint Descriptor
The final step in extracting keypoints is describing the region around a keypoint so that it can be compared with other keypoints. Blurred images at the closest scale are used, sampling points around the keypoint and computing their gradients and orientations. The the image is rotated by the keypoint orientation (so that the orientations are normalised with respect to the keypoint orientation).
The region around the keypoint is divided into four subregions and a weighted histogram of the orientations (weighted by gradient and location) is determined for each of the subregions. 
The orientations are mapped into the relevant bins and also into all adjoining bins in order to reduce problems relating to quantisation.

### Matching Keypoints
### Recognition