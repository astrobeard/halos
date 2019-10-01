/* 
 * This script reads in a halo tree, then writes out the change in mass and 
 * change in spin between the two most recent snapshots. 
 * 
 * ARGV 
 * ==== 
 * 1) 	The name of the input tree file 
 * 2) 	The name of the output file 
 * 3) 	The dimensionality of the tree file 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "../halos.h" 

static unsigned short processor(FILE *tree, FILE *out, 
	const unsigned short dimension); 
static void write_halo(FILE *out, HALO *root, HALO *progenitor); 
static HALO *root(FILE *tree, const unsigned short dimension); 
static FILE *open_tree_file(char *name); 
static HALO *readline(FILE *tree, const unsigned short dimension); 

int main(int argc, char **argv) {

	if (argc != 4) {
		printf("Expected 3 command line arguments. Got: %d\n", argc); 
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
		if (processor(tree, out, atoi(argv[3]))) break; 
	} while (1); 
	return 0; 

} 

static unsigned short processor(FILE *tree, FILE *out, 
	const unsigned short dimension) {

	HALO *root = readline(tree, dimension); 
	HALO *progenitor; 
	do {
		progenitor = readline(tree, dimension); 
		if (progenitor == NULL) return 1; /* no progenitor */ 
		if ((*progenitor).desc_id != (*root).id) halo_free(progenitor); 
	} while (progenitor == NULL); 

	write_halo(out, root, progenitor); 
	halo_free(root); 
	halo_free(progenitor); 
	return next_halo_in_tree(tree); 

} 

static void write_halo(FILE *out, HALO *root, HALO *progenitor) {

	fprintf(out, "%ld\t", (*root).id); 
	fprintf(out, "%ld\t", (*root).pid); 
	fprintf(out, "%.5e\t", (*root).sam_mvir - (*progenitor).sam_mvir); 
	fprintf(out, "%.5e\t", (*root).mvir - (*progenitor).mvir); 
	fprintf(out, "%.5e\t", (*root).mmvir_all - (*progenitor).mmvir_all); 
	fprintf(out, "%.5e\t", (*root).m200b - (*progenitor).m200b); 
	fprintf(out, "%.5e\t", (*root).m200c - (*progenitor).m200c); 
	fprintf(out, "%.5e\t", (*root).m500c - (*progenitor).m500c); 
	fprintf(out, "%.5e\t", (*root).m2500c - (*progenitor).m2500c); 
	fprintf(out, "%.5e\t", (*root).spin - (*progenitor).spin); 
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
				halo -> id = (long) dummy; 
				break; 
			case DESC_ID_COLUMN: 
				halo -> desc_id = (long) dummy; 
				break; 
			case PID_COLUMN: 
				halo -> pid = (long) dummy; 
				break; 
			case SAM_MVIR_COLUMN: 
				halo -> sam_mvir = dummy; 
				break; 
			case MVIR_COLUMN: 
				halo -> mvir = dummy; 
				break; 
			case SPIN_COLUMN: 
				halo -> spin = dummy; 
				break; 
			case MMVIR_ALL_COLUMN: 
				halo -> mmvir_all = dummy; 
				break; 
			case M200B_COLUMN: 
				halo -> m200b = dummy; 
				break; 
			case M200C_COLUMN: 
				halo -> m200c = dummy; 
				break; 
			case M500C_COLUMN: 
				halo -> m500c = dummy; 
				break; 
			case M2500C_COLUMN: 
				halo -> m2500c = dummy; 
				break; 
			case SPIN_BULLOCK_COLUMN: 
				halo -> spin_bullock = dummy; 
				break; 
			default: 
				break; 

		} 

	} 
	return halo; 

} 

