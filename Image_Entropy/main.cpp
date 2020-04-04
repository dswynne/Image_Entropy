/* main.cpp : 
   This file contains the 'main' function. Program execution begins and ends there.
   Initial image handling and mpz_t type logic are stored in this file.
*/

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
#include "tools.h"

using namespace cv;
using namespace std;


/* Taking the intensity values of each pixel and storing it in a 2D matrix
*/
int** find_intensity(Mat I, int rows, int cols) {
    // intializing values
    unsigned char intensity;
    int** intensity_mat = 0;
    intensity_mat = new int* [rows];
    int i, j;

    // storing intensity values
    for (i = 0; i < rows; i++) {
        intensity_mat[i] = new int[cols];
        for (j = 0; j < cols; j++) {
            intensity = I.at<uchar>(i, j);
            intensity_mat[i][j] = int(intensity);
        }
    }
    
    return intensity_mat;
}


/* (TODO):
    - Design at least 2 more ways to divide up the intensity matrix and develop tests for them
    - pick source of data for choosing the bitstring that is actually used
    - start work on filters
*/
int main() {
	// Getting image
    Mat I = imread("Lena.bmp");
    int rows = I.rows;
    int cols = I.cols;
    
    // For testing filter function. Won't modify main.cpp any more until I finish this
    //Implemented in filter.cpp
    Mat filteredImage = applyFilter(I);

    // Storing intensity values of image
    int** intensity_mat = find_intensity(I, rows, cols);
        
    // Divding up the 2D intensity matrix and storing it in a 1D intensity vector
    // (TESTING) This is one implementation of breaking up the 2D matrix the goal will be to test at least two other implementations. 
    vector<int> allpix = mat_snake(intensity_mat, rows, cols);
    
    // Generating N p&q bitstrings from the 1D intensity vector
    bitstrings bitstrings = gen_bitstrings(allpix);

    // (NOTE) I think we will have to do all of the mpz_t type operations inside of main and not be able to pass through functions.
    // This probably means that we will not do too many operations on the mpz_t once it is in that form.
    // Might just want to keep the randomization strictly image processing based

    // Picking a random bitstring from the struct of vector strings for p&q
    // (NEED TO)  Pick a source of randomization that isn't the standard rand func
    int pSZ = bitstrings.p.size();
    int qSZ = bitstrings.q.size();
    srand(time(NULL));
    int pIdx = rand() % pSZ;
    int qIdx = rand() % qSZ;
    std::vector<char*> cstringsP, cstringsQ; // (NEED TO) Check if these actually need to be vectors or if you can just pull it out as a const char*
    cstringsP.reserve(pSZ);
    cstringsP.push_back(const_cast<char*>(bitstrings.p[pIdx].c_str()));
    cstringsQ.reserve(qSZ);
    cstringsQ.push_back(const_cast<char*>(bitstrings.q[qIdx].c_str()));
     
    // Converting bitstrings back to ints
    mpz_t pInt;
    mpz_t qInt;
    mpz_init(pInt);
    mpz_init(qInt);
    mpz_set_str(pInt, cstringsP[0], 10);
    mpz_set_str(qInt, cstringsQ[0], 10);


	return 0;
}