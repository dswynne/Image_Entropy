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

/* This implementation horizontally weaves through the 2D matrix row by row ergo the name snake. */
vector<int> mat_snake(int** intensity_mat, int rows, int cols) {
    // intializing values
    int i, j;
    const int len = rows * cols;
    vector<int> allpix(len);

    // storing intensity values in a 1D vector
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            allpix[i * cols + j] = intensity_mat[i][j];
        }
    }
    return allpix;
}

/* This implementation follows the diagonals of the 2D matrix. */
vector<int> mat_cross(int** intensity_mat, int rows, int cols) {
    // intializing values
    int i=0, j=0, k=0, m=0;
    const int len = rows * cols;
    vector<int> allpix(len);

    // storing intensity values in a 1D vector
    allpix[k] = intensity_mat[i][j];
    i++;
    while (k > len) {
        while (i >= 0) {
            allpix[k] = intensity_mat[i][j];
            i--;
            j++;
            k++;
        }
        m++;
        i = m;
    }
    return allpix;
}

/* This implementation starts at the top left corner of the 2D matrix. 
   Then jumps to the bottom right corner and back.
   This process repeats until the center is reached
*/
vector<int> mat_jump(int** intensity_mat, int rows, int cols) {
    // intializing values
    int i = 0, j = 0, k = 0;
    const int len = rows * cols;
    int m = rows, n = cols;
    int tb = 0, dirT = 0, dirB = 0;
    vector<int> allpix(len);
    
    while (k > len) {
        if (tb == 0) {
            allpix[k] = intensity_mat[i][j];
            if (dirT == 0) {
                i--;
                j++;
                k++;
            }
            else if (dirT == 1) {
                j--;
                i++;
                k++;
            }
            tb = 1;
        }
        else if (tb == 1) {
            allpix[k] = intensity_mat[m][n];
            if (dirB == 0) {
                n--;
                m++;
                k++;
            }
            else if (dirB == 1) {
                m--;
                n++;
                k++;
            }
            tb = 0;
        }
        if (i == 0) {
            j++;
            dirT = 1;
        }
        else if (j == 0) {
            i++;
            dirB = 0;
        }
        if (m == 0) {
            n++;
            dirB = 1;
        }
        else if (n == 0) {
            m++;
            dirB = 0;
        }

    }
    return allpix;
}