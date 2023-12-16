Links: [[Vision Concept Map]]
Tags:
___
# Binary Vision
## Thresholding
Fairly straightforward, a pixel gets marked 1 or 0 depending on if the value (ie. hue, saturation, luminance, etc or combination) found is above or below a given threshold determined through other means

## Threshold Detection Methods
While there are some cases where thresholds can be manually set, lighting conditions change affecting the effectiveness of the set threshold. Techniques have been developed to more automatically determine thresholds.
### Bimodal Histogram Analysis
In a gray scale image. We can assume the background is primarily centred around one gray-scale, and the foreground primarily another gray-scale. Then we can assume the histogram will be bimodal (ie. having two peaks). This means we can find some threshold which effectively separates the foreground and background, this is called the anti-mode. Most histograms will have many local minima and maxima, so finding the anti-mode can be difficult. There are a few potential ways to address this: smoothing to suppress noisy peaks, or using variable step size (rather than considering each element of the histogram separately).

### Optimal Thresholding
### Otsu Thresholding
## Connectivity
### Connected Component Analysis (CCA)
Two types:
- 4-adjacent, normally used for background/holes
- 8-adjacent, normally used for identifying objects


___
Created: 2023-12-11

