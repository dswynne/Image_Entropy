// Image_Entropy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <gmp.h>
#include <mpir.h>

using namespace cv;
using namespace std;
//using mpfr::mpreal;

struct retVals {
    std::vector <std::string> p, q;
};

/* Finds arrays of strings of p&q. 
   Each string is 512 long.
   This implementation weaves through the 2D matrix row by row ergo the name snake
*/
retVals mat_snake(int temp[][256], int rows, int cols) {
    
    // converting 2D to 1D for easier manipulation
    int i, j;
    const int len = rows * cols;
    std::vector<int> allpix(len);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            allpix[i * cols + j] = temp[i][j];
        }
    }

    // finding arrays of p&q's
    retVals retVals;
    string pixel;
    int k = 0, flag = 0, ovr;
    i = 0;
    while (i < allpix.size()) { // (NEED TO) Throw away bit strings that are not 512 long at the end
        // checking if p[k] needs to be initialized or not
        if (flag == 1) {
            retVals.p.push_back("");
            if (ovr - 1 == 0) { // 1 extra value
                retVals.p[k].insert(std::end(retVals.p[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                retVals.p[k].insert(std::end(retVals.p[k]), std::end(pixel) - ovr + 1, std::end(pixel));
            }
            flag = 0;
        }
        else if (flag == 0) {
            retVals.p.push_back(to_string(allpix[i]));
            i++;
        }
        // storing a p in a bitstring
        while (retVals.p[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size() - 1) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make p[k] longer than 512 take the
            // overage and put it into q[k]
            if ((retVals.p[k].size() + pixel.size()) > 512) {
                ovr = (retVals.p[k].size() + pixel.size()) - 512;
                retVals.p[k].insert(std::end(retVals.p[k]), std::begin(pixel), std::end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                retVals.p[k].insert(std::end(retVals.p[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }

        // preventing indexing outside of allpix
        if (i > allpix.size() - 1) {
            break;
        }

        // checking if q[k] needs to be initialized or not
        if (flag == 1) {
            retVals.q.push_back("");
            if (ovr - 1 == 0) { // 1 extra value
                retVals.q[k].insert(std::end(retVals.q[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                retVals.q[k].insert(std::end(retVals.q[k]), std::end(pixel) - ovr + 1, std::end(pixel));
            }
            flag = 0;
        }
        else if (flag == 0) {
            retVals.q.push_back(to_string(allpix[i]));
            i++;
        }
        // storing a q in a bitstring
        while (retVals.q[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size() - 1) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make q[k] longer than 512 take the
            // overage and put it into the next p[k]
            if ((retVals.q[k].size() + pixel.size()) > 512) {
                ovr = (retVals.q[k].size() + pixel.size()) - 512;
                retVals.q[k].insert(std::end(retVals.q[k]), std::begin(pixel), std::end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                retVals.q[k].insert(std::end(retVals.q[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }
        k++;
    }
    // Throwing away bit strings that aren't 512 long
    retVals.p.erase(retVals.p.begin() + k-1);
    retVals.q.erase(retVals.q.begin() + k-1);
    return retVals;//check this
}

int main()
{
	Mat I = imread("Lena.bmp");
    unsigned char intensity;
    int rows = I.rows;
    int cols = I.cols;
    int temp[256][256];
    int i,j;
    // storing intensity values
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++){
            intensity = I.at<uchar>(i, j);
            temp[i][j] = int(intensity);
        }
    }
    
    // finding arrays of p&q's as strings
    // (TESTING) This is one implementation of breaking up the 2D matrix the goal will be to test at least two other implementations. 
    retVals retVals = mat_snake(temp, rows, cols);
    
    /*// This block of code was written before I knew we needed to use MIPR not GMP to work with long ints.
    // I am leaving the logic for now on the assumption that once I get MIPR setup it will use similair logic.
    // Since it is essentially a port of GMP to windows.

    // converting bitstrings back to ints
    unsigned long pSZ = retVals.p.size();
    unsigned long qSZ = retVals.q.size();
    mpz_t pInt;
    mpz_t qInt;
    __gmpz_init2(pInt,pSZ);
    __gmpz_init2(qInt,qSZ);
    //std::vector<char*> str(retVals.p.size());
    std::vector<char*> cstringsP, cstringsQ;
    cstringsP.reserve(retVals.p.size());
    for (i = 0; i < pSZ + 1; i++) {
        cstringsP.push_back(const_cast<char*>(retVals.p[i].c_str()));
        __gmpz_set_str(pInt, cstringsP[i], 10);
    }
    cstringsQ.reserve(retVals.q.size());
    for (i = 0; i < qSZ + 1; i++) {
        cstringsQ.push_back(const_cast<char*>(retVals.q[i].c_str()));
        __gmpz_set_str(qInt, cstringsQ[i], 10);
    }

    // averaging out the p&q's (will break this into a function later)
    mpz_t tot;
    __gmpz_init(tot);
    // for p
    __gmpz_set(tot,pInt[0]);
    for (i = 1; i < pSZ + 1; i++) {
        __gmpz_add(tot, tot, pInt[i]);
    }
    mpz_t pFinal,quo;
    __gmpz_init(pFinal);
    __gmpz_init(quo);
    __gmpz_set(pFinal, __gmpz_cdiv_q(quo,tot,pSZ));
    // for q
    __gmpz_set(tot, qInt[0]);
    for (i = 1; i < qSZ + 1; i++) {
        __gmpz_add(tot, tot, qInt[i]);
    }
    mpz_t qFinal;
    __gmpz_init(qFinal);
    __gmpz_set(qFinal, __gmpz_cdiv_q(quo, tot, qSZ));*/


	return 0;
}