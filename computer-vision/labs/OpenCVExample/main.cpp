#include <opencv2/opencv.hpp>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/objdetect.hpp"
#include <string>

#define OPENCV_DISABLE_PARALLEL_FOR

using namespace std;
using namespace cv;

// Converts to Grayscale image and adds slight guassian blur to handle noise
Mat ConvertToGray(const Mat &img)
{
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_gray, Size(13, 13), BORDER_DEFAULT);
	return img_gray;
}

void rescaleFrame(Mat &frame, double scale)
{
	int width = frame.size().width * scale;
	int height = frame.size().height * scale;
	resize(frame, frame, Size(width, height), 0, 0, INTER_AREA);
}

#pragma region P1
void countourDetection()
{
	// Load the image
	for (int i = 1; i <= 10; ++i)
	{

		string img_path = "Media/balls/Ball" + to_string(i) + ".jpg";

		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty())
		{
			std::cerr << "Error: Could not read the image." << std::endl;
			continue;
		}

		// Converting to gray image to make ball stand out against background
		Mat img_gray = ConvertToGray(image);
		// imshow("grays", img_gray);

		// use adaptive thresholding to create a binary iamge
		Mat binary_img;
		threshold(img_gray, binary_img, 180, 255, THRESH_BINARY);
		// imshow("thresholds", binary_img);

		vector<vector<Point>> contours;
		findContours(binary_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		vector<vector<Point>> validContours;
		double minContourArea = 100.0;
		//// below code to have minimum contour area
		// for (const auto& contour : contours) {
		//	if (contourArea(contour) > minContourArea) {
		//		validContours.push_back(contour);
		//	}
		// }

		// below code for circularity test (includes minimum contour area)
		double minCircularity = 0.7;
		for (const auto &contour : contours)
		{
			double area = contourArea(contour);
			double perimeter = arcLength(contour, true);
			double circularity = (4 * 3.1416 * area) / (perimeter * perimeter);

			if (area > minContourArea && circularity > minCircularity)
			{
				validContours.push_back(contour);
			}
		}

		Mat res = image.clone();
		drawContours(res, validContours, -1, Scalar(0, 255, 0), 2);

		imshow("result Balls" + to_string(i), res);

		int keyPressed = waitKey(0);

		destroyWindow("result Balls" + to_string(i));
		// destroyWindow("thresholds");
		// destroyWindow("grays");

		if (keyPressed == 27)
		{
			break;
		}
	}
	destroyAllWindows();
}

void houghDetection()
{
	// Load the image
	for (int i = 1; i <= 10; ++i)
	{

		string img_path = "Media/balls/Ball" + to_string(i) + ".jpg";

		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty())
		{
			std::cerr << "Error: Could not read the image." << std::endl;
			return;
		}

		// Converting to gray image to make ball stand out against background
		Mat img_gray = ConvertToGray(image);

		// Using HoughCircles to detect circles.
		vector<Vec3f> circles;
		HoughCircles(img_gray,
					 circles,		 // vector to store circle parameters (x, y, radius)
					 HOUGH_GRADIENT, // method (currently, the only one implemented in OpenCV)
					 1,				 // inverse ratio of the accumulator resolution to the image resolution
					 20,			 // minimum distance between the centers of detected circles
					 50,			 // Canny edge detection threshold
					 30,			 // accumulator threshold for circle detection (lower values for more circles)
					 15,			 // minimum radius
					 80				 // maximum radius (0 means unlimited)
		);
		if (!circles.empty())
		{
			for (size_t j = 0; j < circles.size(); ++j)
			{
				Point center(cvRound(circles[j][0]), cvRound(circles[j][1]));
				int radius = cvRound(circles[j][2]);
				circle(image, center, radius, Scalar(0, 255, 0), 2);
				circle(image, center, 2, Scalar(0, 0, 255), 3);
				cout << "Ball" << i << " - Center: (" << center.x << ", " << center.y << "), Diameter: " << 2 * radius << endl;
			}
		}

		imshow("Result Balls" + to_string(i), image);

		int keyPressed = waitKey(0);

		destroyWindow("Result Balls" + to_string(i));

		if (keyPressed == 27)
		{
			break;
		}
	}
	destroyAllWindows();
}
#pragma endregion P1

#pragma region P2

void tableDetect()
{
	for (int i = 1; i <= 5; ++i)
	{
		string img_path = "Media/tables/Table" + to_string(i) + ".jpg";
		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty())
		{
			cerr << "Error: Could not read the image." << endl;
			continue;
		}

		// Convert the image to grayscale
		Mat gray = ConvertToGray(image);

		// Set Canny edge detection thresholds
		double lowThreshold = 50.0;
		double highThreshold = 150.0;

		// Perform Canny edge detection
		Mat edges;
		Canny(gray, edges, lowThreshold, highThreshold);

		imshow("Original Image", image);
		imshow("Canny Edge Detection", edges);

		// Display the original and edge-detected images
		// imshow("Original Image", img_path);
		// imshow("Canny Edge Detection", edges);
		waitKey(0);
	}
}

