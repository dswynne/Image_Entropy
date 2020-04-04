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

/* Developer Created Libraries*/
#include "main.h"


using namespace cv;
using namespace std;

//Applies a filter to add layer of random to the image
Mat applyFilter(Mat input) {

	Mat grayInput;
	int rows = input.rows;
	int cols = input.cols;

	int randRowIndex = rows - 1;
	int randColIndex = cols - 1;
	int randVal = 0;

	//If not grayscale, convert to grayscale
	if (input.channels() > 1) {
		cvtColor(input, grayInput, COLOR_BGR2GRAY);
	}

	//Get a value from grayscale image to use for "random" filter
	randVal = int(grayInput.at<uchar>(randRowIndex, randColIndex));

	// Apply our version of salt and pepper filter
	for (int i = 0; i < rows; i+=2) {
		for (int j = 0; j < cols; j+=2) {

			grayInput.at<int>(i, j) = randVal;

		}
	}
	return grayInput;
}