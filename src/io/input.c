/* 
 * This file implements all input routines for the halos package 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <ctype.h> 
#include "input.h" 

/* 
 * Open a halo catalogue's associated file 
 * 
 * Parameters 
 * ========== 
 * catalogue: 		A pointer to the catalogue object 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on failure 
 * 
 * header: input.h 
 */ 
extern unsigned short catalogue_open_file(CATALOGUE *catalogue) {

	catalogue -> src_file = fopen((*catalogue).src_file_name, "r"); 
	return (*catalogue).src_file == NULL; 

} 

/* 
 * Close the input stream from a halo catalogue's associated file 
 * 
 * Parameters 
 * ========== 
 * catalogue: 		A pointer to the catalogue object 
 * 
 * Returns 
 * ======= 
 * 0 on success, EOF on failure 
 * 
 * header: input.h 
 */ 
extern unsigned short catalogue_close_file(CATALOGUE *catalogue) {

	return fclose(catalogue -> src_file); 

} 

/* 
 * Takes a filestream for a halo tree and moves the reader to the next 
 * tree in the file. 
 * 
 * Parameters 
 * ========== 
 * tree: 		The input file stream for the tree 
 * 
 * Returns 
 * ======= 
 * 1 at end of file, 0 on success 
 * 
 * header: input.h 
 */ 
extern unsigned short next_halo_in_tree(FILE *tree) {

	char *line = (char *) malloc (MAX_LINESIZE * sizeof(char)); 
	do {
		if (fgets(line, MAX_LINESIZE, tree) == NULL) {
			free(line); 
			return 1; 
		} else {} 
	} while (!startswith(line, "#tree")); 
	free(line); 
	return 0; 

} 

/* 
 * Determines if a given string starts with some test string 
 * 
 * Parameters 
 * ========== 
 * str: 		The string to test 
 * test: 		The test string 
 * 
 * Returns 
 * ======= 
 * 1 if the beginning of the string str is identical to test, 0 if not 
 * 
 * header: input.h 
 */ 
extern unsigned short startswith(const char *str, const char *test) {

	unsigned long i; 
	for (i = 0l; i < strlen(test); i++) {
		if (str[i] != test[i]) return 0; 
	} 
	return 1; 

} 

/* 
 * Determine the length of the header at the top of a data file assuming all 
 * header lines begin with #. 
 * 
 * Parameters 
 * ========== 
 * file: 	The name of the file 
 * 
 * Returns 
 * ======= 
 * The length of the header; -1 on failure to read from the file. 
 * 
 * header: input.h 
 */ 
extern int header_length(char *file) {

	/* Open the file and check for error opening the file */ 
	FILE *in = fopen(file, "r"); 
	if (in == NULL) return -1; 

	/* Store a line in memory, check for error reading the first line */  
	char *line = (char *) malloc (MAX_LINESIZE * sizeof(char)); 
	if (fgets(line, MAX_LINESIZE, in) == NULL) { 
		fclose(in); 
		free(line); 
		return -1; 
	} else {} 

	/* Add up the number of lines at the beginning of file that start with # */ 
	int n = 0; 
	while (line[0] == '#') { 
		n++; 
		if (fgets(line, MAX_LINESIZE, in) == NULL) {
			fclose(in); 
			free(line); 
			return -1; 
		} else {
			continue; 
		} 
	} 

	fclose(in); 
	free(line); 
	return n; 

} 

/* 
 * Determine the dimensionality of a data file off of the first line passed the 
 * header, assuming the header is commented out with '#'. 
 * 
 * Parameters 
 * ========== 
 * file: 		The file to determine the dimensionality of 
 * 
 * Returns 
 * ======= 
 * The number of quantities on one line of the file. -1 on failure to read 
 * from the file 
 * 
 * header: input.h 
 */ 
extern int file_dimension(char *file) {

	/* Need to read past header first, find out how many lines that is */ 
	int hlen = header_length(file); 
	if (hlen == -1) return -1; 		/* error checking */ 

	FILE *in = fopen(file, "r"); 
	if (in == NULL) return -1; 		/* error checking */ 

	/* 
	 * Store a line in memory, read passed the header. 
	 * After the header, tree files have the number of trees in the file, then 
	 * a line of the format #tree [HALO ID]. hlists have no such feature, and 
	 * none of the files I produce have such a feature. All cases can be 
	 * taken care of by reading and extra 2 lines passed the header. 
	 */ 
	int i; 
	char *line = (char *) malloc (MAX_LINESIZE * sizeof(char)); 
	for (i = 0; i <= hlen + 2; i++) {
		if (fgets(line, MAX_LINESIZE, in) == NULL) { 
			fclose(in); 
			free(line); 
			return -1; 				/* error checking */ 
		} else {
			continue; 
		} 
	} 

	/* 
	 * For any character in the line that is not whitespace, if the following 
	 * character is whitespace, increment the dimensionality. 
	 */ 
	int dimension = 0; 
	unsigned int j; 
	for (j = 0; j < strlen(line) - 1; j++) { 
		if (isspace(line[j + 1]) && !isspace(line[j])) {
			dimension++; 
		} else {
			continue; 
		} 
	} 
	fclose(in); 
	free(line); 
	return dimension; 

} 

/* 
 * Read a line of data from a file of given dimension from disk memory 
 * 
 * Parameters 
 * ========== 
 * input: 		The input filestream 
 * dimension: 	The dimensionality of the file 
 * 
 * Returns 
 * ======= 
 * The next line of data from wherever the input stream is. NULL on EOF 
 * 
 * header: input.h 
 */ 
extern double *read_line(FILE *input, unsigned int dimension) {

	double *arr = (double *) malloc (dimension * sizeof(double)); 
	unsigned int i; 
	for (i = 0; i < dimension; i++) {
		if (!fscanf(input, "%lf", &arr[i])) {
			free(arr); 
			return NULL; 
		} else {} 
	} 
	return arr; 

}



