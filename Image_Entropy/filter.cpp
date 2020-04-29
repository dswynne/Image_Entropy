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

Mat applyFilter_GS(Mat input) {
	Mat rgbInput = input;
	int rows = input.rows;
	int cols = input.cols;
	int randRowIndex = rows - 1;
	int randColIndex = cols - 1;

	//Get a value from grayscale image to use for "random" filter
	Vec3b randVal = rgbInput.at<cv::Vec3b>(randRowIndex, randColIndex);

	// Apply our version of salt and pepper filter
	for (int i = 0; i < rows; i += 4) {
		for (int j = 0; j < cols; j += 4) {
			for (int k = 0; k < input.channels(); k++) {
				rgbInput.at<cv::Vec3b>(i, j)[k] = randVal[k];
			}
		}
	}

	return rgbInput;
}

/* This function applies a Salt & Pepper Noise filter on all three RGB color channels.
	The function then calls a subfunction that blends all the channels back together.
	Or it calls the grayscale filtering function if the image is detected to be grey scale.
	If the image is grayscale there is no need to blend the channels.
*/
vector<vector<int>>  applyFilter_BGR(Mat I) {
	if (I.channels() == 1) { // Grayscale
		Mat filteredI = applyFilter_GS(I);
		vector<vector<int>> vecI;
		int i, j;

		for (i = 0; i < filteredI.rows; i++) {
			vector<int> row(filteredI.cols);
			for (j = 0; j < filteredI.cols; j++) {
				row[j] = int(filteredI.at<uchar>(i, j));
			}
			vecI.push_back(row);
		}
		
		return vecI;
	}
	else if (I.channels() == 3) { // RGB
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

		array<Mat, 3> filteredI;
		filteredI[0] = spB;
		filteredI[1] = spG;
		filteredI[2] = spR;

		vector<vector<int>> vecI = channel_blender(filteredI);
		return vecI;
	}
	else { // not an accebtable color coordinate system
		vector<vector<int>> vecI;
		return vecI;
	}
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