
#ifndef UTILS_H 
#define UTILS_H 

#ifdef __cplusplus 
extern "C" {
#endif /* __cplusplus */ 

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
 * source: utils.c 
 */ 
extern double *binspace(double start, double stop, unsigned long n_bins); 

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
extern long get_bin_number(double test, double *arr, unsigned long n_bins); 

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
 * source: utils.h 
 */ 
extern double *convert_to_PDF(double *hist, double *binspace, 
	unsigned long n_bins); 

#ifdef __cplusplus 
}
#endif /* __cplusplus */ 

#endif /* UTILS_H */ 

