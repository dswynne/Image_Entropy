#pragma once
#include <string> 

struct metric_ent {
    double p;
    double q;
};

metric_ent test_single_string_entropy(std::string stringP, std::string stringQ);
double test_single_string_entropy_new(std::string seed);
