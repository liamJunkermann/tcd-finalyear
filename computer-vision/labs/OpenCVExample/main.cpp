#include <opencv2/opencv.hpp>

int main()
{
  // Read the image in grayscale
  cv::Mat image = cv::imread("Media/target_1.jpg", cv::IMREAD_GRAYSCALE);
  if (image.empty())
  {
    std::cerr << "Error reading image file." << std::endl;
    return -1;
  }

  // Apply Gaussian blurring
  cv::Mat blurred;
  cv::GaussianBlur(image, blurred, cv::Size(5, 5), 0);

  // Apply Watershed segmentation
  cv::Mat markers;
  cv::threshold(blurred, markers, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);
  cv::connectedComponents(markers, markers);
  // cv::watershed(image, markers);

  // Find contours in the segmented image
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(markers, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  // Filter contours based on area (example: keep only large contours)
  std::vector<std::vector<cv::Point>> filtered_contours;
  double threshold_area = 100.0; // Adjust as needed
  for (const auto &contour : contours)
  {
    if (cv::contourArea(contour) > threshold_area)
    {
      filtered_contours.push_back(contour);

      // Extract bounding boxes or centroids of filtered contours
      cv::Rect bounding_box = cv::boundingRect(contour);
      int centroid_x = bounding_box.x + bounding_box.width / 2;
      int centroid_y = bounding_box.y + bounding_box.height / 2;
      std::cout << "Target location: (" << centroid_x << ", " << centroid_y << ")\n";
    }
  }

  // Draw contours on the original image
  cv::Mat result_image = image.clone();
  cv::drawContours(result_image, filtered_contours, -1, cv::Scalar(0, 255, 0), 2);

  // Display the result with contours
  cv::imshow("Target Contours", result_image);
  cv::waitKey(0);

  return 0;
}