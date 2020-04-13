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
#include <fstream>
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
    ofstream myfile;
    myfile.open("example.txt");
    // Getting image
    Mat I = imread("Lena.bmp");
    int rows = I.rows;
    int cols = I.cols;

 
    I = detectBadImage(I);
    if (countNonZero(I) == 0) {       
        //Image is all black and a bad image
        cout << "Bad image provided. Please take a new image with more color diversity\n";

        //Close file and go to next image
        myfile.close();
        return 0;
    }
    
    // For testing filter function. Won't modify main.cpp any more until I finish this
    //Implemented in filter.cpp
    Mat filteredImage = applyFilter(I);
    
    // Divding up the 2D intensity Mat and storing it in a 1D intensity vector
    // (TESTING) Three seperate implementations for testing 
    //vector<int> allpix = mat_snake(filteredImage);
    vector<int> allpix = mat_cross(filteredImage);
    //vector<int> allpix = mat_jump(filteredImage);

    // Generating N 32 byte bitstrings from the 1D intensity vector
    vector<string> bitstrings = gen_bitstrings_new(allpix);
   
    // Picking a random 32 byte bitsring from the vector of strings
    int numStrings = bitstrings.size();
    int index = get_random_index(numStrings);

    /* CODE TO TEST RANDOMNESS WILL BREAK OUT LATER*/
    string seed = bitstrings[index];
    myfile << seed << "\n";
    myfile.close();
    /*END OF CODE TO TEST RANDOMNESS */
    
   return 0;
}