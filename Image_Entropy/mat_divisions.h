#pragma once

// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

std::vector<std::vector<int>> channel_blender(std::array<cv::Mat, 3> filteredI);
std::vector<std::vector<int>> make_square(cv::Mat intensity_mat);
std::vector<std::vector<int>> make_square_new(std::vector<std::vector<int>> intensity_mat);
std::vector<int> mat_snake(cv::Mat intensity_mat);
std::vector<int> mat_cross(cv::Mat intensity_mat);
//std::vector<int> mat_jump(cv::Mat intensity_mat);
std::vector<int> mat_jump(std::vector<std::vector<int>> intensity_mat);