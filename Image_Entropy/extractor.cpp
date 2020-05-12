/* extractor.cpp:
    The functions in this file implement different extracting algorithms to help randomize the bitstrings.
*/

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
/* Developer Created Libraries*/
#include "extractor.h"
#include "tools.h"

using namespace std;

/* This function takes a random bitstring that was generated in gen_bitstrings() and stores
   it a 1024 bit long input into the SHA-2 hashing algorithm.
   The process to store bits in this bitstring is called a Von Neumman Extractor.
   If two successive bits match, no output is fed into the bitstring.
   If the bits differ, the value of the first bit is fed into the bitstring.
*/
string vn_extractor(vector<string> bitstrings) {
    int numStrings = bitstrings.size();
    int index;
    int k = 0, i = 0;
    string curstr, seed;
    cv::Point temp;
    while (k < 1024) {
        //index = get_random_index(numStrings);
        temp = getPQIndices(numStrings, numStrings);
        index = temp.x;
        curstr = bitstrings[index];
        while (i < 256 && k < 1024) {
            if (curstr[i] == curstr[i + 1]) {
                i = i + 2;
            }
            else if (curstr[i] != curstr[i + 1]) {
                seed += curstr[i];
                k++;
                i = i + 2;
            }
        }
        i = 0;
    }
    return seed;
}

/* This function takes a random bitstring that was generated in gen_bitstrings() and stores
   it a 1024 bit long input into the SHA-2 hashing algorithm.
   The process to store bits in this bitstring is a (developer designed) 
   modified version of the Von Neumman extractor called a XOR Extractor.
   If two successive bits match, a 0 is fed into the bitstring.
   If the bits differ, a 1 is fed into the bitstring.
*/
string xor_extractor(vector<string> bitstrings) {
    int numStrings = bitstrings.size();
    int index;
    int k = 0, i = 0;
    string curstr, seed;
    cv::Point temp;
    unsigned char a, b, c;
    while (k < 1024) {
        //index = get_random_index(numStrings);
        temp = getPQIndices(numStrings, numStrings);
        index = temp.x;
        curstr = bitstrings[index];
        while (i < 256 && k < 1024) {
            if (curstr[i] == curstr[i + 1]) {
                seed += '0';
                k++;
                i = i + 2;
            }
            else if (curstr[i] != curstr[i + 1]) {
                seed += '1';
                k++;
                i = i + 2;
            }
        }
        i = 0;
    }
    return seed;
}

/* This function takes outputs from the two above functions and XOR's them together.
*/
string extractor_blender(string seedVN, string seedXOR) {
    int k = 0, i = 0;
    string seed;
    while (k < 256) {
        if (seedVN[k] == seedXOR[k]) {
            seed += '0';
            k++;
        }
        else if (seedVN[k] != seedXOR[k]) {
            seed += '1';
            k++;
        }
    }
    return seed;
}
