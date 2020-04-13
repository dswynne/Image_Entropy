#pragma warning(disable : 4996).

/* Standard Libraries: */
#include <iostream>
#include <string> 
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "nist_sts_tests.h"

constexpr auto ALPHA = 0.01;

string readBinaryDigitsInASCIIFormat()
{
	string epsilon;
	FILE* fp;
	int  numOfBitStreams = 1;
	int		i, j = 0, num_0s, num_1s, bitsRead, bit;
	fp = fopen("output.txt", "r");
	for (i = 0; i < numOfBitStreams; i++) {
		num_0s = 0;
		num_1s = 0;
		bitsRead = 0;
		while (fscanf_s(fp, "%1d", &bit) != EOF) {
			bitsRead++;
			if (bit == 0)
				num_0s++;
			else
				num_1s++;
			epsilon.append(to_string(bit));
			j++;
		}
	}
	printf("BITSREAD = %d 0s = %d 1s = %d\n", bitsRead, num_0s, num_1s);
	fclose(fp);
	return epsilon;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
						  F R E Q U E N C Y  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Frequency(string epsilon)
{
	int		i, bit;
	double	f, s_obs, p_value, sum, sqrt2 = 1.41421356237309504880;
	sum = 0.0;
	int n = epsilon.size();
	for (i = 0; i < n; i++) {
		bit = epsilon[i] - '0';
		sum += 2 * bit - 1;
	}

	s_obs = fabs(sum) / sqrt(n);
	f = s_obs / sqrt2;
	p_value = erfc(f);
	printf("FREQUENCY TEST:\n");
	printf("The nth partial sum = % d\n", (int)sum);
	printf("S_n/n               = %f\n", sum / n);
	printf("%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
}