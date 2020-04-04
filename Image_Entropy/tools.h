#pragma once
#ifndef Tools
#define Tools

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
// MPIR
#include <mpirxx.h>
/* Developer Created Libraries*/
#include "main.h"

using namespace std;

//Takes an OpenCV type and turns it into a string so it can be printed 
string type2str(int type) {
	string r;

	uchar depth = type & CV_MAT_DEPTH_MASK;
	uchar chans = 1 + (type >> CV_CN_SHIFT);

	switch (depth) {
	case CV_8U:  r = "8U"; break;
	case CV_8S:  r = "8S"; break;
	case CV_16U: r = "16U"; break;
	case CV_16S: r = "16S"; break;
	case CV_32S: r = "32S"; break;
	case CV_32F: r = "32F"; break;
	case CV_64F: r = "64F"; break;
	default:     r = "Not standard"; break;
	}

	r += "C";
	r += (chans + '0');

	return r;
}

//Prints the type of the Mat file. Used for debugging
void printMatType(cv::Mat input) {
	string imageInfo = type2str(input.type());
	cout << "\n\n" << imageInfo.c_str() << "\n\n";
}

#endif // !Tools
