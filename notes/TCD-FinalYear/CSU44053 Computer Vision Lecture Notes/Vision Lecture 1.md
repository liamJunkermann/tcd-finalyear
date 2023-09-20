Links: [[CSU44053 Computer Vision Lectures]]
Tags: #LectureNote 
___
> Images + Binary Lectures
# Images
## Camera Models and Digital Images
### Camera Models
- Lens + Sensor
- Simple Pinhole has no lens (some maths)
### Digital Images
#### Sampling
- How many samples do we need
	- Do not want wasted space/extra computation time
	- Enough resolution for objects of interest
	- OpenCV Code
	```
	Mat image, smaller_image;
	resize(image, smaller_image,
											Size(image.cols/2, image.rows/2))
	```
#### Quantisation
- Representing image points as digital values
	- Typically 8 bits
- This is what causes the "stepping" in photos of the sky
- Bit selection, similar to sampling selection
	- Wasted Space
		- 8 bits per channel does not waste loads of space, storage can be an issue
	- Fewer bits loses ability to distinguish objects
- Image quantisation code in lecture notes (slide 8 of images)
## Colour Images
Grey scale are luminance only
Colour Images (luminance + chrominance)
- Multiple channels (typically 3)
- Around 16.8 million colours
- More complex to process
- Colour also facilitates certain operations
### RGB Images
Red-Green-Blue
- Most common
- Channels correspond roughly to RGB wavelengths
- Converting to grayscale is weighted sum
### CMY Images
Cyan-Magenta-Yellow
- Secondary colours (inverse of RGB)
- Mostly used in printers
### YUV Images
- Used for analogue tv signals
- Used in PAL and NTSC
### HLS Images
Hue-Luminance-Saturation
- Separates Luminance and Chrominance

## Noise and Smoothing
Gaussian Noise
- Addition/Subtraction to values
Salt and Pepper noise
- White/Black points in scene
### Smoothing
#### Averaging filters (linear)
There are different masks
- Local Averages
- Gaussian
	- Different weightings
#### Median Filter (non-linear)
- Less affected by noise
- Doesn't blur edges as much, affects corners though

# Binary
> Binary Image processing, converted to black/white so pixels are either of interest or not of interest

Most early work in vision was done in Binary image processing, because its faster
### Binary Thresholding
- Works best for simple scenes
- Used to use Look up tables (LUT)
#### Threshold Detection
- Manual setting
	- Issues with changing lighting
- Need to determine automatically
- Open CV uses Otsu Thresholding
##### Otsu Thresholding
Minimise the spread of the pixels
- Smallest within class variance (formulas to determine average values of foreground/background)
  $\sigma_{w}^{2}(T) = w_f(T)\sigma_{2}^{f}(T)+w_b(T)\sigma_b^2(T)$
  $w_f(T)=\sum_{g=T}^{255}p(g)$
  $\sigma_f^2=\frac{\sum_{g=T}^255p(g)\cdot(g-\mu_f(T))^2}{w_f(T)}$
  $w_b(T) = \sum_{g=0}^{T-1}p(g)$
  $\sigma_b^2(T)=\frac{\sum_{g=0}^{T-1}p(g)\cdot(g-\mu_b(T))^2}{w_b(T)}$
  $\mu_f(T)=\frac{\sum_{g=T}^255p(g)\cdot g}{w_f(T)}$
  $\mu_b(T)=\frac{\sum_{g=0}^{T-1}p(g)\cdot g}{w_b(T)}$
- Largest between class variance
  $\sigma_b^2=w_f(T)w_b(T)(\mu_f(T)-\mu_b(T))^2$
- OpenCV has a function for this
##### Adaptive Thresholding
Steps for old standard method:
- Divide the image into sub-images
- Compute the threshold for each sub-image
- Interpolate thresholds for every point using bilinear interpolation
### Cleaning Binary Images
#### Dilation
- Makes 'regions bigger'
- Effectively fills small holes and joins regions
#### Erosion
- Similar maths to dilation, but removes border pixels instead of adding
- Makes 'regions smaller'
#### Opening
- Removes noise
- Roughly maintains 'region size'
- Removes narrow bridges
- Smooths shape
#### Closing
- Fills small holes
- Roughly maintains 'region' size
- Joins close 'regions'

- Opening and Closing maintain alot of the benefits of Dilation and Erosion with less effect on the image

___
Created: 2023-09-18

