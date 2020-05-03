/* main.cpp : 
   This file contains the 'main' function. Program execution begins and ends there.
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
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
/* Developer Created Libraries*/
#include "extractor.h"
#include "filter.h"
#include "mat_divisions.h"
#include "gen_bitstrings.h"
#include "tools.h"
#include "sha256.h"
#include "hash2seed.h"
#include "generateKeys.h"

using namespace cv;
using namespace std;

constexpr auto MAXPATHLEN = 100;

/* TODO: 
    - Make arguments where this prints out seed: + seed, etc. & just the seeds for the generator
    - Ensure file paths can be read as arguments
    - Get the RSA/AES keys into the text file as well
*/
int main(int argc, char* argv[]) {
    
    // Get current working directory
    char cwd[MAXPATHLEN];
    _getcwd(cwd, sizeof(cwd));
    string curpath;
    int i = 0;
    while (cwd[i] != '\0') {
        curpath += cwd[i];
        i++;
    }
    
    // Opening text file for writing outputs
    ofstream outfile;
    string temp = curpath;

    if (string(argv[2]) == "-t") { // Being called by the test function
        temp.append("\\seeds4Testing.txt");
        string outputText = temp;
        outfile.open(outputText, ios::app);
    }
    else if (string(argv[2]) == "-o") { // Being called by the app
        temp.append("\\output.txt");
        string outputText = temp;
        outfile.open(outputText);
    }

    // Getting image
    Mat I;
    if (argc < 2) { 
        outfile << "Not enough input arguments." << endl;
        outfile.close();
        return 0;
    }
    else {
        I = imread(argv[1]);
    }
    

    int rows = I.rows;
    int cols = I.cols;

    if (rows == 0) {
        outfile << "Image not opened." << endl;
        outfile.close();
        return 0;
    }

    //Struct I made to work around errors for detection of a bad image
    struct ImageValidity v;
    v = detectBadImage(I);
    I = v.image;
    if (!v.valid) {       
        //cout << "Bad image provided. Please take a new image with more color diversity\n";
        if (string(argv[2]) == "-o") {
            outfile << "Bad image provided. Please input a new image with more color diversity." << endl;
        }

        //Close file and go to next image
        outfile.close();
        return 0;
    }
        
    // Applying noise filter to the image
    vector<vector<int>> vecI = applyFilter_BGR(I);
           
    // Divding up the 2D intensity Mat and storing it in a 1D intensity vector 
    vector<int> allpix = mat_jump(vecI);

    // Generating N 32 byte bitstrings from the 1D intensity vector
    vector<string> bitstrings = gen_bitstrings_LSB(allpix);
    
    // Using an extractor to generate a seed that is closer to truly random
    string extracted = xor_extractor(bitstrings);

    //Using SHA-2 Hash function to generate a random hash
    string hash = sha256(extracted);

    // Converting the hash into a new bitstring that will serve as the seed
    string seed = hash2seed(hash);

    // Determing which format the output should be
    if (string(argv[2]) == "-t"){ // Being called by the test function
        // Outputting seed into a file
        outfile << seed << endl;
        outfile.close();
    }
    else if (string(argv[2]) == "-o"){ // Being called by the app
        // Outputting seed into a file
        outfile << "Seed:" << endl;
        outfile << seed << endl;

        // Generating RSA keys
        retValsRSA RSAKeys = generateRSAKey(seed);
        outfile << "RSA Keys:" << endl;
        outfile << "\n" << RSAKeys.privateKey << endl;
        outfile << RSAKeys.privateKey << endl;
        outfile.close();
    }
    return 0;
       
}

