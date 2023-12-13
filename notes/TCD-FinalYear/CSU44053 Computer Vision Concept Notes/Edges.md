Links: [[Vision Concept Map]]
Tags: #concept
___
# Edges
There are two main ways to address the segmentation of images:
1. Edge Processing. Identifying discontinuities (edges) in images
2. Region Processing, looking for homogenous regions of the image. Binary vision is an example of region processing
## Edge Detection
Edge detection works by detecting rates of change in brightness
Vocab:
Gradient = the change in intensity or color across an edge in an image
### First Derivative Edge Detection
Looks at rate of change.
First derivative edge detectors compute two partial derivatives, then combine them to determine gradient and orientation values for each edge point. 
#### Compass Edge Detectors
#### Computing Gradient and Orientation
First derivative edge detectors compute the **gradient** as a combination of two orthogonal partial derivatives (normally RMS).
$$
\nabla f(i,j) = \sqrt{(\frac{\delta f(i,j)}{\delta{i}})^2+(\frac{\delta f(i,j)}{\delta{i}})^2}
$$
To make this computation quicker, this can be approximated using a sum of the absolute partial derivatives
$$\nabla f(i,j) = \bigl|\frac{\delta f(i,j)}{\delta{i}}\bigr|+\bigl|\frac{\delta f(i,j)}{\delta{i}}\bigr|$$
The **orientation** of the edge is computed from two orthogonal partial derivatives using the inverse tangent function with two arguments (to allow all 360$\degree$ to be distinguished):
$$\phi(i,j)=\arctan(\frac{\delta f(i,j)}{\delta j},\frac{\delta f(i,j)}{\delta j})$$
#### Edge Image Thresholding
Simple binary thresholding applied to a gradient image. This can cause gradient response several pixels wide (ie. not precise). To address this, an additional stage is added to suppress all gradient responses outside the central maximum. This is non-maxima suppression.
#### Non-Maxima Suppression
Technique using gradient and orientation information to determine which edge points are central points. Determines, with the orientation, which points are to each side of the current edge point. It then suppresses the current point if its gradient is less than either of its two neighbours.

### Second Derivative Edge Detection
Look at rate of change of rate of change.
Laplacian second derivative filter is quite common. Centre pixel is weighted heavily, which causes issues with noise. Smoothing can help manage these issues
Better at determining where edges are with high degree of precision.
#### Laplacian of Gaussian
-  Widely used second derivative edge detector
- Images must be smoothened first. Smoothing filter must satisfy the following two criteria
	- it is smooth and band limited in the frequency domain (ie. it must limit the frequencies of edges in the image)
	- it exhibits good spatial localisation (ie. the smoothing filter must not move the edges or change their spatial relationships)
#### Canny Edge Detector
Designed to optimise the following:
1. Detection - edges should not be missed.
2. Localisation - distance between actual and located edges should be minimised.
3. One response - minimises multiple response to a single edge.
This processes a gray image. Uses a low and high threshold to manage issues where contours get disconnected with a single threshold point.
Canny works through the following steps:
1. Convolve with Gaussian with some standard deviation $\sigma$.
2. Estimate the edge normal direction (ie. orientation) using the first derivative of the Gaussian convolved image.
3. Find the edges, suppressing non-maxima values. This is done by searching for zero-crossings in the directional second derivative of the Gaussian convolved image, where those derivatives are taken with respect to the edge orientations which were computed in the previous step.
4. The edge gradient is computed based on the the first derivative of the Gaussian convolved image.
5. Thresholding edges with hysteresis. The idea here is that edge points are considered in contours of connected points. Two thresholds are used - a high gradient threshold over which all points are definitely classified as edge points and a low threshold over which points are connected to definitive edge points are considered edge points. This attempts to get over the problem of edge contours which breakup into unconnected segments, due to the use of a simple threshold.
6. 

### Contour Segmentation
This technique extracts information from the edge image (result of above edge detectors) and represents the edges more explicitly. First, need to decide which points are edges (as most points will have a non-zero gradient). This typically uses image thresholding and non-maxima suppression or the use of Canny. The edge data then needs to be extracted from the image by using graph searching, border refining, etc. Then it needs to be represented in some way (eg. [[#Boundary Chain Codes (BCCs)|Boundary Chain Code]], graphs, sequences of straight lines, etc). 
#### Boundary Chain Codes (BCCs)
A basic way to represent edge data outside the image domain.
A start point is specified, then the direction to the next point is repeatedly specified as a value from 0 to 8 (think a box around the centre point, 1 pixel away).
BCCs are orientation dependant, if orientation of object/region changes, results will change significantly. Representation can change with object scale as well. 
The boundary can be smoothed to reduce noise, but this needs to be done carefully to avoid deforming the shape.
#### Directed Graph
Another basic way to represent edge data outside the image domain
A structure consisting of nodes (which correspond to pixel edges) and oriented arcs (connections between bordering pixels/nodes).
To create this graph, all edge pixels are added to the graph as nodes, if their gradient values $s(x_i)$ are greater than some threshold $(T)$. To decide which nodes are connected by arcs, the orientation of $s(x_i)$ associated with each node $n_i$ is considered to determine which neighbouring pixel $x_j$ should be connected. 

#### Border Detection
> Graph search for edges (yay)

Border detection is either a (1) search for the optimal path between a source and destination or (2) as a search for the best representation of all edge points in the image.

For (1), there is a good amount of *priori* knowledge and hence locations of the source and destination can be at least approximately known in advance.
> An example for this is using vision to do QA on PCB boards. The locations/distances of circuits will be known ahead of time, so this can be evaluated well.

For (2), normally a general representation of all the edge contours in the scene is needed for further processing.

### Hough Transform
The Hough transformation directly maps from image space to the probability of the existence of some features (lines, circles, other generalised shapes). It is capable of detecting partial objects.
Greatest issue is speed. It is an expensive operation, to reduce the computational load, smaller lower resolution images are used to limit where the more expensive higher resolution computation will happen. 

Hough generally works by converting the image space to hough space, then using an accumulator to "vote" on likely shapes/intersections. The result of this voting is compiled to find the likely answer which is then returned and converted back into image space as a mask.

#### Hough for lines
Normally $j=mi+c$ (or more commonly $y=mx+b$) is used to represent lines. This cannot represent some lines so an alternative form is used: $s = i.\cos{(\vartheta)}+j.\sin{(\theta)}$.
To find lines in image space, image space is transformed to Hough space where the axis is $s$ and $\vartheta$. For each edge point in the binary edge image of the scene, the cells in hough space are incremented to correspond to every possible line through that edge point. 

#### Hough for Circles
Major issue for hough for circles is if the size of the circle is not known in advance. This results in needing a 2d accumulator to try determine the radius, increasing the number of computations.



___
Created: 2023-12-11

