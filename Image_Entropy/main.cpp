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
Mat find_intensity(Mat input, int rows, int cols) {
    // intializing values


   /* 
    if (input.channels() > 1) {
        cvtColor(input, input, COLOR_BGR2GRAY);
    }*/
    return input;
    
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
    Mat intensity_mat = find_intensity(I, rows, cols);

    //Start stopwatch to time length of mat_snake execution
    auto start = chrono::high_resolution_clock::now();
        
    // Divding up the 2D intensity matrix and storing it in a 1D intensity vector
    // (TESTING) This is one implementation of breaking up the 2D matrix the goal will be to test at least two other implementations. 
    Mat allpix = mat_snake(intensity_mat, rows, cols);

    //Stop stopwatch and display elapsed time for mat_snake execution
    //auto finish = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsed = finish - start;
    //std::cout << "Mat_snake() Execution Time: " << elapsed.count() << " s\n";

    
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