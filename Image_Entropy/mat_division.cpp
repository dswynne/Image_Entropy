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
vector<int> mat_snake(int** intensity_mat, int rows, int cols) {
    // intializing values
    int i, j;
    const int len = rows * cols;
    std::vector<int> allpix(len);

    // storing intensity values in a 1D vector
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            allpix[i * cols + j] = intensity_mat[i][j];
        }
    }
    return allpix;
}