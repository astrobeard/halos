/* 
 * This file implements all input routines for the halos package 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "input.h" 

static unsigned short startswith(const char *str, const char *test); 

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
 */ 
static unsigned short startswith(const char *str, const char *test) {

	unsigned long i; 
	for (i = 0l; i < strlen(test); i++) {
		if (str[i] != test[i]) return 0; 
	} 
	return 1; 

}

