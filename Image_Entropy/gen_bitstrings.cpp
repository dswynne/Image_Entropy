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

using namespace std;

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

vector<string> gen_bitstrings_new(vector<int> allpix) {
    int i = 0, k = 0, n = 0;
    vector<string> bitstrings;
    string btstr;

    // finding 32 byte bitstrings
    while (i+32 < allpix.size()) {
        bitstrings.push_back("");
        for (k = i; k < i+32; k++) {
            btstr = bitset<8>(allpix[k]).to_string();
            bitstrings[n].insert(end(bitstrings[n]), begin(btstr), end(btstr));
        }
        i = k + 1;
        n++;
    }
    return bitstrings;
}