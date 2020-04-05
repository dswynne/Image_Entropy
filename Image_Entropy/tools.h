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


void printMatArray(cv::Mat M) {
	cout << "M = " << endl << " " << M << endl << endl;
}

//Junk function used for getPQIndices()
int mathFunc(int a, int b) {
	int c = 0;
	int numCalcs = 250000;
	for (int i = 0; i < numCalcs; i++) {
		c = a * b;
		c = a + b;
	}
	return c;
}


cv::Point getPQIndices(int numPStrings, int numQStrings)
{
	//x = p index, y = q index
	cv::Point indices;

	int N = 163;
	int pIndex = 0;
	int qIndex = 0;

	//Figure out max number of bits needed
	int num = N;
	int numBits = 0;
	while (num > 0) {
		num /= 2;
		numBits++;
	}

	//Start stopwatch
	auto start = std::chrono::high_resolution_clock::now();

	//Execute a function. Put in junk code for testing
	int c = mathFunc(5, 5);

	//Stop stopwatch and display elapsed time
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;

	//Use elapsed.count() to get p and q indices. it is a double type
	// need a number between 0 and N
	double doubleValue = elapsed.count();
	uint8_t* bytePointer = (uint8_t*)&doubleValue;
	int factor = 1;

	for (size_t index = 0; index < sizeof(double); index++)
	{
		uint8_t byte = bytePointer[index];
		for (int bit = 0; bit < numBits; bit++)
		{
			if (pIndex + byte * factor > N) {
				//Reached the value just below N
				break;
			}
			else {
				pIndex += byte * factor;
				factor *= 2;
			}
		}
	}
	//Make factor = 2 to get different numbers for p and q index
	factor = 2;
	for (size_t index = 0; index < sizeof(double); index++)
	{
		uint8_t byte = bytePointer[index];

		for (int bit = 0; bit < numBits; bit++)
		{
			if (qIndex + byte * factor > N) {
				//Reached the value just below N
				break;
			}
			else {
				qIndex += byte * factor;
				factor *= 2;
			}
		}
	}

	std::cout << "p Index: "<< pIndex << "\n";
	std::cout << "q Index: " << qIndex << "\n";
	
	indices.x = pIndex;
	indices.y = qIndex;

}

#endif // !Tools
