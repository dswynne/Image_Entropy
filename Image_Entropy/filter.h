#pragma once
// OpenCV
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


cv::Mat applyFilter_GS(cv::Mat input);
std::vector<std::vector<int>>  applyFilter_BGR(cv::Mat I);
std::vector<std::vector<int>> channel_blender(std::array<cv::Mat, 3> filteredI);