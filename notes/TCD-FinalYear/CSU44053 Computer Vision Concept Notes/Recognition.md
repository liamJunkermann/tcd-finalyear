Links: [[Vision Concept Map]]
Tags: #concept 
___
# Recognition
Recognition can be
1. distinguishing different types of objects (eg. people vs cars, cars vs bicycles)
2. recognising specific individuals
3. automatically reading the license plate of a car
4. locating specific objects to be manipulated by a robot
5. recognising a page of a book, or a specific painting, or building, etc to augment reality
6. locate eyes so that we can track them to provide advanced UIs
7. classifying objects (such as items on a production line) so that a robot may pick them up and place them in the correct location.
## Template Matching
This technique is used to try find a sub-image within an image. The sub-image is some object of interest, effectively in 2D.
This can be used in some instances but fails in quite a few conditions:
1. Poor image quality
2. not near enough matches to the template (eg. reg plate letters where only numbers provided)
Template matching is used often in stereo vision (two images taken side by side to determine the distance away an object is)
## Chamfer Matching
Template matching requires the object of interest to look almost the same (we ignore illumination) to the template provided, any distortion to the appearance of an object can have an impact on the matching score obtained.
### Chamfering Algorithm
The chamfer value for a pixel is the distance from that pixel to the nearest object (edge) point. Doing this for every pixel in a scene is computationally expensive, so a two pass operation has been developed. The first pass looks at all points from top to bottom, left to right and considers points above and to the left of the current point. The second pass does the opposite - Bottom to Top, right to left - and considers points below and to the right of the current point. 
### Chamfer Matching
Chamfer matching is normally used to compare binary edge images (or any binary image can work). The template for chamfer matching is a binary template where only the object pixels (those set to any value greater than or equal to 1) are considered. This template is compared in every possible location but the matching metric is a sum of chamfer values corresponding to the object pixels in a template.
## Statistical Pattern Recognition (SPR)
### Probability Review
#### A *priori* and a *posteriori* Probabilities
The probability $p(x|W_i)$ is the *a priori* probability that a feature value/vector $x$ will occur given that an object of class $W_i$ is viewed. We are often more interested in the *a posteriori* probability -- what is the probability that we have located an object of class $W_i$ if some feature value/vector $x$ has been observed.
#### Bayes Theorem
We can compute the *a posteriori* probabilities from the *a priori* probabilities and the relative probabilities of the individual classes (ie. how frequently each class of object occurs $p(W_i)$).
For two classes *A* and *B* the *a posteriori* probability is:
$$P(B|A) = \frac{P(A|B)P(B)}{P(A)}$$
Where there are multiple classes $W_i$, we use Bayes Theorem:
$$
p(W_i|x) = \frac{p(x|W_i)P(W_i)}{\sum_jp(x|w_j)P(W_j)}
$$
### Sample Features
SPR is based on the likelihood of occurrence of some features associated with shapes/objects. These features are frequently computed from the object shape characteristics (eg. aspect ratio), but can equally be based on the colours in the object region or measures describing the texture of the object and so on. 
- Area
- Elongatedness
- Length to width ratio for the minimum bounding rectangle
- Convex Hull Area/Minimum Bounding rectangle area ratio
- Concavities and Holes
- Rectangularity
- Moments and Moment Invariants
	- Moments measure the distribution of shape

## Cascade of Haar Classifiers
This technique for object detection learns to identify objects (like faces) based on a number of positive and negative samples. It uses simple features to decide if a sub=image contains the object in question. It selects a large number of features during training and creates classifiers with them to provide an accept/reject response. The classifiers are organised into a cascade where if the sub-image is rejected by any classifier in the cascade it is not processed any further. This creates a computational advantage where most sub-images are not processed past one or two classifiers

### Features
Features are determined by taking the difference of sums of a number of rectangular regions of a grey-scale image. Given a sub-image, the mask for one of the features is placed at some specific location, and scale. The feature value is simple the normalised sum of the pixels in the black area subtracted from the normalised sum of the pixels in the white area.
### Training
The training phase for object detection must identify which features are best to use at each stage in the classifier cascade. The system must be provided with a large number of positive and negative samples.


___
Created: 2023-12-12

