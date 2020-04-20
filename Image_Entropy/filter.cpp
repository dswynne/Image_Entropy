/* filter.cpp:
	Functions that deal with filtering the input image.
*/

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
/* External Libraries: */
// OpenCV
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
/* Developer Created Libraries*/
#include "filter.h"

using namespace cv;
using namespace std;

//Applies a filter to add layer of random to the image

Mat applyFilter(Mat input) {
	Mat grayInput = input;
	int rows = input.rows;
	int cols = input.cols;
	int randRowIndex = rows - 1;
	int randColIndex = cols - 1;

	//If not grayscale, convert to grayscale
	if (input.dims > 2) {
		cvtColor(input, grayInput, COLOR_BGR2GRAY);
	}
	//Get a value from grayscale image to use for "random" filter
	uchar randVal = grayInput.at<uchar>(randRowIndex, randColIndex);

	// Apply our version of salt and pepper filter
	for (int i = 0; i < rows; i+=2) {
		for (int j = 0; j < cols; j+=2) {
			grayInput.at<uchar>(i, j) = randVal;

		}
	}
	return grayInput;
}

/* This function applies a Salt & Pepper Noise filter on all three RGB color channels */
array<Mat, 3>  applyFilter_BGR(Mat I) {
	Mat bgrI[3];
	split(I, bgrI);
	Mat B = bgrI[0];
	Mat G = bgrI[1];
	Mat R = bgrI[2];
	
	Mat saltpepper_noise = Mat::zeros(B.rows, B.cols, CV_8U);
	randu(saltpepper_noise, 0, 255);

	Mat black = saltpepper_noise < 30;
	Mat white = saltpepper_noise > 225;

	Mat spB = B.clone();
	Mat spG = G.clone();
	Mat spR = R.clone();
	spB.setTo(255, white);
	spB.setTo(0, black);
	spG.setTo(255, white);
	spG.setTo(0, black);
	spR.setTo(255, white);
	spR.setTo(0, black);
	
	array<Mat, 3> spBGR;
	spBGR[0] = spB;
	spBGR[1] = spG;
	spBGR[2] = spR;

	return spBGR;
}

/* This function takes the BGR channels and XOR's them to create a one channel 2D matrix */
vector<vector<int>> channel_blender(array<Mat, 3> filteredI) {
	Mat B = filteredI[0];
	Mat G = filteredI[1];
	Mat R = filteredI[2];
	const int rows = B.rows;
	const int cols = B.cols;
	vector<vector<int>> Ib;
	int i, j;

	for (i = 0; i < rows; i++) {
		vector<int> row(cols);
		for (j = 0; j < cols; j++) {
			row[j] = int(B.at<uchar>(i, j) ^ G.at<uchar>(i, j) ^ R.at<uchar>(i, j));
		}
		Ib.push_back(row);
	}
	return Ib;
}