/* gen_bitstrings.cpp:
   All the functions in this file take a 1D intensity vector and convert it into 512 long bitstrings.
   Each function uses a different amount of bits from each pixel of the intensity vector. 
*/

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
/* Developer Created Libraries*/
#include "gen_bitstrings.h"
#include "tools.h"

using namespace std;

/* This function takes the 1D intensity array and converts each value to its 8 bit binary representation.
   It then scrambles the binary value.
   These binary values are then appended into bitstrings 256 bits long each.
*/
vector<string> gen_bitstrings_whole_pixel(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr, temp;
    // finding 32 byte bitstrings
    while (i+32 < allpix.size()) {
        bitstrings.push_back("");
        for (k = i; k < i+32; k++) {
            btstr = bitset<8>(allpix[k]).to_string();
            // scrambiling the bits to further randomize the data
            temp.append(btstr.begin(), btstr.begin() + 2);      // 2^7 & 2^6
            temp.append(btstr.begin() + 4, btstr.begin() + 6);  // 2^3 & 2^2
            temp.append(btstr.begin() + 2, btstr.begin() + 4);  // 2^5 & 2^4
            temp.append(btstr.begin() + 6, btstr.end());        // 2^1 & 2^0

            bitstrings[n].insert(end(bitstrings[n]), begin(temp), end(temp));
            temp = "";
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}

/* This function takes the 1D intensity array and outputs...
        - 1 if the intensity value is between 65 & 128 or 193 & 255
        - 0 if the intensity value is between 0 & 64 or 129 & 192
   These binary values are then appended into bitstrings 256 bits long each.
*/
vector<string> gen_bitstrings_HL(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr;
    // finding 32 byte bitstrings
    while (i + 256 < allpix.size()) {
        bitstrings.push_back("");
        for (k = i; k < i + 256; k++) {
            if (allpix[k] <= 64 || (allpix[k] > 128 && allpix[k] <=192)) {
                bitstrings[n].append("0");
            }
            else if ((allpix[k] > 64 && allpix[k] <=128) || (allpix[k] > 192)) {
                bitstrings[n].append("1");
            }
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}

/* This function takes the 1D intensity array and converts each value to its 8 bit binary representation.
   It only takes the LSB of this 8 bit output.
   These binary values are then appended into bitstrings 256 bits long each.
*/
vector<string> gen_bitstrings_LSB(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr;
    // finding 32 byte bitstrings
    while (i + 256 < allpix.size()) {
        bitstrings.push_back("");
        for (k = i; k < i + 256; k++) {
            bitstrings[n].append(bitset<1>(allpix[k]).to_string());
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}

/* This function takes the 1D intensity array and converts each value to its 8 bit binary representation.
   It then takes one bit from the 8 bit value. 
   These binary values are then appended into bitstrings 256 bits long each.
*/
vector<string> gen_bitstrings_bitshift(vector<int> allpix) {
    int i = 0, k = 0, n = 0, m = 7;
    vector<string> bitstrings;
    string btstr;
    // finding 32 byte bitstrings
    while (i + 256 < allpix.size()) {
        bitstrings.push_back("");
        for (k = i; k < i + 256; k++) {
            btstr = bitset<8>(allpix[k]).to_string();
            bitstrings[n].push_back(btstr[m]);
            m--;
            if (m < 0) {
                m = 7;
            }
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}

