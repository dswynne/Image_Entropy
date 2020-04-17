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
#include <direct.h>
/* External Libraries: */
// OpenCV
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
// MPIR
#include <mpirxx.h>
/* Developer Created Libraries*/
#include "extractor.h"
#include "filter.h"
#include "mat_divisions.h"
#include "gen_bitstrings.h"
#include "tools.h"
using namespace cv;
using namespace std;


int main(int argc, char* argv[]) {
    ofstream myfile;
    myfile.open("output.txt", ios_base::app);
    // Getting image
    Mat I; 
    if (argc < 2) {
        //I = imread("C:\\School\\UMD\\ENEE408G\\Final_Project\\code\\Image_Entropy\\Image_Entropy\\images\\Lena.bmp");
        I = imread("D:\\Pictures\\ENEE408GImages\\wallpapers\\27-u3kAmlA.jpg", IMREAD_COLOR);
    }
    else {
        I = imread(argv[1]);
    }


    //int rows = I.rows;
    //int cols = I.cols;

    ////Struct I made to work around errors for detection of a bad image
    //struct ImageValidity v;
    //v = detectBadImage(I);
    //I = v.image;
    //if (!v.valid) {       
    //    cout << "Bad image provided. Please take a new image with more color diversity\n";

    //    //Close file and go to next image
    //    myfile.close();
    //    return 0;
    //}
    //
    //// For testing filter function. Won't modify main.cpp any more until I finish this
    ////Implemented in filter.cpp
    //Mat filteredImage = applyFilter(I);
    array<Mat, 3> filteredI = applyFilter_BGR(I);
    
    // Taking the BGR channels and XORing them for each pixel
    vector<vector<int>> Ib = channel_blender(filteredI);
        
    // Divding up the 2D intensity Mat and storing it in a 1D intensity vector 
    //vector<int> allpix = mat_cross(filteredImage);
    //vector<int> allpix = mat_jump(filteredImage);
    vector<int> allpix = mat_jump(Ib);

    // Generating N 32 byte bitstrings from the 1D intensity vector
    //vector<string> bitstrings = gen_bitstrings_whole_pixel(allpix);
    //vector<string> bitstrings = gen_bitstrings_HL(allpix);
    vector<string> bitstrings = gen_bitstrings_LSB(allpix);
    //vector<string> bitstrings = gen_bitstrings_bitshift(allpix);
    
    // Using a Von Neumman Extractor to generate a seed that is closer to truly random
    //string seed = vn_extractor(bitstrings);
    string seed = xor_extractor(bitstrings);
    //string seed = vn_extractor_recursive(bitstrings);

    //string seed = extractor_blender(seedVN, seedXOR);
    
    /*// Picking a random 32 byte bitsring from the vector of strings
    int numStrings = bitstrings.size();
    //int index = get_random_index(numStrings);
    Point temp = getPQIndices(numStrings, numStrings);
    int index = temp.x;
    string seed = bitstrings[index];*/
    
    // Outputting seed into a file
    myfile << seed << "\n";
    myfile.close();
    return 0;
       
}

