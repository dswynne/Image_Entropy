/* mat_division.cpp:
   Functions that convert 2D intensity matrix to 1D intensity vector for easier manipulation.
   Each function is a different implementation of how to step through the matrix.
*/

/* Standard Libraries: */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
/* Developer Created Libraries*/
#include "main.h"

using namespace std;
using namespace cv;

/* This implementation horizontally weaves through the 2D matrix row by row ergo the name snake. 
   Order is A[0,0],A[0,1],...,A[0,N-1],A[1,0],...,A[N,N] 
   where A is the intensity_mat and N is the number of columns 
*/
vector<int> mat_snake(Mat intensity_mat, int rows, int cols) {
    // intializing values
    int i, j;
    const int len = rows * cols;
    vector<int> allpix(len);

    // storing intensity values in a 1D vector
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            allpix[i * cols + j] = int(intensity_mat.at<uchar>(i, j));
        }
    }
    return allpix;
}

/* This implementation follows the diagonals of the 2D matrix. 
   Order is A[0,0],A[1,0],A[0,1],A[2,0],A[1,1],A[0,2],...,A[N,N] 
   where A is the intensity_mat and N is the number of columns
*/
vector<int> mat_cross(Mat intensity_mat, int rows, int cols) {
    // intializing values
    int i = 0, j = 0, k = 0, m = 1, n = 0;
    const int len = rows * cols;
    vector<int> allpix(len);

    // storing intensity values in a 1D vector
    allpix[k] = int(intensity_mat.at<uchar>(i, j));
    i++;
    k++;
    // storing up to when i reaches the last row
    while (k < len) {
        while (i >= 0) {
            allpix[k] = int(intensity_mat.at<uchar>(i, j));
            i--;
            j++;
            k++;
        }
        j = 0;
        m++;
        i = m;
        if (i == rows) {
            i--;
            m--;
            break;
        }
    }
    // storing for the diagonals after i has reached the last row
    j++;
    n = j;
    while (k < len) {
        while (i >= n) {
            allpix[k] = int(intensity_mat.at<uchar>(i, j));
            i--;
            j++;
            k++;
        }
        i = m;
        n++;
        j = n;
    }
    return allpix;
}

/* This implementation starts at the top left corner of the 2D matrix. 
   Then jumps to the bottom right corner and back.
   This process repeats until the center is reached.
   Order is A[0,0],A[N,N],A[1,0],A[N-1,N],A[0,1],A[N,N-1],A[0,2],A[N,N-2],A[1,1],...
   where A is the intensity_mat and N is the number of columns
   In the comments...
   - The top half is anything before the diagonal going from the bottom left corner to the bottom right corner.
   - The bot half is anything after the diagonal described above
*/
vector<int> mat_jump(Mat intensity_mat, int rows, int cols) {
    // intializing values
    int i = 0, j = 0, k = 0;
    const int len = rows * cols;
    int m = rows - 1, n = cols - 1;
    int tb = 0, dirT = 0, dirB = 0;
    vector<int> allpix(len);
    
    // storing intensity values in a 1D vector
    // storing the two corners first
    allpix[k] = int(intensity_mat.at<uchar>(i, j));
    i++;
    k++;
    allpix[k] = int(intensity_mat.at<uchar>(m, n));
    m--;
    k++;
    // storing the rest
    while (k < len) {
        if (tb == 0) { // Get a pixel from the top half
            allpix[k] = int(intensity_mat.at<uchar>(i, j));
            if (dirT == 0) { // Going towards the upper right corner
                i--;
                j++;
                k++;
            }
            else if (dirT == 1) { // Going away from the upper right corner
                j--;
                i++;
                k++;
            }
            tb = 1;
        }
        else if (tb == 1) { // Get a pixel from the bot half
            allpix[k] = int(intensity_mat.at<uchar>(m, n));
            if (dirB == 0) { // Going away from the upper right corner
                n--;
                m++;
                k++;
            }
            else if (dirB == 1) { // Going towards the upper right corner
                m--;
                n++;
                k++;
            }
            tb = 0;
        }
        else if (tb == 2) { // Special case of the main diagonal
            allpix[k] = int(intensity_mat.at<uchar>(i, j));
            k++;
            allpix[k] = int(intensity_mat.at<uchar>(j, i));
            k++;
            i++;
            j--;
        }

        // Checking the direction and switching accordingly for the top half of the matrix
        if (i < 0) { // Start going away from the upper right corner
            i = 0;
            dirT = 1;
        }
        else if (j < 0) { // Start going towards from the upper right corner
            j = 0;
            dirT = 0;
        }

        // Checking the direction and switching accordingly for the bot half of the matrix
        if (m > rows - 1) { // Start going towards from the upper right corner
            m = rows - 1;
            dirB = 1;
        }
        else if (n > cols - 1) { // Start going away from the upper right corner
            n = cols - 1;
            dirB = 0;
        }

        // Checking if we have reached the main diagonal (bottom left corner to the bottom right corner)
        if (j == cols - 1) {
            tb == 2;
        }

    }
    return allpix;
}