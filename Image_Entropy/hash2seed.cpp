/* hash2seed.cpp:
    takes the 64 long hexidecimal hash and converts it to a 256 bit long seed in binary.
*/

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
/* Developer Created Libraries*/
#include "hash2seed.h"

using namespace std;

string hash2seed(string hash) {
	int i;
	string bits, seed;
	for (i = 0; i < hash.size(); i++) {
        switch (hash[i]) {
            case '0': 
                bits = "0000";
                break;
            case '1': 
                bits = "0001";
                break;
            case '2': 
                bits = "0010";
                break;
            case '3': 
                bits = "0011";
                break;
            case '4': 
                bits = "0100";
                break;
            case '5': 
                bits = "0101";
                break;
            case '6': 
                bits = "0110";
                break;
            case '7': 
                bits = "0111";
                break;
            case '8': 
                bits = "1000";
                break;
            case '9': 
                bits = "1001";
                break;
            case 'a': 
                bits = "1010";
                break;
            case 'b': 
                bits = "1011";
                break;
            case 'c': 
                bits = "1100";
                break;
            case 'd': 
                bits = "1101";
                break;
            case 'e': 
                bits = "1110";
                break;
            case 'f': 
                bits = "1111";
                break;
        }
		seed.append(bits);
	}
	return seed;
}