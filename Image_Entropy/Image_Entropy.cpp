// Image_Entropy.cpp : This file contains the 'main' function. Program execution begins and ends there.

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
// MPIR
#include <mpirxx.h>

using namespace cv;
using namespace std;

struct bitstrings {
    std::vector <std::string> p, q;
};

/* Taking the intensity values of each pixel and storing it in a 2D matrix
*/
int** find_intensity(Mat I, int rows, int cols) {
    // intializing values
    unsigned char intensity;
    int** intensity_mat = 0;
    intensity_mat = new int* [rows];
    int i, j;

    // storing intensity values
    for (i = 0; i < rows; i++) {
        intensity_mat[i] = new int[cols];
        for (j = 0; j < cols; j++) {
            intensity = I.at<uchar>(i, j);
            intensity_mat[i][j] = int(intensity);
        }
    }
    
    return intensity_mat;
}

/* Converting 2D intensity matrix to 1D intensity vector for easier manipulation
   This implementation weaves through the 2D matrix row by row ergo the name snake.
*/
vector<int> mat_snake(int **intensity_mat, int rows, int cols) {
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

/* Takes the 1D intensity vector and alternates between storing 512 long bit strings in p&q.
   Outputting bit strings are stored in a struct of vectors.
   Each struct vector is N long depending on the size of the image.
*/
bitstrings gen_bitstrings(vector<int> allpix) {
    // intializing values
    bitstrings bitstrings;
    string pixel;
    int i = 0, k = 0, flag = 0, ovr;
    
    // finding arrays of p&q's
    while (i < allpix.size()) {
        // checking if p[k] needs to be initialized or not
        if (flag == 1) {
            bitstrings.p.push_back("");
            if (ovr - 1 == 0) { // 1 extra value
                bitstrings.p[k].insert(std::end(bitstrings.p[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                bitstrings.p[k].insert(std::end(bitstrings.p[k]), std::end(pixel) - ovr + 1, std::end(pixel));
            }
            flag = 0;
        }
        else if (flag == 0) {
            bitstrings.p.push_back(to_string(allpix[i]));
            i++;
        }
        // storing a p in a bitstring
        while (bitstrings.p[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size() - 1) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make p[k] longer than 512 take the
            // overage and put it into q[k]
            if ((bitstrings.p[k].size() + pixel.size()) > 512) {
                ovr = (bitstrings.p[k].size() + pixel.size()) - 512;
                bitstrings.p[k].insert(std::end(bitstrings.p[k]), std::begin(pixel), std::end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                bitstrings.p[k].insert(std::end(bitstrings.p[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }

        // preventing indexing outside of allpix
        if (i > allpix.size() - 1) {
            break;
        }

        // checking if q[k] needs to be initialized or not
        if (flag == 1) {
            bitstrings.q.push_back("");
            if (ovr - 1 == 0) { // 1 extra value
                bitstrings.q[k].insert(std::end(bitstrings.q[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                bitstrings.q[k].insert(std::end(bitstrings.q[k]), std::end(pixel) - ovr + 1, std::end(pixel));
            }
            flag = 0;
        }
        else if (flag == 0) {
            bitstrings.q.push_back(to_string(allpix[i]));
            i++;
        }
        // storing a q in a bitstring
        while (bitstrings.q[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size() - 1) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make q[k] longer than 512 take the
            // overage and put it into the next p[k]
            if ((bitstrings.q[k].size() + pixel.size()) > 512) {
                ovr = (bitstrings.q[k].size() + pixel.size()) - 512;
                bitstrings.q[k].insert(std::end(bitstrings.q[k]), std::begin(pixel), std::end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                bitstrings.q[k].insert(std::end(bitstrings.q[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }
        k++;
    }
    // Throwing away bit strings that aren't 512 long
    bitstrings.p.erase(bitstrings.p.begin() + k - 1);
    bitstrings.q.erase(bitstrings.q.begin() + k - 1);
    return bitstrings;
}

/* (TODO):
    - synchronize file paths
    - Design at least 2 more ways to divide up the intensity matrix and develop tests for them
    - pick source of data for choosing the bitstring that is actually used
    - break out functions into seperate files
    - start work on filters
*/
int main() {
	// Getting image
    Mat I = imread("Lena.bmp");
    int rows = I.rows;
    int cols = I.cols;
    
    // Storing intensity values of image
    int** intensity_mat = find_intensity(I, rows, cols);
        
    // Divding up the 2D intensity matrix and storing it in a 1D intensity vector
    // (TESTING) This is one implementation of breaking up the 2D matrix the goal will be to test at least two other implementations. 
    vector<int> allpix = mat_snake(intensity_mat, rows, cols);
    
    // Generating N p&q bitstrings from the 1D intensity vector
    bitstrings bitstrings = gen_bitstrings(allpix);

    // (NOTE) I think we will have to do all of the mpz_t type operations inside of main and not be able to pass through functions.
    // This probably means that we will not do too many operations on the mpz_t once it is in that form.
    // Might just want to keep the randomization strictly image processing based

    // Picking a random bitstring from the struct of vector strings for p&q
    // (NEED TO)  Pick a source of randomization that isn't the standard rand func
    int pSZ = bitstrings.p.size();
    int qSZ = bitstrings.q.size();
    srand(time(NULL));
    int pIdx = rand() % pSZ;
    int qIdx = rand() % qSZ;
    std::vector<char*> cstringsP, cstringsQ; // (NEED TO) Check if these actually need to be vectors or if you can just pull it out as a const char*
    cstringsP.reserve(pSZ);
    cstringsP.push_back(const_cast<char*>(bitstrings.p[pIdx].c_str()));
    cstringsQ.reserve(qSZ);
    cstringsQ.push_back(const_cast<char*>(bitstrings.q[qIdx].c_str()));
     
    // Converting bitstrings back to ints
    mpz_t pInt;
    mpz_t qInt;
    mpz_init(pInt);
    mpz_init(qInt);
    mpz_set_str(pInt, cstringsP[0], 10);
    mpz_set_str(qInt, cstringsQ[0], 10);


	return 0;
}