Links: [[CSU44053 Computer Vision Lectures]]
Tags: #LectureNote 
___
# Vision Lecture 2
> In person lecture 1
## Intro recap
- Main Course work from next week to Nov 5
Assignment 1:
- Project evaluating table tennis video
- Writeup, discuss theory behind whats been done
- Evaluation of whats been done
- 15 Page Report
Assignment 2:
- Sample exam question
Exam:
- Very application based, lectures will deal with more tutorial problems than anything

## Images Q&A
### Colour Images
- RGB is primary colour mode (inverse being CMY)
- HLS/HSV - used in vision alot
	- Hue value for White/Black/Gray (monochrome colours) doesn't matter
	- Need to be careful with maths around hue, processing colours can be confusing
		- eg. taking average of red where it can be represented by 254 and 1
	- Local averaging hue does not work
		- Might make sense to do local averaging in different colour representation
## Binary Q&A
**Ken doesn't approve of deep learning**
- Hard to know what's happening with deep learning
- Will a critical system operate well in "odd" circumstances
	- ex. Arizona woman killed bc she was pushing a bike
Vision started in industrial environments, so lighting and environment could be managed
These techniques continue to be used today
Need to know how to:
- Threshold an image
	- Go from colour to black and white image
- Creating regions
Colour image -> Convert to greyscale -> Go to binary ...

## Ethics in Computer Vision
GDPR = Thing that doesn't let you do stuff


___
Created: 2023-09-19