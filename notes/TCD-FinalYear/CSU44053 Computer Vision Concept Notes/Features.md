Links: [[Vision Concept Map]]
Tags: #concept 
___
# Features
Given just an edge map we can't determine the movement of edges between frames. Due to the ambiguity of matches, the mappings of matches don't transfer from one frame to the next.
Solution: Computer Vision makes use of corners, image features, or interest points (terms used interchangeably)
Use of features reduces number of points considered from frame to frame and each of these points is more complex than just an edge point. This makes it much easier to create matches between frames
Corner/feature detection is not robust/repeatable due to locations of corner points varying between frames and sometimes disappearing
### Corner detection framework
Image -> Corner Detector -> Cornerness Map
Corner detection tends to follow the same base steps:
1. **Determine cornerness values.** For each pixel in the image, compute a cornerness value based on the local pixels. **Output of this stage is a cornerness map**
   > This computation tends to differentiate corner detectors.
2. **Non-Maxima suppression.** Suppress all cornerness values which are less than a local neighbour (within $n$ pixels distance; eg. $n=3$) in order to avoid multiple responses for the same corner.
3. **Threshold the cornerness map.** Select the cornerness values which remain and are significant, this is typically done with thresholding (ie. the cornerness value must be above some threshold $T$ in order to be considered a corner).
## Moravec Corner Detection
First/simplest corner detection detectors.
Looks at the local variation around a point by comparing local images patches and computing the un-normalised local autocorrelation between them.
For each pixel, it compares a patch centered on that pixel with eight local patches which are shifted by a small amount (typically one pixel in each of the 8 possible directions) from the current patch. It compares the patches using a sum of differences and records the minimum of the 8 values as the cornerness for the pixel. 
$$
V_{u,v}(i,j) = \sum_{\forall a,b\in Window}(f(i+u+a,j+v+b)-f(i+a,j+b))^2
$$
where $(u,v)\in \{(-1,-1),(-1,0),(-1,1),(0,-1),(0,1),(1,-1),(1,0),(1,1)\}$ and the Window is typically 3x3, 5x5, or 7x7.

The Moravec corner detector has two flaws which motivated the development of other corner detectors:
1. Anisotropic (varying in magnitude according to the direction of measurement) response. Using the examples from the book. Moravec responded more strongly to the diagonal lines in the Yield sign, rather than the horizontal or vertical lines. This response can be reduced by smoothing the image before applying the the corner detector
2. Noisy Response. Moravec is very sensitive to noise (most corner detectors are). Noise can be reduced by smoothing the image or using a larger area before applying the detector.

