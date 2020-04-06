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

	int N = numPStrings;
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
	return indices;
}

//Finds alpha and beta to correct grayscale image
cv::Point2f autoAdjustImage(cv::Mat src, float clipHistPercent)
{
	cv::Point2f output;
	int histSize = 256;
	float alpha, beta;
	double minGray = 0, maxGray = 0;

	//to calculate grayscale histogram
	cv::Mat gray;
	if (src.type() == CV_8UC1) gray = src;
	else if (src.type() == CV_8UC3) cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	else if (src.type() == CV_8UC4) cvtColor(src, gray, cv::COLOR_BGR2GRAY);
	if (clipHistPercent == 0)
	{
		// keep full available range
		cv::minMaxLoc(gray, &minGray, &maxGray);
	}
	else
	{
		cv::Mat hist; //the grayscale histogram

		float range[] = { 0, 256 };
		const float* histRange = { range };
		bool uniform = true;
		bool accumulate = false;
		calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

		// calculate cumulative distribution from the histogram
		std::vector<float> accumulator(histSize);
		accumulator[0] = hist.at<float>(0);
		for (int i = 1; i < histSize; i++)
		{
			accumulator[i] = accumulator[i - 1] + hist.at<float>(i);
		}

		// locate points that cuts at required value
		float max = accumulator.back();
		clipHistPercent *= (max / 100.0); //make percent as absolute
		clipHistPercent /= 2.0; // left and right wings
		// locate left cut
		minGray = 0;
		while (accumulator[minGray] < clipHistPercent)
			minGray++;

		// locate right cut
		maxGray = histSize - 1;
		while (accumulator[maxGray] >= (max - clipHistPercent))
			maxGray--;
	}

	alpha = 255 / (maxGray - minGray);
	beta = -minGray * alpha;

	output.x = alpha;
	output.y = beta;
	return output;
}


//Detects if image is too monochromatic. Will change image if there is too much of one color above
//the threshold
cv::Mat detectBadImage(cv::Mat input, int upperThesh, int lowerThresh)
{
	cv::Mat output = input;
	cv::Mat grayInput;
	double alpha = 0.0;
	double beta = 0;
	int rgbFlag = 0;

	if (input.dims > 2) {
		//Image is  RGB and must check all three channels
		rgbFlag = 1;
	}

	//Use the grayscale image to fix the original image
	cv::Point2f values = autoAdjustImage(input, 0.0);
	alpha = (double)values.x;
	beta = (double)values.y;
	
	convertScaleAbs(input, output, alpha, beta);

	if (rgbFlag) {
		cout << "Need to analyze RGB channels for correction\n";
		cout << "This has not been implemented yet\n";
	}

	return output;
}

#endif // !Tools
