Links: 
Tags:
___
# Histograms
## 1D Histograms
> aka. grey-scale

Histogram has information about the image completely independent from the position and orientation of the objects in the image. 
### Histogram Smoothing
Used to minimise less useful image information and highlight any local maxima/minima

### Colour Histograms
Colour histograms are normally determined for each channel independently
Different [[Colour Images#Colour Models|colour models]] have an impact on how useful the histogram is, 

## 3D Histograms
In cases where colours of objects matter, [[#1D Histograms]] won't cut it. 3D Histograms allow multiple values (eg. hue + lightness + saturation) to be considered. For example, if you wanted to find the red of a snooker ball, Saturation would be quite high, and the hue value would fall in a limited range. 3d histograms allow for better segmentation.

## Histogram/Image Equalisation
A technique to brighten a greyscale image by interspersing higher luminance pixels with darker ones

## Histogram Comparison
The degree at which a histogram between a sample and reference photo match. There are a number of metrics normally used to compare histograms.
[[Histogram Comparison Methods]]


## Back-Projection
Improved method to select colours in images.
Done by:
1. Obtaining a representative sample set of the colour(s) to be selected.
2. Create a histogram of the samples
3. Normalise the histogram so that the maximum value is 1.0 allowing values to be treated as probabilities. (ie. the probability that a pixel with the corresponding colour is from the sample set)
4. Back-Project the normalised histogram onto any image $f(i,j)$ where the similarity of the pixels in the image to those in the sample set is required, in effect providing a probability image $p()$ where $p(i,j)$ indicates the similarity between $f(i,j)$ and the sample set. (ie. $p(i,j) = h(f(i,j))$)
Back projection effectiveness relies on the number of "bins" used in the sample histogram and the colour space used. HSL tends to be more effective than RGB for example. 

## k-means Clustering
A major issue with colour images is the range of possible colours that exist. To make computations more straightforward we want to reduce this number of potential colours. Clustering is a common technique used to reduce the number of colours. 
K-means clustering is the process of searching for the number ($k$) of exemplars (ie. specific colours) to best represent all the colours in an image. The number ($k$) is determined ahead of time. The colour of each pixel is referred to as a pattern. A group of patterns associated with a particular exemplar is referred to as a cluster

### Vocab - Summarised
**Pattern**: colour of each pixel
**Exemplar**: Specific colour
**Cluster**: group of patterns associated with an exemplar

### Process
- Starting exemplars are, for example,
	- picked randomly
	- chosen as the first $k$ patterns
	- distributed evenly
- First Pass:
	- For all patterns, allocate the pattern to the nearest exemplar. Re-compute the exemplar as the centre of gravity of all patterns associated with it after each new pattern is associated with it
- Second Pass:
	- Use the final exemplars from the first pass and reallocate all patterns to the exemplars (these allocations may not be the same as the first time, however exemplars don't change)
Randomly selecting the first exemplars means that k-means is non-deterministic.
Deciding how many colours should be used to represent an image is not straight-forward


___
Created: 2023-12-11

