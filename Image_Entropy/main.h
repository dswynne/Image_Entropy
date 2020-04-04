/* main.h: header file for project as of now */

#pragma once

struct bitstrings {
    std::vector <std::string> p, q;
};

//gen_bitstrings.cpp 
bitstrings gen_bitstrings(std::vector<int> allpix);
//mat_division.cpp
std::vector<int> mat_snake(int** intensity_mat, int rows, int cols);
//tools.cpp