#pragma region P3

void videoDetect()
{
	VideoCapture cap("Media/TableTennis.avi");

	Mat frame, hsv, mask, gray, prevGray, diff;
	vector<vector<Point>> contours;
	vector<Point> ballPositions;
	Point prevPos;
	int framesWithoutBall = 0;
	int bounceStartFrame = -1;
	bool ballLeftHit = false, ballRightHit = false;

	double fps = cap.get(CAP_PROP_FPS);
	int currentFrame = 0;

	Scalar lowerBound(0, 100, 220); // HSV color space thresholds
	Scalar upperBound(20, 255, 255);
	Mat diffGray;

	while (true)
	{
		bool ret = cap.read(frame);
		if (!ret)
			break;

		currentFrame++;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		// imshow("hsv", hsv);
		inRange(hsv, lowerBound, upperBound, mask);
		// imshow("mask1", mask);

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		// imshow("gray", gray);

		if (!prevGray.empty())
		{
			absdiff(gray, prevGray, diffGray);
			// imshow("diffgray", diffGray);
			threshold(diffGray, diffGray, 10, 255, THRESH_BINARY);
			// imshow("diffGrayThresh", diffGray);
			bitwise_and(mask, diffGray, mask);
			// imshow("mask2", mask);
		}

		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		ballPositions.clear();

		for (const auto &contour : contours)
		{
			double area = contourArea(contour);
			if (area > 30)
			{
				Moments M = moments(contour);
				if (M.m00 != 0)
				{
					Point mc(int(M.m10 / M.m00), int(M.m01 / M.m00));
					ballPositions.push_back(mc);
				}
			}
		}

		if (ballPositions.empty())
		{
			framesWithoutBall++;
			if (framesWithoutBall > 10)
			{
				cout << "Frame " << currentFrame << ": The ball is out of bounds!" << endl;
				framesWithoutBall = 0;
				bounceStartFrame = -1;
				ballLeftHit = ballRightHit = false;
			}
		}
		else
		{
			framesWithoutBall = 0;
			Point currentPos = ballPositions.back();

			// Define the rectangle coordinates for the net detection
			Rect netRectangle(470, 370, 20, 135);
			rectangle(frame, netRectangle, Scalar(0, 0, 255), 2);

			int padding = 5;
			if (currentPos.y >= netRectangle.y - padding &&
				currentPos.y <= netRectangle.y + netRectangle.height + padding &&
				currentPos.x >= netRectangle.x - padding &&
				currentPos.x <= netRectangle.x + netRectangle.width + padding)
			{
				cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit the net!" << endl;
			}

			if (prevPos != Point())
			{
				if (currentPos.y > prevPos.y)
				{
					bounceStartFrame = currentFrame; // Record the frame where the ball starts going down
				}
				else if (bounceStartFrame > 0 && currentPos.y < prevPos.y)
				{
					// If the ball was going down and is now going up, a bounce has occurred
					cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): The ball has bounced!" << endl;
					bounceStartFrame = 0; // Reset the bounceStartFrame
				}

				// Detecting ball hit by the players
				if (currentPos.x < prevPos.x)
				{
					if (ballLeftHit)
					{
						cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit by player 2!" << endl;
						ballLeftHit = false;
					}
				}
				else
				{
					ballLeftHit = true;
				}

				if (currentPos.x > prevPos.x)
				{
					if (ballRightHit)
					{
						cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit by player 1!" << endl;
						ballRightHit = false;
					}
				}
				else
				{
					ballRightHit = true;
				}
			}

			prevPos = currentPos;
		}

		for (const auto &position : ballPositions)
		{
			circle(frame, position, 10, Scalar(0, 255, 0), 2);
		}

		imshow("Table Tennis Video", frame);

		if (waitKey(static_cast<int>(1000 / fps)) == 27)
		{
			break;
		}

		prevGray = gray.clone();
	}

	cap.release();
}

#pragma endregion P3

int main()
{
	int choice;
	cout << "Enter which part you would like to test, 1, 2 or 3: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		cout << "select contour (1) or hough (2): ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			countourDetection();
			break;
		case 2:
			houghDetection();
			break;
		}
		break;
	case 2:
		tableDetect();
		break;
	case 3:
		videoDetect();
		break;
	}
	// countourDetection();
	////houghDetection();
	return 0;
}