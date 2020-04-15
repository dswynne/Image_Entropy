/* gen_bitstrings.cpp:
   Takes the 1D intensity vector and alternates between storing 512 long bit strings in p&q.
   Outputting bit strings are stored in a struct of vectors.
   Each struct vector is N long depending on the size of the image.
*/

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
/* Developer Created Libraries*/
#include "main.h"
#include "tools.h"

using namespace std;

/* THIS IS AN OBSOLETE FUNCTION AND WILL BE REMOVED SOON */
/* This function takes the 1D intensity array and generates strigns of decimals 512 long for p&q */
bitstrings gen_bitstrings_old(vector<int> allpix) {
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
                bitstrings.p[k].insert(end(bitstrings.p[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                bitstrings.p[k].insert(end(bitstrings.p[k]), end(pixel) - ovr + 1, end(pixel));
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
                bitstrings.p[k].insert(end(bitstrings.p[k]), begin(pixel), end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                bitstrings.p[k].insert(end(bitstrings.p[k]), begin(pixel), end(pixel));
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
                bitstrings.q[k].insert(end(bitstrings.q[k]), pixel[pixel.size() - 1]);
            }
            else { // 2 extra values
                bitstrings.q[k].insert(end(bitstrings.q[k]),end(pixel) - ovr + 1, end(pixel));
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
                bitstrings.q[k].insert(end(bitstrings.q[k]), begin(pixel), end(pixel) - ovr);
                flag = 1;
                i++;
            }
            else {
                bitstrings.q[k].insert(end(bitstrings.q[k]), begin(pixel), end(pixel));
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

/* This function takes the 1D intensity array and converts each value to its 8 bit binary representation.
   These binary values are then appended into bitstrings 256 bits long each.
*/
vector<string> gen_bitstrings(vector<int> allpix) {
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
            //bitstrings[n].insert(end(bitstrings[n]), begin(btstr), end(btstr));
            bitstrings[n].insert(end(bitstrings[n]), begin(temp), end(temp));
            temp = "";
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}

vector<string> gen_bitstrings_HL(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr, temp;
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

vector<string> gen_bitstrings_LSB(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr, temp;
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

vector<string> gen_bitstrings_bitshift(vector<int> allpix) {
    int i = 0, k = 0, n = 0, m = 7;
    vector<string> bitstrings;
    string btstr, temp;
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

/* This function takes a random bitstring that was generated in gen_bitstrings() and stores it into the final seed.
   The process to store bits in this seed is called a Von Neumman Extractor.
   If two successive bits match, no output is fed into the seed. 
   If the bits differ, the value of the first bit is fed into the seed.
*/
string vn_extractor(vector<string> bitstrings) {
    int numStrings = bitstrings.size();
    int index; 
    int k = 0, i = 0;
    string curstr, seed;
    cv::Point temp;
    while (k < 256) {
        //index = get_random_index(numStrings);
        temp = getPQIndices(numStrings, numStrings);
        index = temp.x;
        curstr = bitstrings[index];
        while (i < 256 && k < 256) {
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

string xor_extractor(vector<string> bitstrings) {
    int numStrings = bitstrings.size();
    int index;
    int k = 0, i = 0;
    string curstr, seed;
    cv::Point temp;
    unsigned char a, b, c;
    while (k < 256) {
        //index = get_random_index(numStrings);
        temp = getPQIndices(numStrings, numStrings);
        index = temp.x;
        curstr = bitstrings[index];
        while (i < 256 && k < 256) {
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

string vn_extractor_recursive(vector<string> bitstrings) {
    int k = 0, i = 0;
    string curstr, seed;
    while (k < 256) {
        curstr = vn_extractor(bitstrings);
        while (i < 256 && k < 256) {
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