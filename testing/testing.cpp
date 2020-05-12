// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996).
/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <direct.h>
#include <windows.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
/* Developer Created Libraries*/
#include "nist_sts_tests.h"


using namespace cv;
using namespace std;

constexpr auto MAXPATHLEN = 100;

int main(int argc, char* argv[])
{
       
    // Wipe out old file
    ofstream myfile;
    myfile.open("seeds4Testing.txt", ios::trunc);
    myfile.close();
    
    /* Read all images in a folder */   
    // Get cwd
    char cwd[MAXPATHLEN];
    _getcwd(cwd, sizeof(cwd));
    string curpath;
    int i = 0;
    while (cwd[i] != '\0') {
        curpath += cwd[i];
        i++;
    }
    
    // Go to the directory where the test images are stored
    size_t found = curpath.find("Image_Entropy");
    //string testImages = curpath.substr(0, found);
    //testImages.append("Image_Entropy\\Image_Entropy\\images\\*");
    string testImages = "D:\\Pictures\\ENEE408GImages\\wallpapers\\*";
    vector<cv::String> filenames;	//Holds filenames of all images in the folder
    glob(testImages, filenames, false);
    
    // Run the algorithm for all the images in the test set
    string cmd;
    string exec = curpath.substr(0, found);
    exec.append("Image_Entropy\\x64\\Release\\Image_Entropy.exe ");

    for (i = 0; i < filenames.size(); i++) {
        cmd = exec + filenames[i] + " -t";
        system(cmd.c_str());
        //cout << i << endl;
    }

    
    //Run testing code
    string epsilon = readBinaryDigitsInASCIIFormat();
    Frequency(epsilon);
    LongestRunOfOnes(epsilon);
    Runs(epsilon);
    BlockFrequency(epsilon);
    FILE* resultsFile;
    resultsFile = fopen("results.txt", "a");
    fprintf(resultsFile, "For more detailed results see the text files corresponding to each test.\n");
    fclose(resultsFile);
    return 0;
}


