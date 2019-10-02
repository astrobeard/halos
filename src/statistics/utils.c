/* 
 * This file implements utility functions for statistical subroutines 
 */ 

#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include "utils.h" 

/* 
 * Obtain a binspace as a double pointer 
 * 
 * Parameters 
 * ========== 
 * start: 		The minimum value of the binspace 
 * stop: 		The maximum value of the binspace 
 * n_bins: 		The number of bins to generate 
 * 
 * Returns 
 * ======= 
 * [start, start + dx, ... , stop - dx, stop] (length: n_bins + 1) 
 * 
 * header: utils.h 
 */ 
extern double *binspace(double start, double stop, unsigned long n_bins) { 

	/* The output array will be of length n_bins + 1 */ 
	double *arr = (double *) malloc ((n_bins + 1l) * sizeof(double)); 
	double dx = (stop - start) / n_bins; /* stepsize */ 

	unsigned long i; 
	for (i = 0l; i <= n_bins; i++) { 
		arr[i] = start + i * dx; 
	} 
	return arr; 

} 

/* 
 * Determine the bin number of a test value in a given binspace 
 * 
 * Parameters 
 * ========== 
 * test: 		The test value 
 * arr: 		A pointer to the binspace. Assumed to be sorted least to 
 * 				greatest. 
 * n_bins: 		The number of bins in the binspace. This should always be one 
 * 				less than the number of elements in array arr, as in 
 * 				arr[n_bins] is expected to be defined. 
 * 
 * Returns 
 * ======= 
 * The bin number of the test value; -1 if not in the range of the binspace 
 * 
 * header: utils.h 
 */ 
extern long get_bin_number(double test, double *arr, unsigned long n_bins) {

	unsigned long i; 
	for (i = 0l; i < n_bins; i++) {
		if (arr[i] <= test && test <= arr[i + 1l]) return (signed) i; 
	} 
	return -1; 

} 

/* 
 * Convert a distribution to a probability density function (PDF). 
 * 
 * Parameters 
 * ========== 
 * hist: 		The counts on a given binspace 
 * binspace: 	The binspace itself. Assumed to be sorted least to greatest. 
 * n_bins: 		The number of bins on the binspace. Should always be one less 
 * 				than the number of elements in the binspace array, as in 
 * 				binspace[n_bins] is expected to be defined. 
 * 
 * Returns 
 * ======= 
 * A normalized copy of hist, such that the integral over its extent is equal 
 * to 1. 
 * 
 * header: utils.h 
 */ 
extern double *convert_to_PDF(double *hist, double *binspace, 
	unsigned long n_bins) { 

	/* 
	 * Integrate numerically via iterative sum. This is as good of 
	 * resolution to the actual integral over the distribution given the 
	 * information passed to this function 
	 */ 
	unsigned long i; 
	double intgrl = 0, *pdf = (double *) malloc (n_bins * sizeof(double)); 
	for (i = 0l; i < n_bins; i++) {
		intgrl += hist[i] * (binspace[i + 1l] - binspace[i]); 
	} 
	if (intgrl == 0) {
		free(pdf); 
		return NULL; 
	} else {
		for (i = 0l; i < n_bins; i++) {
			pdf[i] = hist[i] / intgrl; 
		} 
		return pdf; 
	}

}

