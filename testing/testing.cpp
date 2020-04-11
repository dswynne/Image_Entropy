// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
/* Developer Created Libraries*/
#include "testing.h"
using namespace cv;
using namespace std;


metric_ent test_single_string_entropy(string stringP, string stringQ) {
    // Computing Shanon Entropy
    double numCountsP[10], numCountsQ[10];
    char nums[10] = { '0','1','2','3','4','5','6','7','8','9' };
    int i;
    for (i = 0; i < 10; i++) {
        numCountsP[i] = count(stringP.begin(), stringP.end(), nums[i]);
        numCountsQ[i] = count(stringQ.begin(), stringQ.end(), nums[i]);
    }
    double shanonP = 0;
    double shanonQ = 0;
    double curP, curQ;
    for (i = 0; i < 10; i++) {
        curP = numCountsP[i] / double(stringP.size());
        curQ = numCountsQ[i] / double(stringQ.size());
        shanonP += (curP)*log2(curP);
        shanonQ += (curQ)*log2(curQ);
    }

    // Compuiting Metric Entropy
    metric_ent metric_ent;
    metric_ent.p = (-1) * shanonP / double(stringP.size());
    metric_ent.q = (-1) * shanonQ / double(stringQ.size());

    return metric_ent;
}

double test_single_string_entropy_new(string seed) {
    // Computing Shanon Entropy
    double numCounts[2];
    char nums[2] = { '0','1' };
    int i;
    for (i = 0; i < 2; i++) {
        numCounts[i] = count(seed.begin(), seed.end(), nums[i]);
    }
    double shanon = 0;
    double cur;
    for (i = 0; i < 2; i++) {
        cur = numCounts[i] / double(seed.size());
        shanon += (cur)*log2(cur);
    }

    // Compuiting Metric Entropy
    double metric_ent;
    metric_ent = (-1) * shanon / double(seed.size());

    return metric_ent;
}

int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
