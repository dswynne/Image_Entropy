#pragma once
#include <string>
#include <vector>

std::string vn_extractor(std::vector<std::string> bitstrings);
std::string xor_extractor(std::vector<std::string> bitstrings);
std::string vn_extractor_recursive(std::vector<std::string> bitstrings);
std::string extractor_blender(std::string seedVN, std::string seedXOR);