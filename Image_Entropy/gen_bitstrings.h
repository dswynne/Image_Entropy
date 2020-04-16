#pragma once
#include <string>
#include <vector>
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

struct bitstrings {
    std::vector <std::string> p, q;
};

bitstrings gen_bitstrings_old(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_whole_pixel(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_HL(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_LSB(std::vector<int> allpix);
std::vector<std::string> gen_bitstrings_bitshift(std::vector<int> allpix);