
#ifndef INPUT_H 
#define INPUT_H 

#ifdef __cplusplus 
extern "C" {
#endif /* __cplusplus */ 

#include "../objects.h" 

#ifndef MAX_LINESIZE 
#define MAX_LINESIZE 1e6 
#endif /* MAX_LINESIZE */ 

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
 * source: input.c 
 */ 
extern unsigned short catalogue_open_file(CATALOGUE *catalogue); 

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
 * source: input.c 
 */ 
extern unsigned short catalogue_close_file(CATALOGUE *catalogue); 

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
 * source: input.c 
 */ 
extern unsigned short next_halo_in_tree(FILE *tree); 

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
 * source: input.c 
 */ 
extern unsigned short startswith(const char *str, const char *test); 

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
 * source: input.c 
 */ 
extern int header_length(char *file); 

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
 * source: input.c 
 */ 
extern int file_dimension(char *file); 

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
 * source: input.c 
 */ 
extern double *read_line(FILE *input, unsigned int dimension); 

#ifdef __cplusplus 
} 
#endif /* __cplusplus */ 

#endif /* INTPUT_H */ 

