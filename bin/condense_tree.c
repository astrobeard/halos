/* 
 * This file condenses all halos in a tree file to those that are only above 
 * some resolution limit. 
 * 
 * ARGV 
 * ==== 
 * 1) 		The name of the input tree file 
 * 2) 		The name of the output tree file 
 * 3) 		The minimum log10 of the halo mass in Msun 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "../halos.h" 

static unsigned short processor(FILE *halo_finder, FILE *secondary, FILE *out, 
	unsigned short dimension, double minlogm); 
static unsigned short write_tree_to_output_file(FILE *in, FILE *out); 
static HALO *next_present_day_halo(FILE *in, unsigned short dimension); 

/* 
 * This program works by opening the input file twice, using one filestream to 
 * read in the z = 0 halo information, and the next to then read in and 
 * subsequently write out to the output file if the halo at the final snapshot 
 * is above the resolution limit. 
 */ 
int main(int argc, char **argv) {

	if (argc != 4) {
		printf("Incorrect number of command line arguments. Expected: 3. "); 
		printf("Got: %d\n", argc - 1); 
		return 1; 
	} else {} 

	if (!strcmp(argv[1], argv[2])) {
		printf("Input and Output data files must not have the same name.\n"); 
		return 1; 
	} else {} 

	int dimension = file_dimension(argv[1]); 
	if (dimension == -1) {
		printf("Couldn't open input tree file: %s\n", argv[1]); 
		return 1; 
	} else {} 
	FILE *halo_finder = fopen(argv[1], "r"); 
	FILE *secondary = fopen(argv[1], "r"); 
	next_halo_in_tree(halo_finder); 
	next_halo_in_tree(secondary); 

	FILE *out = fopen(argv[2], "w"); 
	if (out == NULL) {
		printf("Couldn't open output tree file: %s\n", argv[2]); 
		return 1; 
	} else {} 

	double minlogm = atof(argv[3]); 
	unsigned long n = 0l; 
	do {
		if (processor(halo_finder, secondary, out, dimension, minlogm)) break; 
		n++; 
		printf("\rTrees processed: %ld\n", n); 
	} while (1); 
	fclose(halo_finder); 
	fclose(secondary); 
	fclose(out); 
	return 0; 

} 

/* 
 * Processes a single tree in a tree file and writes it to the output file if 
 * it is above the resolution limit. 
 * 
 * Parameters 
 * ========== 
 * halo_finder: 	The input stream used to find z = 0 halos 
 * secondary: 		The secondary input file reading in the whole tree after 
 * 					finding z = 0 hosts 
 * out: 			The output data stream 
 * dimension: 		The dimension of the input tree file 
 * minlogm: 		The specified minimum halo mass from the command line 
 * 
 * Returns 
 * ======= 
 * 0 if the program should continue reading the file, 1 at EOF 
 */ 
static unsigned short processor(FILE *halo_finder, FILE *secondary, FILE *out, 
	unsigned short dimension, double minlogm) {

	HALO *halo = next_present_day_halo(halo_finder, dimension); 
	if (halo != NULL) { 
		// printf("log10(mvir) = %.2f ", log10((*halo).mvir)); 
		if (log10((*halo).mvir) >= minlogm) { 
			// printf("writing....\n"); 
			write_tree_to_output_file(secondary, out); 
		} else {
			// printf("skipping....\n"); 
			next_halo_in_tree(secondary); /* skip this halo */ 
		} 
		/* move halo finder passed this tree */ 
		next_halo_in_tree(halo_finder); 
		halo_free(halo); 
		return 0; 
	} else {
		return 1; 
	} 

}

/* 
 * Write the tree information from a halo in the input file to the output file
 * 
 * Parameters 
 * ========== 
 * in: 		The filestream that is not reading in the halo information 
 * 
 * Returns 
 * ======= 
 * 0 on success, 1 on EOF 
 */ 
static unsigned short write_tree_to_output_file(FILE *in, FILE *out) {

	char *line = (char *) malloc (MAX_LINESIZE * sizeof(char)); 
	do {
		if (fgets(line, MAX_LINESIZE, in) == NULL) {
			free(line); 
			return 1; 
		} else {
			fprintf(out, "%s", line); 
		} 
	} while (!startswith(line, "#tree")); 
	free(line); 
	return 0; 

}

/* 
 * Finds the next halo in the tree at the present day snapshot 
 * 
 * Parameters 
 * ========== 
 * in: 			The input stream for finding the next z = 0 halo 
 * dimension: 	The dimensionality of the input file 
 * 
 * Returns 
 * ======= 
 * A halo object with the ID and virial masses assigned 
 */ 
static HALO *next_present_day_halo(FILE *in, unsigned short dimension) {

	HALO *halo = halo_initialize(); 
	double *line = read_line(in, dimension); 
	while (line[SCALE_COLUMN] != 1) {
		free(line); 
		line = read_line(in, dimension); 
		if (line == NULL) {
			free(line); 
			halo_free(halo); 
			return NULL; 
		} else {} 
	} 
	halo -> id = (unsigned long) line[ID_COLUMN]; 
	halo -> mvir = (long) line[MVIR_COLUMN]; 
	return halo; 

}



