#pragma once

std::vector<std::vector<int>> make_square_reshape(std::vector<std::vector<int>> intensity_mat);
std::vector<std::vector<int>> make_square_crop(std::vector<std::vector<int>> intensity_mat);
std::vector<int> mat_snake(std::vector<std::vector<int>> intensity_mat);
std::vector<int> mat_cross(std::vector<std::vector<int>> intensity_mat);
std::vector<int> mat_jump(std::vector<std::vector<int>> intensity_mat);