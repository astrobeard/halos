
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

#ifdef __cplusplus 
} 
#endif /* __cplusplus */ 

#endif /* INTPUT_H */ 

