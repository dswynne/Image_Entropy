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
inline string type2str(int type) {
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
inline void printMatType(cv::Mat input) {
	string imageInfo = type2str(input.type());
	cout << "\n\n" << imageInfo.c_str() << "\n\n";
}


inline void printMatArray(cv::Mat M) {
	cout << "M = " << endl << " " << M << endl << endl;
}

//Junk function used for getPQIndices()
inline int mathFunc(int a, int b) {
	int c = 0;
	int numCalcs = 250000;
	for (int i = 0; i < numCalcs; i++) {
		c = a * b;
		c = a + b;
	}
	return c;
}


inline cv::Point getPQIndices(int numPStrings, int numQStrings)
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

	//std::cout << "p Index: "<< pIndex << "\n";
	//std::cout << "q Index: " << qIndex << "\n";
	
	indices.x = pIndex;
	indices.y = qIndex;
	return indices;
}

inline int get_random_index(int numStrings) {

	int N = numStrings;
	int index = 0;

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
	uint8_t byte;
	int totalBitsUsed = 0;

	totalBitsUsed = 0;
	for (size_t index = 0; index < sizeof(double); index++)
	{
		byte = bytePointer[index];
		for (int bit = 0; bit < 8; bit++)
		{
			//Only use the number bits needed to reach N
			if (totalBitsUsed >= numBits) {
				break;
			}

			if (index + byte * factor > N) {
				//Reached the value just below N
				break;
			}
			else {
				index += byte * factor;
				factor *= 2;
			}

			byte >>= 1;
			totalBitsUsed++;
		}
	}
	return index;
}

//Finds alpha and beta to correct grayscale image
inline cv::Point2f autoAdjustImage(cv::Mat input, float histogramPercent)
{
	cv::Point2f output;
	int histogramLength = 256;
	float alpha, beta;
	double minGray = 0, maxGray = 0;
	cv::Mat hist; //the grayscale histogram

	//to calculate grayscale histogram
	cv::Mat gray;
	if (input.type() == CV_8UC1) {
		gray = input;
	}
	else {
		cvtColor(input, gray, cv::COLOR_BGR2GRAY);
	}

	//If you don't want to cut off a certain percentage of the ends
	if (histogramPercent == 0)
	{
		// keep full available range
		cv::minMaxLoc(gray, &minGray, &maxGray);
	}
	else
	{
		float range[] = { 0, 256 };
		const float* histRange = { range };
		
		//Get historgram of intensity values of input image
		calcHist(&gray, 1, 0, cv::Mat(), hist, 1, &histogramLength, &histRange, true, false);

		// calculate cumulative distribution from the histogram
		std::vector<float> accumulator(histogramLength);
		accumulator[0] = hist.at<float>(0);
		for (int i = 1; i < histogramLength; i++)
		{
			accumulator[i] = accumulator[i-1] + hist.at<float>(i);
		}

		// Get max value from last element in accumulator vector
		float max = accumulator.back();
		histogramPercent *= (max / 100.0); //make percent cut off relative to max value of histogram
		histogramPercent /= 2.0; // divide by 2 as there are left and right sides to distribution

		//Start minGray at the far left and increment until you reach the cutoff on left side
		minGray = 0;
		while (accumulator[minGray] <= histogramPercent)
			minGray++;

		//Start maxGray at the far right and decrement until you reach the cutoff on left side
		maxGray = histogramLength - 1;
		while (accumulator[maxGray] >= (max - histogramPercent))
			maxGray--;
	}

	//Calculate alpha and beta to modify each pixel in original image
	alpha = 255 / (maxGray - minGray);
	beta = -minGray * alpha;

	output.x = alpha;
	output.y = beta;
	return output;
}

// Check if there is too much of one color in image
// Returns 1 if image is ok
// Returns 0 if image is not ok
inline int checkRGBImageColors(cv::Mat input, int upperThresh, int lowerThresh) {

	int upperFlag[3] = { 0 };
	int lowerFlag[3] = { 0 };

	//Get mean r, g, b channel values
	cv::Scalar meanValues = cv::mean(input);

	// If some of the channels are above upperThresh while others are below lowerThresh, probably too much of a color
	for (int i = 0; i < 3; i++) {
		//Set flags to indicate channels that are above or below the threshold
		if (meanValues[i] >= upperThresh)
			upperFlag[i] = 1;
		if (meanValues[i] <= lowerThresh)
			lowerFlag[i] = 1;
	}

	//First check R, G, B. check if one channel is high while others are low
	if (upperFlag[0] && lowerFlag[1] && lowerFlag[2]) {
		return 0;
	}
	else if (upperFlag[1] && lowerFlag[0] && lowerFlag[2]) {
			return 0;
	}
	else if (upperFlag[2] && lowerFlag[0] && lowerFlag[1]) {
		return 0;
	}

	//Second, Check pairs of channels that are high while third channel is low

	//Not sure if this necessary, I don't know what the RGB values of normal images are

	//Third, check for all white image
	if (upperFlag[0] && upperFlag[1] && upperFlag[2])
		return 0;

	//Fourth, check for all black image
	if (lowerFlag[0] && lowerFlag[1] && lowerFlag[2])
		return 0;

	return 1;
}

//image contains the Mat
// if invalid, valid = 0;
struct ImageValidity {
	cv::Mat image;
	int valid = 0;
};

//Detects if image is too monochromatic. Will change image if there is too much of one color above
//the threshold
inline ImageValidity detectBadImage(cv::Mat input)
{

	struct ImageValidity v;
	v.valid = 1;
	cv::Mat output = input;
	double alpha = 0.0;
	double beta = 0;
	int lowerThresh = 20;
	int upperThresh = 220;

	//Use the grayscale image to fix the original image
	cv::Point2f values = autoAdjustImage(input, 0.25);
	alpha = (double)values.x;
	beta = (double)values.y;

	// Apply alpha and beta to get new image
	//convertScaleAbs(input, output, alpha, beta);
	for (int y = 0; y < input.rows; y++) {
		for (int x = 0; x < input.cols; x++) {
			for (int c = 0; c < input.channels(); c++) {
				output.at<cv::Vec3b>(y, x)[c] =
					cv::saturate_cast<uchar>(alpha * input.at<cv::Vec3b>(y, x)[c] + beta);
			}
		}
	}

	//Now check RGB image after adjustment to see if any colors are too strong
	if (output.channels() > 2) {
		//Image is  RGB and must check all three channels
		if (!checkRGBImageColors(input, upperThresh, lowerThresh)) {
			v.valid = 0;
		}
	}
	v.image = output;

	return v;
}

#endif // !Tools
