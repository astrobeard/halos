/* 
 * This script reads in a halo tree, then writes out the change in mass and 
 * change in spin between the two most recent snapshots. 
 * 
 * ARGV 
 * ==== 
 * 1) 	The name of the input tree file 
 * 2) 	The name of the output file 
 * 3) 	The dimensionality of the tree file 
 * 4) 	The minimum log10 halo mass 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include <math.h> 
#include "../halos.h" 

static unsigned short processor(FILE *tree, FILE *out, 
	const unsigned short dimension, double minlogm); 
static void write_halo(FILE *out, HALO *root, HALO *progenitor); 
static HALO *root(FILE *tree, const unsigned short dimension); 
static FILE *open_tree_file(char *name); 
static HALO *readline(FILE *tree, const unsigned short dimension); 

int main(int argc, char **argv) {

	if (argc != 5) {
		printf("Expected 4 command line arguments. Got: %d\n", argc - 1); 
		return 1; 
	} else {} 
	FILE *tree = open_tree_file(argv[1]); 
	if (tree == NULL) {
		return 1; 
	} else {} 
	FILE *out = fopen(argv[2], "w"); 
	if (out == NULL) {
		fclose(tree); 
		return 1; 
	} else {} 
	if (next_halo_in_tree(tree)) {
		fclose(tree); 
		fclose(out); 
		return 1; 
	} else {} 

	printf("Processing: %s....\n", argv[1]); 
	do {
		if (processor(tree, out, atoi(argv[3]), atof(argv[4]))) break; 
	} while (1); 
	return 0; 

} 

static unsigned short processor(FILE *tree, FILE *out, 
	const unsigned short dimension, double minlogm) {

	HALO *root = readline(tree, dimension); 
	HALO *progenitor; 
	do { 
		/* 
		 * Read until it reaches the progenitor whose descendant ID matches 
		 * the z = 0 halo 
		 */ 
		progenitor = readline(tree, dimension); 
		if (progenitor == NULL) return 1; /* no progenitor */ 
		if ((*progenitor).desc_id != (*root).id) halo_free(progenitor); 
	} while (progenitor == NULL); 

	while (!(*progenitor).mmp) { 
		/* keep reading until it reaches the most massive progenitor */ 
		halo_free(progenitor); 
		progenitor = readline(tree, dimension); 
	}

	if (log10((*root).mvir) > minlogm) write_halo(out, root, progenitor); 
	halo_free(root); 
	halo_free(progenitor); 
	return next_halo_in_tree(tree); 

} 

static void write_halo(FILE *out, HALO *root, HALO *progenitor) {

	fprintf(out, "%ld\t", (*root).id); 
	fprintf(out, "%ld\t", (*root).pid); 
	fprintf(out, "%.5e\t", (*root).mvir); 
	fprintf(out, "%.5e\t", (*root).mvir - (*progenitor).mvir); 
	fprintf(out, "%.5e\t", (*root).rvir / (*root).rs); 
	fprintf(out, "%.5e\t", (*root).rvir / (*root).rs - 
		(*progenitor).rvir / (*progenitor).rs); 
	fprintf(out, "%.5e\t", (*root).b_to_a); 
	fprintf(out, "%.5e\t", (*root).b_to_a - (*progenitor).b_to_a); 
	fprintf(out, "%.5e\t", (*root).c_to_a); 
	fprintf(out, "%.5e\t", (*root).c_to_a - (*progenitor).c_to_a); 
	fprintf(out, "%.5e\t", (*root).spin); 
	fprintf(out, "%.5e\t", (*root).spin - (*progenitor).spin); 
	fprintf(out, "%.5e\t", (*root).spin_bullock); 
	fprintf(out, "%.5e\t", (*root).spin_bullock - (*progenitor).spin_bullock); 
	fprintf(out, "\n"); 

}

/* 
 * Reads in the first halo in a tree 
 * 
 * Parameters 
 * ========== 
 * tree: 		The tree input filestream 
 * dimension: 	The dimensionality of the tree file 
 * 
 * Returns 
 * ======= 
 * The halo object corresponding to the z = 0 halo 
 */ 
static HALO *root(FILE *tree, const unsigned short dimension) {

	return readline(tree, dimension); 

}

/* 
 * Opens the filestream for the tree file and returns a pointer to it 
 * 
 * Parameters 
 * ========== 
 * name: 		The name of the file 
 */ 
static FILE *open_tree_file(char *name) {

	return fopen(name, "r"); 

}

/* 
 * Read in the halo object corresponding to a given line of the tree file 
 * bookkeeping the quantities that are relevant for this analysis. 
 * 
 * Parameters 
 * ========== 
 * tree: 		The filestream for the tree data 
 * dimension: 	The dimensionality of the tree file 
 * 
 * Returns 
 * ======= 
 * The halo object corresponding to that line of the data. NULL on failure to 
 * read from the file, or EOF 
 */ 
static HALO *readline(FILE *tree, const unsigned short dimension) {

	HALO *halo = halo_initialize(); 
	unsigned short i; 
	double dummy; 
	for (i = 0; i < dimension; i++) {
		if (!fscanf(tree, "%lf", &dummy)) {
			halo_free(halo); 
			return NULL; 
		} else {} 

		switch(i) {
			case SCALE_COLUMN: 
				halo -> scale = dummy; 
				break; 
			case ID_COLUMN: 
				halo -> id = (unsigned long) dummy; 
				break; 
			case DESC_ID_COLUMN: 
				halo -> desc_id = (long) dummy; 
				break; 
			case PID_COLUMN: 
				halo -> pid = (long) dummy; 
				break; 
			case MVIR_COLUMN: 
				halo -> mvir = dummy; 
				break; 
			case SPIN_COLUMN: 
				halo -> spin = dummy; 
				break; 
			case SPIN_BULLOCK_COLUMN: 
				halo -> spin_bullock = dummy; 
				break; 
			case RS_COLUMN: 
				halo -> rs = dummy; 
				break; 
			case RVIR_COLUMN: 
				halo -> rvir = dummy; 
				break; 
			case B_TO_A_COLUMN: 
				halo -> b_to_a = dummy; 
				break; 
			case C_TO_A_COLUMN: 
				halo -> c_to_a = dummy; 
				break; 
			case MMP_COLUMN: 
				halo -> mmp = (unsigned short) dummy; 
				break; 
			default: 
				break; 

		} 

	} 
	return halo; 

} 