## Harris Corner Detection
Harris corner detector changes how the cornerness value is determined. Just as mentioned in the [[#Corner detection framework|framework]], the first step changes. Rather than considering the sum of squared differences, it uses partial derivatives. This is a Gaussian weighting function and the eigenvalues of a matrix representation of the equation.
Consider the intensity variation (sum of squared differences) of an image patch $W$ for a small shift $(\Delta i, \Delta j)$: 
$$
SSD_W(\Delta{i}, \Delta{j}) = \sum_{(i,j)\in W}(f(i,j)-f(i-\Delta{i},j-\Delta{j}))^2
$$
Second term can be approximated as
$$
f(i-\Delta{i},j-\Delta{j}) \approx f(i,j) + {\Huge[}\frac{\delta{f(i,j)}}{\delta{i}}~\frac{\delta{f(i,j)}}{\delta{i}}{\Huge]}{\Huge[}{{\Delta{i}}\atop{\Delta{j}}}{\Huge]}
$$
Rewriting and simplifying results in:
$$
SSD_W(\Delta{i}, \Delta{j}) = [\Delta{i}~\Delta{j}]
{\Huge[}{
{\sum_{(i,j)\in W}(\frac{\delta{f(i,j)}}{\delta{i}})^2~\sum_{(i,j)\in W}\frac{\delta{f(i,j)}}{\delta{i}}\frac{\delta{f(i,j)}}{\delta{i}}}
\atop
{\sum_{(i,j)\in W}\frac{\delta{f(i,j)}}{\delta{i}}\frac{\delta{f(i,j)}}{\delta{i}}~\sum_{(i,j)\in W}(\frac{\delta{f(i,j)}}{\delta{i}})^2}
}{\Huge]} {\Huge[}{{\Delta{i}}\atop{\Delta{j}}}{\Huge]}
$$
Cornerness can then be computed as:
$$C(i,j) = \det(M)-k(trace(M))^2$$
where $k$ is a constant empirically determined to be in the range 0.04 to 0.06 and
$$M = {\Huge[}{
{\sum_{(i,j)\in W}(\frac{\delta{f(i,j)}}{\delta{i}})^2~\sum_{(i,j)\in W}\frac{\delta{f(i,j)}}{\delta{i}}\frac{\delta{f(i,j)}}{\delta{i}}}
\atop
{\sum_{(i,j)\in W}\frac{\delta{f(i,j)}}{\delta{i}}\frac{\delta{f(i,j)}}{\delta{i}}~\sum_{(i,j)\in W}(\frac{\delta{f(i,j)}}{\delta{i}})^2}
}{\Huge]} = {\Huge[}{{A~B}\atop{B~C}}{\Huge]} $$
$\det(M) = \lambda_1\lambda_2=AC +B^2$
$trace(M) = \lambda_1\lambda_2= A + C$
The summation over $W$ is weighted so that more weight on measurements closer to the centre of the window is given. 
Harris is significantly more expensive than Moravec. Just like Moravec it is sensitive to noise and has a somewhat anisotropic response. 
Harris is preferred due to two factors:
1. It has a very repeatable response
2. It has a better detection rate (taking into account true positives, false positives, true negatives, and false negatives) than Moravec.

## FAST Corner Detection
**FAST** (**F**eature from **A**ccelerated **S**egment **T**est) is different from [[#Moravec Corner Detection|Moravec]] and [[#Harris Corner Detection|Harris]] edge detectors because it does not compute a cornerness metric. Instead it looks at a circle of points around the current pixel being considered. (normally a radius of 3 pixels, mapping to 16 total pixels). The current pixel $p$ is a corner if there is a contiguous arc of at least 9 pixels around the circle which are all brighter or darker than the nucleus (current point or an average of the current point and its neighbours) by some predefined threshold $t$. 
The value of 9 is used to exclude edges and has been shown to give the best results. This value was originally 12. 
Because cornerness is not computed, in order to use non-maxima suppression (in order to ensure a single response per corner), corner strength is defined as the maximum of value of the threshold $t$ which classifies $p$ as a corner. 
> Find where the threshold can be highest for classifications p of a corner

FAST lives up to its name and is faster than the other detectors. When implemented Harris was 5-10x slower and SIFT was around 50 times slower.
Much like the rest of the corner detectors, FAST is very susceptible to noise. It also has a higher likelihood of detecting extra corners in high density corner images.

## SIFT
**SIFT** (**S**cale **I**nvariant **F**eature **T**ransform) was developed to provide repeatable and robust features for tracking, recognition, panorama stitching, etc. This detector is invariant to scaling and rotation and partly invariant to illumination and viewpoint changes. This shows a huge step forward when compared to typical corner detectors ([[#Moravec Corner Detection|Moravec]], [[#Harris Corner Detection|Harris]], [[#FAST Corner Detection|FAST]]).
SIFT extracts features through the following stages:
1. [[SIFT Steps#Scale Space Extrema Detection|Scale Space Extrema Detection]] (outputs keypoint locations)
2. [[SIFT Steps#Accurate Keypoint Location|Accurate Keypoint Location]] (outputs accurate/significant keypoint locations)
3. [[SIFT Steps#Keypoint Orientation Assignment|Keypoint Orientation Assignment]] (outputs orientation of keypoints)
4. [[SIFT Steps#Keypoint Descriptor|Keypoint Descriptors]]

[[SIFT Steps]]



___
Created: 2023-12-12

