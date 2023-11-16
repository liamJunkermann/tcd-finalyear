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
Mat ConvertToGray(const Mat& img) {
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	GaussianBlur(img_gray, img_gray, Size(13, 13), BORDER_DEFAULT);
	return img_gray;
}

void rescaleFrame(Mat& frame, double scale) {
	int width = frame.size().width * scale;
	int height = frame.size().height * scale;
	resize(frame, frame, Size(width, height), 0, 0, INTER_AREA);
}

#pragma region P1
void countourDetection() {
	// Load the image
	for (int i = 1; i <= 10; ++i) {

		string img_path = "Media/balls/Ball" + to_string(i) + ".jpg";

		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty()) {
			std::cerr << "Error: Could not read the image." << std::endl;
			continue;
		}

		// Converting to gray image to make ball stand out against background
		Mat img_gray = ConvertToGray(image);
		//imshow("grays", img_gray);

		// use adaptive thresholding to create a binary iamge
		Mat binary_img;
		threshold(img_gray, binary_img, 180, 255, THRESH_BINARY);
		//imshow("thresholds", binary_img);

		vector<vector<Point>> contours;
		findContours(binary_img, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


		vector<vector<Point>> validContours;
		double minContourArea = 100.0;
		//// below code to have minimum contour area
		//for (const auto& contour : contours) {
		//	if (contourArea(contour) > minContourArea) {
		//		validContours.push_back(contour);
		//	}
		//}

		// below code for circularity test (includes minimum contour area)
		double minCircularity = 0.7;
		for (const auto& contour : contours) {
			double area = contourArea(contour);
			double perimeter = arcLength(contour, true);
			double circularity = (4 * 3.1416 * area) / (perimeter * perimeter);

			if (area > minContourArea && circularity > minCircularity) {
				validContours.push_back(contour);
			}
		}

		Mat res = image.clone();
		drawContours(res, validContours, -1, Scalar(0, 255, 0), 2);

		imshow("result Balls" + to_string(i), res);

		int keyPressed = waitKey(0);

		destroyWindow("result Balls" + to_string(i));
		//destroyWindow("thresholds");
		//destroyWindow("grays");

		if (keyPressed == 27) {
			break;
		}
	}
	destroyAllWindows();

}

