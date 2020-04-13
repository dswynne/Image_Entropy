/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
/* Developer Created Libraries*/
#include "metric_ent.h"
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