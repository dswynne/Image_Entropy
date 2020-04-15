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
bitstrings gen_bitstrings_old(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_HL(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_LSB(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_bitshift(std::vector<int> allpix);
std::string vn_extractor(std::vector<std::string> bitstrings);
std::string xor_extractor(std::vector<std::string> bitstrings);
std::string vn_extractor_recursive(std::vector<std::string> bitstrings);
//mat_division.cpp
std::vector<std::vector<int>> make_square(cv::Mat intensity_mat);
std::vector<int> mat_snake(cv::Mat intensity_mat);
std::vector<int> mat_cross(cv::Mat intensity_mat);
std::vector<int> mat_jump(cv::Mat intensity_mat);
//filter.cpp
cv::Mat applyFilter(cv::Mat input);
