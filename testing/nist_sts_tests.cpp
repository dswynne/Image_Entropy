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
#include <fstream>
/* External Libraries: */
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
// NIST STS (Modified to work for our needs)
// Note: This testing project was just used to check that we could pass the the basic tests of the suite.
// If we were not passing it was easier to understand how to improve the generator with the code in this format.
// Instead of using the full suite. To test the generator against the full suite see documentation on how to run the full suite.
#include "nist_sts_tests.h"
#include "cephes.h" 

using namespace cv;
using namespace std;


constexpr auto ALPHA = 0.01;

string readBinaryDigitsInASCIIFormat()
{
	string epsilon;
	FILE* fp;
	int  numOfBitStreams = 1;
	int		i, j = 0, num_0s, num_1s, bitsRead, bit;
	fp = fopen("seeds4Testing.txt", "r");
	//fp = fopen("data.pi", "r");
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
	fclose(fp);
	printf("BITSREAD = %d 0s = %d 1s = %d\n", bitsRead, num_0s, num_1s);
	FILE* resultsFile;
	resultsFile = fopen("results.txt", "w");
	fprintf(resultsFile,"BITSREAD = %d 0s = %d 1s = %d\n", bitsRead, num_0s, num_1s);
	fclose(resultsFile);
	return epsilon;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
						  FREQUENCY  TEST
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
	// Writing output to test specific file
	FILE* freqFile;
	freqFile = fopen("frequency.txt", "w");
	fprintf(freqFile,"\t\t\t  FREQUENCY TEST:\n");
	fprintf(freqFile,"\t\t---------------------------------------------\n");
	fprintf(freqFile,"\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(freqFile,"\t\t---------------------------------------------\n");
	fprintf(freqFile,"The nth partial sum = % d\n", (int)sum);
	fprintf(freqFile,"S_n/n               = %f\n", sum / n);
	fprintf(freqFile, "\t\t---------------------------------------------\n");
	fprintf(freqFile,"%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
	fclose(freqFile);

	// Writing output to summary file
	FILE* resultsFile;
	resultsFile = fopen("results.txt", "a");
	fprintf(resultsFile, "FREQUENCY TEST:\n");
	fprintf(resultsFile, "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
	fclose(resultsFile);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
				LONGEST RUN OF ONES WITHIN A BLOCK TEST
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void LongestRunOfOnes(string epsilon)
{
	double			pval, chi2, pi[7];
	int				run, v_n_obs, N, i, j, K, M, V[7];
	unsigned int	nu[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int n = epsilon.size();
	FILE* lrFile;
	lrFile = fopen("longestRun.txt", "w");

	if (n < 128) {
		fprintf(lrFile,"\t\t\t  LONGEST RUNS OF ONES TEST\n");
		fprintf(lrFile,"\t\t---------------------------------------------\n");
		fprintf(lrFile,"\t\t   n=%d is too short\n", n);
		return;
	}
	if (n < 6272) {
		K = 3;
		M = 8;
		V[0] = 1; V[1] = 2; V[2] = 3; V[3] = 4;
		pi[0] = 0.21484375;
		pi[1] = 0.3671875;
		pi[2] = 0.23046875;
		pi[3] = 0.1875;
	}
	else if (n < 750000) {
		K = 5;
		M = 128;
		V[0] = 4; V[1] = 5; V[2] = 6; V[3] = 7; V[4] = 8; V[5] = 9;
		pi[0] = 0.1174035788;
		pi[1] = 0.242955959;
		pi[2] = 0.249363483;
		pi[3] = 0.17517706;
		pi[4] = 0.102701071;
		pi[5] = 0.112398847;
	}
	else {
		K = 6;
		M = 10000;
		V[0] = 10; V[1] = 11; V[2] = 12; V[3] = 13; V[4] = 14; V[5] = 15; V[6] = 16;
		pi[0] = 0.0882;
		pi[1] = 0.2092;
		pi[2] = 0.2483;
		pi[3] = 0.1933;
		pi[4] = 0.1208;
		pi[5] = 0.0675;
		pi[6] = 0.0727;
	}

	N = n / M;
	for (i = 0; i < N; i++) {
		v_n_obs = 0;
		run = 0;
		for (j = 0; j < M; j++) {
			if (epsilon[i * M + j] == '1') {
				run++;
				if (run > v_n_obs)
					v_n_obs = run;
			}
			else
				run = 0;
		}
		if (v_n_obs < V[0])
			nu[0]++;
		for (j = 0; j <= K; j++) {
			if (v_n_obs == V[j])
				nu[j]++;
		}
		if (v_n_obs > V[K])
			nu[K]++;
	}

	chi2 = 0.0;
	for (i = 0; i <= K; i++)
		chi2 += ((nu[i] - N * pi[i]) * (nu[i] - N * pi[i])) / (N * pi[i]);

	pval = cephes_igamc((double)(K / 2.0), chi2 / 2.0);

	fprintf(lrFile, "\t\t\t  LONGEST RUNS OF ONES TEST\n");
	fprintf(lrFile, "\t\t---------------------------------------------\n");
	fprintf(lrFile, "\t\tCOMPUTATIONAL INFORMATION:\n");
	fprintf(lrFile, "\t\t---------------------------------------------\n");
	fprintf(lrFile, "\t\t(a) N (# of substrings)  = %d\n", N);
	fprintf(lrFile, "\t\t(b) M (Substring Length) = %d\n", M);
	fprintf(lrFile, "\t\t(c) Chi^2                = %f\n", chi2);
	fprintf(lrFile, "\t\t---------------------------------------------\n");
	fprintf(lrFile, "\t\t      F R E Q U E N C Y\n");
	fprintf(lrFile, "\t\t---------------------------------------------\n");

	if (K == 3) {
		fprintf(lrFile, "\t\t  <=1     2     3    >=4   P-value  Assignment");
		fprintf(lrFile, "\n\t\t %3d %3d %3d  %3d ", nu[0], nu[1], nu[2], nu[3]);
	}
	else if (K == 5) {
		fprintf(lrFile, "\t\t<=4  5  6  7  8  >=9 P-value  Assignment");
		fprintf(lrFile, "\n\t\t %3d %3d %3d %3d %3d  %3d ", nu[0], nu[1], nu[2],
			nu[3], nu[4], nu[5]);
	}
	else {
		fprintf(lrFile, "\t\t<=10  11  12  13  14  15 >=16 P-value  Assignment");
		fprintf(lrFile, "\n\t\t %3d %3d %3d %3d %3d %3d  %3d ", nu[0], nu[1], nu[2],
			nu[3], nu[4], nu[5], nu[6]);
	}
	//if (isNegative(pval) || isGreaterThanOne(pval))
	if (pval < 0 || pval > 1)
		fprintf(lrFile, "WARNING:  P_VALUE IS OUT OF RANGE.\n");

	fprintf(lrFile, "%s\t\tp_value = %f\n\n", pval < ALPHA ? "FAILURE" : "SUCCESS", pval);
	//fprintf(lrFile, "%f\n", pval);
	fclose(lrFile);

	// Writing output to summary file
	FILE* resultsFile;
	resultsFile = fopen("results.txt", "a");
	fprintf(resultsFile, "LONGEST RUNS OF ONES TEST\n");
	fprintf(resultsFile, "%s\t\tp_value = %f\n\n", pval < ALPHA ? "FAILURE" : "SUCCESS", pval);
	fclose(resultsFile);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
							RUNS TEST
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 void Runs(string epsilon)
{
	int		S, k;
	double	pi, V, erfc_arg, p_value;
	int n = epsilon.size();
	FILE* runsFile;
	runsFile = fopen("runs.txt", "w");

	S = 0;
	for (k = 0; k < n; k++)
		if (epsilon[k] == '1')
			S++;
	pi = (double)S / (double)n;

	if (fabs(pi - 0.5) > (2.0 / sqrt(n))) {
		fprintf(runsFile, "\t\t\t\tRUNS TEST\n");
		fprintf(runsFile, "\t\t------------------------------------------\n");
		fprintf(runsFile, "\t\tPI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
		p_value = 0.0;
		fclose(runsFile);
		// Writing output to summary file
		FILE* resultsFile;
		resultsFile = fopen("results.txt", "w+");
		fprintf(resultsFile, "RUNS TEST\n");
		fprintf(resultsFile, "\t\tPI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
		fclose(resultsFile);
	}
	else {

		V = 1;
		for (k = 1; k < n; k++)
			if (epsilon[k] != epsilon[k - 1])
				V++;

		erfc_arg = fabs(V - 2.0 * n * pi * (1 - pi)) / (2.0 * pi * (1 - pi) * sqrt(2 * n));
		p_value = erfc(erfc_arg);

		fprintf(runsFile, "\t\t\t\tRUNS TEST\n");
		fprintf(runsFile, "\t\t------------------------------------------\n");
		fprintf(runsFile, "\t\tCOMPUTATIONAL INFORMATION:\n");
		fprintf(runsFile, "\t\t------------------------------------------\n");
		fprintf(runsFile, "\t\t(a) Pi                        = %f\n", pi);
		fprintf(runsFile, "\t\t(b) V_n_obs (Total # of runs) = %d\n", (int)V);
		fprintf(runsFile, "\t\t(c) V_n_obs - 2 n pi (1-pi)\n");
		fprintf(runsFile, "\t\t    -----------------------   = %f\n", erfc_arg);
		fprintf(runsFile, "\t\t      2 sqrt(2n) pi (1-pi)\n");
		fprintf(runsFile, "\t\t------------------------------------------\n");
		//if (isNegative(p_value) || isGreaterThanOne(p_value))
		if (p_value < 0 || p_value > 1)
			fprintf(runsFile, "WARNING:  P_VALUE IS OUT OF RANGE.\n");

		fprintf(runsFile, "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);// fflush(stats[TEST_RUNS]);
		fclose(runsFile);
		// Writing output to summary file
		FILE* resultsFile;
		resultsFile = fopen("results.txt", "a");
		fprintf(resultsFile, "RUNS TEST\n");
		fprintf(resultsFile, "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
		fclose(resultsFile);
	}

}

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
							BLOCK FREQUENCY TEST
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 void BlockFrequency(string epsilon) {
	 int		i, j, N, blockSum;
	 double	p_value, sum, pi, v, chi_squared;
	 
	 int n = epsilon.size();
	 int M = (.01*n)+1;


	 N = n / M; 		/* # OF SUBSTRING BLOCKS      */
	 sum = 0.0;

	 int intValue;
	 for (i = 0; i < N; i++) {
		 blockSum = 0;
		 for (j = 0; j < M; j++) {
			 intValue = epsilon[j + i * M] - '0';
			 blockSum += intValue;
		 }

		 pi = (double)blockSum / (double)M;
		 v = pi - 0.5;
		 sum += v * v;
	 }
	 chi_squared = 4.0 * M * sum;
	 p_value = cephes_igamc(N / 2.0, chi_squared / 2.0);
	 
	 FILE* bfFile;
	 bfFile = fopen("blockFrequency.txt", "w");
	 fprintf(bfFile, "\t\t\tBLOCK FREQUENCY TEST\n");
	 fprintf(bfFile, "\t\t---------------------------------------------\n");
	 fprintf(bfFile, "\t\tCOMPUTATIONAL INFORMATION:\n");
	 fprintf(bfFile, "\t\t---------------------------------------------\n");
	 fprintf(bfFile, "\t\t(a) Chi^2           = %f\n", chi_squared);
	 fprintf(bfFile, "\t\t(b) # of substrings = %d\n", N);
	 fprintf(bfFile, "\t\t(c) block length    = %d\n", M);
	 fprintf(bfFile, "\t\t(d) Note: %d bits were discarded.\n", n % M);
	 fprintf(bfFile, "\t\t---------------------------------------------\n");

	 fprintf(bfFile, "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value); //fflush(stats[TEST_BLOCK_FREQUENCY]);
	 fprintf(bfFile, "%f\n", p_value); //fflush(results[TEST_BLOCK_FREQUENCY]);
	 fclose(bfFile);
	 // Writing output to summary file
	 FILE* resultsFile;
	 resultsFile = fopen("results.txt", "a");
	 fprintf(resultsFile, "BLOCK FREQUENCY TEST\n");
	 fprintf(resultsFile, "%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value); //fflush(stats[TEST_BLOCK_FREQUENCY]);
	 fclose(resultsFile);
 }