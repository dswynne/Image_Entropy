/* mat_division.cpp:
   Functions that convert 2D intensity matrix to 1D intensity vector for easier manipulation.
   Each function is a different implementation of how to step through the matrix.
*/

/* Standard Libraries: */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* Developer Created Libraries*/
#include "mat_divisions.h"

using namespace std;


/* This function is called by all implementations of matrix dividing.
   It simply takes a rectangular matrix and makes it a square matrix.
   This helps with simplifyinhg logic in the matrix diving functions
   as well as further altering the initial input image.
*/
vector<vector<int>> make_square(vector<vector<int>> intensity_mat) {
    int i, j;
    const int rows = intensity_mat.size();
    const int cols = intensity_mat[0].size();
    int reshapeFactor;

    if (rows == cols) { // already a square
        vector<vector<int>> intensity_sq;

        for (i = 0; i < rows; i++) {
            vector<int> row(rows);
            for (j = 0; j < cols; j++) {
                row[j] = intensity_mat[i][j];
            }
            intensity_sq.push_back(row);
        }
        return intensity_sq;
    }
    else if (rows > cols) { // portrait photo
        reshapeFactor = floor((rows - cols) / 2);
        vector<vector<int>> intensity_sq;

        for (i = 0; i < cols + reshapeFactor; i++) {
            vector<int> row(cols + reshapeFactor);
            for (j = 0; j < cols + reshapeFactor; j++) {
                row[j] = intensity_mat[i][j];
            }
            intensity_sq.push_back(row);
        }
        return intensity_sq;
    }
    else if (rows < cols) { // landscape photo
        reshapeFactor = floor((rows - cols) / 2);
        vector<vector<int>> intensity_sq;

        for (i = 0; i < rows + reshapeFactor; i++) {
            vector<int> row(rows + reshapeFactor);
            for (j = 0; j < rows + reshapeFactor; j++) {
                row[j] = intensity_mat[i][j];
            }
            intensity_sq.push_back(row);
        }
        return intensity_sq;
    }

}

/* This implementation horizontally weaves through the 2D matrix row by row ergo the name snake. 
   Order is A[0,0],A[0,1],...,A[0,N-1],A[1,0],...,A[N,N] 
   where A is the intensity_mat and N is the number of columns 
*/
vector<int> mat_snake(vector<vector<int>> intensity_mat) {
    // converting matrix to square matrix
    vector<vector<int>> intensity_sq = make_square(intensity_mat);
    // intializing values
    int i, j;
    int rows = intensity_sq.size();
    int cols = intensity_sq.size();
    const int len = rows * cols;
    vector<int> allpix(len);

    // storing intensity values in a 1D vector
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            allpix[i * cols + j] = intensity_sq[i][j];
        }
    }
    return allpix;
}

/* This implementation follows the diagonals of the 2D matrix.
   
   First starts from top left corner...
   Order is A[0,0],A[1,0],A[0,1],A[2,0],A[1,1],A[0,2],...,A[N,N] 
   where A is the intensity_mat and N is the number of columns
   
   Then starts from top right corner...
   Order is A[0,N],A[1,N],A[0,N-1],A[2,N],A[1,N-1],A[0,N-2],...,A[N,0]
   where A is the intensity_mat and N is the number of columns
*/
vector<int> mat_cross(vector<vector<int>> intensity_mat) {
    // converting matrix to square matrix
    vector<vector<int>> intensity_sq = make_square(intensity_mat);
    // intializing values
    int i, j, k;            // iterators
    int m, n;               // m keeps track of next row and n keeps track of next column 
    int c, d, e, f, g;      // case variables to tell j which direction it is going
    int rows = intensity_sq.size();
    int cols = intensity_sq.size();
    const int len = 2 * rows * cols;
    vector<int> allpix(len);
    
    // storing intensity values in a 1D vector
    for (c = 1; c < 3; c++) {
        // determining where to start 
        if (c == 1) { // top left corner
            i = 0;
            j = 0;
            k = 0;
            m = 1;
            d = 1;
            e = 0;
            f = cols - 1;
            g = rows - 1;
        }
        else if (c == 2) { // top right corner
            i = 0;
            j = cols - 1;
            k = rows * cols - 1;
            m = 1;
            d = -1;
            e = cols - 1;
            f = -1;
            g = -1;
        }
        // storing the corner value
        allpix[k] = intensity_sq[i][j];
        i++;
        k++;
        // storing up to when i reaches the last row
        while (1) {
            while (i >= 0 && j != f) {
                allpix[k] = intensity_sq[i][j];
                i--;
                j = j + d;
                k++;
            }
            j = e;
            m++;
            i = m;
            if (i == rows) {
                i--;
                m--;
                break;
            }
        }
        // storing for the diagonals after i has reached the last row
        j = j + d;
        n = j;
        while (1) {
            while (j != f && i != -1) {
                allpix[k] = intensity_sq[i][j];
                i--;
                j = j + d;
                k++;
            }
            i = m;
            n = n + d;
            j = n;
            if (j == f) {
                break;
            }
        }
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
vector<int> mat_jump(vector<vector<int>> intensity_mat) {
    // converting matrix to square matrix
    vector<vector<int>> intensity_sq = make_square(intensity_mat);
    // intializing values
    int i = 0, j = 0, k = 0;
    int rows = intensity_sq.size();
    int cols = intensity_sq.size();
    const int len = rows * cols;
    int m = rows - 1, n = cols - 1;
    int tb = 0, dirT = 0, dirB = 0;
    vector<int> allpix(len);
    
    // storing intensity values in a 1D vector
    // storing the two corners first
    allpix[k] = intensity_sq[i][j];
    i++;
    k++;
    allpix[k] = intensity_sq[m][n];
    m--;
    k++;
    // storing the rest
    while (k < len) {
        if (tb == 0) { // Get a pixel from the top half
            allpix[k] = intensity_sq[i][j];
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
            allpix[k] = intensity_sq[m][n];
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
            allpix[k] = intensity_sq[i][j];
            k++;
            allpix[k] = intensity_sq[j][i];
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
            tb = 2;
        }

    }
    return allpix;
}