void houghDetection() {
	// Load the image
	for (int i = 1; i <= 10; ++i) {

		string img_path = "Media/balls/Ball" + to_string(i) + ".jpg";

		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty()) {
			std::cerr << "Error: Could not read the image." << std::endl;
			return;
		}

		// Converting to gray image to make ball stand out against background
		Mat img_gray = ConvertToGray(image);

		// Using HoughCircles to detect circles.
		vector<Vec3f> circles;
		HoughCircles(img_gray,
			circles,         // vector to store circle parameters (x, y, radius)
			HOUGH_GRADIENT,  // method (currently, the only one implemented in OpenCV)
			1,               // inverse ratio of the accumulator resolution to the image resolution
			20,              // minimum distance between the centers of detected circles
			50,             // Canny edge detection threshold
			30,              // accumulator threshold for circle detection (lower values for more circles)
			15,               // minimum radius
			80                // maximum radius (0 means unlimited)
		);
		if (!circles.empty()) {
			for (size_t j = 0; j < circles.size(); ++j) {
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

		if (keyPressed == 27) {
			break;
		}

	}
	destroyAllWindows();

}
#pragma endregion P1

#pragma region P2

void tableSobel() {
	for (int i = 1; i <= 5; ++i) {
		string img_path = "Media/tables/Table" + to_string(i) + ".jpg";
		Mat image = imread(img_path);

		// Check if the image is loaded successfully
		if (image.empty()) {
			cerr << "Error: Could not read the image." << endl;
			continue;
		}

		// Convert the image to grayscale
		Mat gray = ConvertToGray(image);

		// Use the Sobel operator for edge detection
		Mat gradX, gradY;
		Sobel(gray, gradX, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);
		Sobel(gray, gradY, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);

		imshow("grayx", gradX);
		waitKey(0);

		// Convert the gradient images back to CV_8U
		Mat absGradX, absGradY;
		convertScaleAbs(gradX, absGradX);
		convertScaleAbs(gradY, absGradY);

		// Combine the gradients to get the final edge-detected image
		Mat edges;
		addWeighted(absGradX, 0.5, absGradY, 0.5, 0, edges);

		// Find contours in the binary edge image
		vector<vector<Point>> contours;
		findContours(edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		// Find the contour with the largest area (assuming it's the table)
		double maxArea = 0;
		int maxAreaContourIndex = -1;
		for (int i = 0; i < contours.size(); ++i) {
			double area = contourArea(contours[i]);
			if (area > maxArea) {
				maxArea = area;
				maxAreaContourIndex = i;
			}
		}

		// Get the four corners of the table
		if (maxAreaContourIndex != -1) {
			vector<Point> tableCorners;
			approxPolyDP(contours[maxAreaContourIndex], tableCorners, 0.04 * arcLength(contours[maxAreaContourIndex], true), true);

			if (tableCorners.size() == 4) {
				// Define the target corners for perspective transformation
				vector<Point2f> targetCorners = { Point2f(0, 0), Point2f(800, 0), Point2f(800, 1200), Point2f(0, 1200) };

				// Compute the perspective transformation matrix
				Mat perspectiveMatrix = getPerspectiveTransform(tableCorners, targetCorners);

				// Apply the perspective transformation
				Mat transformedImage;
				warpPerspective(image, transformedImage, perspectiveMatrix, Size(800, 1200));

				// Display the result
				imshow("Original Image", image);
				imshow("Transformed Image", transformedImage);
				waitKey(0);
				destroyAllWindows();
			}
			else {
				cerr << "Error: Unable to find four corners of the table." << endl;
				continue;
			}
		}
		else {
			cerr << "Error: Unable to find the contour of the table." << endl;
			continue;
		}

		continue;
	}
}

void tableDetect2() {
	char* file_location1 = "Media/tables/";
	char* image_files1[] = {
		"Table1.jpg",
		"Table2.jpg",
		"Table3.jpg",
		"Table4.jpg",
		"Table5.jpg",
	};

	int number_of_images1 = sizeof(image_files1) / sizeof(image_files1[0]);
	Mat* image1 = new Mat[number_of_images1];
	for (int file_no = 0; (file_no < number_of_images1); file_no++) {
		string filename(file_location1);
		filename.append(image_files1[file_no]);
		image1[file_no] = imread(filename, -1);
		if (image1[file_no].empty()) {
			cout << "Could not open " << image1[file_no] << endl;
			return;
		}
	}

	for (int i = 0; i < number_of_images1; i++) {
		Mat current_image = image1[i].clone();
		if (current_image.empty()) {
			std::cout << "Could not open or find the image!" << std::endl;
			return;
		}
		Mat hsv;
		cvtColor(current_image, hsv, COLOR_BGR2HSV);
		vector<Mat> hsvChannels;
		split(hsv, hsvChannels);
		Mat v = hsvChannels[2]; // V channel
		Mat sat = hsvChannels[1]; // S channel

		// Apply Histogram Equalization to the V channel
		equalizeHist(v, v);

		// Use multiple iterations of CLAHE on the V channel
		Ptr<CLAHE> clahe = createCLAHE();
		clahe->setClipLimit(3);
		clahe->setTilesGridSize(Size(1, 1));

		int numIterations = 5;
		for (int j = 0; j < numIterations; ++j) {
			clahe->apply(v, v);
		}

		// Adjust the saturation
		float saturationMultiplier = 2.2;
		for (int y = 0; y < sat.rows; y++) {
			for (int x = 0; x < sat.cols; x++) {
				int newVal = sat.at<uchar>(y, x) * saturationMultiplier;
				sat.at<uchar>(y, x) = (newVal > 255) ? 255 : newVal;
			}
		}

		// Merge channels back into the HSV image
		hsvChannels[1] = sat;
		hsvChannels[2] = v;
		merge(hsvChannels, hsv);

		// Define the range for blue color in HSV
		Scalar lower_blue = Scalar(90, 50, 35);
		Scalar upper_blue = Scalar(170, 255, 255);

		// Threshold the HSV image to get only blue colors
		Mat blueMask;
		inRange(hsv, lower_blue, upper_blue, blueMask);

		// Dilate the blueMask
		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
		dilate(blueMask, blueMask, kernel, Point(-1, -1), 1);

		// Apply the blue color mask
		Mat blueFiltered;
		current_image.copyTo(blueFiltered, blueMask);

		// Find contours
		vector<vector<Point>> contours;
		findContours(blueMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		// Iterate through each contour
		for (size_t j = 0; j < contours.size(); j++) {
			vector<Point> contour_poly;
			approxPolyDP(contours[j], contour_poly, 3, true);

			// Check if the polygon is a quadrilateral
			if (contour_poly.size() == 4) {
				for (size_t k = 0; k < 4; k++) {
					circle(current_image, contour_poly[k], 5, Scalar(0, 255, 0), -1);
				}
			}
		}

		// Rescale the images for display
		rescaleFrame(current_image, 0.15);
		rescaleFrame(blueFiltered, 0.15);

		// Display the images
		imshow("Original Image", current_image);
		imshow("Blue Color Filtered Image", blueFiltered);

		// Wait for a key press
		waitKey(0);
		destroyAllWindows();
	}

	// Make sure to delete the dynamically allocated array
	delete[] image1;
}

#pragma endregion P2

#pragma region P3

void videoDetect() {
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

	while (true) {
		bool ret = cap.read(frame);
		if (!ret) break;

		currentFrame++;
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		//imshow("hsv", hsv);
		inRange(hsv, lowerBound, upperBound, mask);
		//imshow("mask1", mask);

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		//imshow("gray", gray);


		if (!prevGray.empty()) {
			absdiff(gray, prevGray, diffGray);
			//imshow("diffgray", diffGray);
			threshold(diffGray, diffGray, 10, 255, THRESH_BINARY);
			//imshow("diffGrayThresh", diffGray);
			bitwise_and(mask, diffGray, mask);
			//imshow("mask2", mask);
		}

		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		ballPositions.clear();

		for (const auto& contour : contours) {
			double area = contourArea(contour);
			if (area > 30) {
				Moments M = moments(contour);
				if (M.m00 != 0) {
					Point mc(int(M.m10 / M.m00), int(M.m01 / M.m00));
					ballPositions.push_back(mc);
				}
			}
		}

		if (ballPositions.empty()) {
			framesWithoutBall++;
			if (framesWithoutBall > 10) {
				cout << "Frame " << currentFrame << ": The ball is out of bounds!" << endl;
				framesWithoutBall = 0;
				bounceStartFrame = -1;
				ballLeftHit = ballRightHit = false;
			}
		}
		else {
			framesWithoutBall = 0;
			Point currentPos = ballPositions.back();

			// Define the rectangle coordinates for the net detection
			Rect netRectangle(470, 370, 20, 135);
			rectangle(frame, netRectangle, Scalar(0, 0, 255), 2);

			int padding = 5;
			if (currentPos.y >= netRectangle.y - padding &&
				currentPos.y <= netRectangle.y + netRectangle.height + padding &&
				currentPos.x >= netRectangle.x - padding &&
				currentPos.x <= netRectangle.x + netRectangle.width + padding) {
				cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit the net!" << endl;
			}

			if (prevPos != Point()) {
				if (currentPos.y > prevPos.y) {
					bounceStartFrame = currentFrame; // Record the frame where the ball starts going down
				}
				else if (bounceStartFrame > 0 && currentPos.y < prevPos.y) {
					// If the ball was going down and is now going up, a bounce has occurred
					cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): The ball has bounced!" << endl;
					bounceStartFrame = 0; // Reset the bounceStartFrame
				}

				// Detecting ball hit by the players
				if (currentPos.x < prevPos.x) {
					if (ballLeftHit) {
						cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit by player 2!" << endl;
						ballLeftHit = false;
					}
				}
				else {
					ballLeftHit = true;
				}

				if (currentPos.x > prevPos.x) {
					if (ballRightHit) {
						cout << "Frame " << currentFrame << " (" << currentPos.y << ", " << currentPos.x << "): Ball hit by player 1!" << endl;
						ballRightHit = false;
					}
				}
				else {
					ballRightHit = true;
				}
			}

			prevPos = currentPos;
		}

		for (const auto& position : ballPositions) {
			circle(frame, position, 10, Scalar(0, 255, 0), 2);
		}

		imshow("Table Tennis Video", frame);

		if (waitKey(static_cast<int>(1000 / fps)) == 27) {
			break;
		}

		prevGray = gray.clone();
	}

	cap.release();
}

#pragma endregion P3

int main() {
	int choice;
	cout << "Enter which part you would like to test, 1, 2 or 3: ";
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "select contour (1) or hough (2): ";
		cin >> choice;
		switch (choice) {
		case 1:
			countourDetection();
			break;
		case 2:
			houghDetection();
			break;
		}
		break;
	case 2:
		//cout << "Table Detection. WIP";
		cout << "select v1 or v2: ";
		cin >> choice;
		switch (choice) {
		case 1:
			tableSobel();
			break;
		case 2:
			tableDetect2();
			break;
		}
		//tableCanny();
		break;
	case 3:
		videoDetect();
		break;
	}
	//countourDetection();
	////houghDetection();
	return 0;
}