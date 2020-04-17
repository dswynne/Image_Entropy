#pragma once
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


cv::Mat applyFilter(cv::Mat input);
std::array<cv::Mat, 3> applyFilter_BGR(cv::Mat I);