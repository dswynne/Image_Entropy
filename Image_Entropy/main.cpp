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

int main() {
	// Getting image
    Mat I = imread("Lena.bmp");
    int rows = I.rows;
    int cols = I.cols;

    int lowerThresh = 20;
    int upperThresh = 220;

    I = detectBadImage(I, lowerThresh, upperThresh);
    if (countNonZero(I) == 0) {
        //Image is all black and a bad image
        cout << "Bad image provided. Please take a new image with more color diversity\n";
        waitKey();
        return 0;
    }
    
    // For testing filter function. Won't modify main.cpp any more until I finish this
    //Implemented in filter.cpp
    Mat filteredImage = applyFilter(I);
    
    // Divding up the 2D intensity Mat and storing it in a 1D intensity vector
    // (TESTING) Three seperate implementations for testing 
    //vector<int> allpix = mat_snake(filteredImage, rows, cols);
    vector<int> allpix = mat_cross(filteredImage, rows, cols);
    //vector<int> allpix = mat_jump(filteredImage, rows, cols);

    // Generating N p&q bitstrings from the 1D intensity vector
    bitstrings bitstrings = gen_bitstrings(allpix);

    // (NOTE) I think we will have to do all of the mpz_t type operations inside of main and not be able to pass through functions.
    // This probably means that we will not do too many operations on the mpz_t once it is in that form.
    // Might just want to keep the randomization strictly image processing based

    // Picking a random bitstring from the struct of vector strings for p&q
    int numPStrings = bitstrings.p.size();
    int numQStrings = bitstrings.q.size();
    Point pq = getPQIndices(numPStrings, numQStrings);
    int pIdx = pq.x;
    int qIdx = pq.y;
    const char* cstringsP; 
    const char* cstringsQ;
    cstringsP = const_cast<char*>(bitstrings.p[pIdx].c_str());
    cstringsQ = const_cast<char*>(bitstrings.q[qIdx].c_str());
     
    // Converting bitstrings back to ints
    mpz_t pInt;
    mpz_t qInt;
    mpz_init(pInt);
    mpz_init(qInt);
    mpz_set_str(pInt, cstringsP, 10);
    mpz_set_str(qInt, cstringsQ, 10);

    // Find a the next prime greater than pInt and qInt
    mpz_t pPrime;
    mpz_t qPrime;
    mpz_init(pInt);
    mpz_init(qInt);
    gmp_randstate_t pState;
    gmp_randstate_t qState;
    gmp_randinit_mt(pState);
    gmp_randinit_mt(qState);
    mpz_next_prime_candidate(pPrime, pInt, pState);
    mpz_next_prime_candidate(qPrime, qInt, qState);



	return 0;
}