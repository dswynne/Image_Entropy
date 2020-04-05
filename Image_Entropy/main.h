/* main.h: header file for project as of now */

#pragma once

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct bitstrings {
    std::vector <std::string> p, q;
};

//gen_bitstrings.cpp 
bitstrings gen_bitstrings(cv::Mat allpix);
//mat_division.cpp
cv::Mat mat_snake(cv::Mat intensity_mat, int rows, int cols);
//filter.cpp
cv::Mat applyFilter(cv::Mat input);
