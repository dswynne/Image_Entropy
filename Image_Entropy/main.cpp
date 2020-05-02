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

int main(int argc, char* argv[]) {
    ofstream myfile;
    myfile.open("output.txt", ios_base::app);
    // Getting image
    Mat I;


    if (argc < 2) {
        char cwd[MAXPATHLEN];
        _getcwd(cwd, sizeof(cwd));
        string path;
        int i = 0;
        while (cwd[i] != '\0') {
            path += cwd[i];
            i++;
        }
        //path.append("\\images\\27-u3kAmlA.jpg");
        //path.append("\\images\\28-jk8YxLB.jpg");
        path.append("\\images\\Lena.bmp");
        I = imread(path);//IMREAD_ANYDEPTH
    }
    else {
        I = imread(argv[1]);
    }

    cout << I.channels();
    int rows = I.rows;
    int cols = I.cols;

    //Struct I made to work around errors for detection of a bad image
    struct ImageValidity v;
    v = detectBadImage(I);
    I = v.image;
    if (!v.valid) {       
        cout << "Bad image provided. Please take a new image with more color diversity\n";

        //Close file and go to next image
        myfile.close();
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

    //Generate RSA keypair and AES key
    retValsRSA r = generateRSAKey(seed);
    retValsAES a = generateAESKey(seed);

    // Outputting seed into a file
    myfile << seed << "\n";
    myfile.close();
    return 0;
       
}

