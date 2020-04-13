// testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
/*// NIST STS
#include "defs.h"
#include "externs.h"
#include "config.h"
#include "stat_fncs.h"
#include "utilities.h"*/
/* Developer Created Libraries*/
#include "nist_sts_tests.h"
//#include "../Image_Entropy/main.h"
//#include "../Image_Entropy/tools.h"

using namespace cv;
using namespace std;



int main()
{
    char choice[1];
    // put in prompt asking yourself if you want to do this or just skip to testing
    printf("Read in new images? 1 for yes, 0 for no: ");
    scanf_s("%1d", choice);
    if ((int)choice[0] == 1) {
            /* Code for reading a folder of images */
            //Read all images in a folder
            vector<cv::String> filenames;	//Holds filenames of all images in the folder
            glob("D:\\Pictures\\ENEE408GImages\\wallpapers\\*", filenames, false);
            int i;
            string cmd;
            string exec = "C:\\School\\UMD\\ENEE408G\\Final_Project\\code\\Image_Entropy\\x64\\Release\\Image_Entropy.exe ";
            for (i = 0; i < filenames.size(); i++) {
                cmd = exec + filenames[i];
                system(cmd.c_str());
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
    }
    

     
    //Run testing code
    string epsilon = readBinaryDigitsInASCIIFormat();
    Frequency(epsilon);
}

