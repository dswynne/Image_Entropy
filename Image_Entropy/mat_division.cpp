/* mat_division.cpp:
   Functions that convert 2D intensity matrix to 1D intensity vector for easier manipulation.
   Each function is a different implementation of how to step through the matrix.
*/

/* Standard Libraries: */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
/* Developer Created Libraries*/
#include "main.h"

using namespace std;

/* This implementation weaves through the 2D matrix row by row ergo the name snake. */
cv::Mat mat_snake(cv::Mat intensity_mat, int rows, int cols) {
    cv::Mat oneDMat = intensity_mat.reshape(0, 1);
    return oneDMat;
}