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
    //char choice[1];
    //printf("Read in new images? 1 for yes, 0 for no: ");
    //scanf_s("%1d", choice);
    //if ((int)choice[0] == 1) {
        
        // Wipe out old file
        ofstream myfile;
        myfile.open("seeds4Testing.txt", ios::trunc);
        myfile.close();
        /* Code for reading a folder of images */
        //Read all images in a folder
        
        char cwd[MAXPATHLEN];
        _getcwd(cwd, sizeof(cwd));
        string curpath;
        int i = 0;
        while (cwd[i] != '\0') {
            curpath += cwd[i];
            i++;
        }
        size_t found = curpath.find("Image_Entropy");
        string testImages = curpath.substr(0, found);
        testImages.append("Image_Entropy\\Image_Entropy\\images\\*");
        vector<cv::String> filenames;	//Holds filenames of all images in the folder
        //glob("D:\\Pictures\\ENEE408GImages\\wallpapers\\*", filenames, false);
        glob(testImages, filenames, false);
        string cmd;
        string exec = curpath.substr(0, found);
        exec.append("Image_Entropy\\x64\\Release\\Image_Entropy.exe ");

        //string exec = "C:\\School\\UMD\\ENEE408G\\Final_Project\\code\\Image_Entropy\\x64\\Release\\Image_Entropy.exe ";
        for (i = 0; i < filenames.size(); i++) {
            cmd = exec + filenames[i] + " -t";
            system(cmd.c_str());
            //cout << i << endl;
        }

        /*//Vector that holds all of the images in the folder
        vector<Mat> images;
        size_t count = filenames.size(); //number of image files in the folder

        // Create array of filenames
        for (size_t i = 0; i < count; i++) {
            images.push_back(imread(filenames[i]));
        }

        Mat imageToTest;
        // Run through all the images
        for (size_t i = 0; i < count; i++) {
            imageToTest = images[i];
        }*/
//}
    

     
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


