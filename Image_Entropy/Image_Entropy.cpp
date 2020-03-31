// Image_Entropy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <mpir.h>


using namespace cv;
using namespace std;

int main()
{
	Mat I = imread("Lena.bmp");
    //Scalar intensity = 0;
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

    // converting 2D to 1D for easier manipulation
    const int len = rows * cols;
    std::vector<int> allpix(len);
    for (i = 0; i < rows; i++){
        for (j = 0; j < cols; j++){
            allpix[i * cols + j] = temp[i][j];
        }
    }
    /* finding arrays of p&q's
    current implementation is to alternate between storing p & q */
    std::vector <std::string> p, q;
    string pixel;
    int k = 0, flag = 0, ovr;
    i = 0;
    
    while (i < allpix.size() + 1) { // (NEED TO) Throw away bit strings that are not 512 long at the end
        // checking if p[k] needs to be initialized or not
        if (flag == 1) {
            flag = 0;
        }
        else if(flag == 0) {
            p.push_back(to_string(allpix[i])); // CORRECT LINE I THINK
            //p[k] = std::to_string(allpix[i]);
            i++;
        }
        // storing a p in a bitstring
        while (p[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size()) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make p[k] longer than 512 take the
            // overage and put it into q[k]
            if ((p[k].size() + pixel.size()) > 512) {
                ovr = (p[k].size() + pixel.size()) - 512;
                p[k].insert(std::end(p[k]), std::begin(pixel), std::end(pixel)-ovr);
                q[k].insert(std::end(q[k]), std::end(pixel)-ovr+1, std::end(pixel));
                flag = 1;
                i++;
            }
            else {
                p[k].insert(std::end(p[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }

        // preventing indexing outside of allpix
        if (i > allpix.size()) {
            break;
        }

        // checking if q[k] needs to be initialized or not
        if (flag == 1) {
            flag = 0;
        }
        else if (flag == 0) {
            q.push_back(to_string(allpix[i])); // CORRECT LINE I THINK
            //q[k] = std::to_string(allpix[i]);
            i++;
        }
        // storing a q in a bitstring
        while (q[k].size() < 512) {
            // preventing indexing outside of allpix
            if (i > allpix.size()) {
                break;
            }
            // converting current pixel to string
            pixel = to_string(allpix[i]);
            // if the current pixel will make q[k] longer than 512 take the
            // overage and put it into the next p[k]
            if ((q[k].size() + pixel.size()) > 512) {
                ovr = (q[k].size() + pixel.size()) - 512;
                q[k].insert(std::end(q[k]), std::begin(pixel), std::end(pixel) - ovr);
                p[k+1].insert(std::end(p[k+1]), std::end(pixel) - ovr + 1, std::end(pixel));
                flag = 1;
                i++;
            }
            else {
                q[k].insert(std::end(q[k]), std::begin(pixel), std::end(pixel));
                i++;
            }
        }
    }
    
    // This block of code was written before I knew we needed to use MIPR not GMP to work with long ints.
    // I am leaving the logic for now on the assumption that once I get MIPR setup it will use similair logic.
    // Since it is essentially a port of GMP to windows.

    /*// converting bitstrings back to ints
    unsigned long pSZ = p.size();
    unsigned long qSZ = q.size();
    mpz_t pInt;
    mpz_t qInt;
    mpz_init (pInt,pSZ);
    mpz_init (qInt,qSZ);
    for (i = 0; i < pSZ + 1; i++) {
        mpz_set_str (pInt[i], stoi(p[i]);
    }
    for (i = 0; i < qSZ + 1; i++) {
        mpz_set_str (qInt[i], stoi(q[i]);
    }

    // averaging out the p&q's (will break this into a function later)
    mpz_t tot;
    mpz_init(tot);
    // for p
    mpz_set(tot,pInt[0]);
    for (i = 1; i < pSZ + 1; i++) {
        mpz_add(tot, tot, pInt[i]);
    }
    mpz_t pFinal,qou;
    mpz_init(pFinal);
    mpz_init(quo);
    mpz_set(pFinal, mpz_cdiv_q(quo,tot,pSZ));
    // for q
    mpz_set(tot, qInt[0]);
    for (i = 1; i < qSZ + 1; i++) {
        mpz_add(tot, tot, qInt[i]);
    }
    mpz_t qFinal;
    mpz_init(qFinal);
    mpz_set(qFinal, mpz_cdiv_q(quo, tot, qSZ));*/


	return 0;
}