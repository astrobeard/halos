
#ifndef CATALOGUE_H 
#define CATALOGUE_H 

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */ 

#include "objects.h" 

/* 
 * Allocate memory for an return a pointer to a catalogue object 
 * 
 * Parameters 
 * ========== 
 * file: 		The path to the file containing the halo catalogue 
 * 
 * source: catalogue.c 
 */ 
extern CATALOGUE *catalogue_initialize(char *file); 

/* 
 * Free up the memory stored in a catalogue object 
 * 
 * Parameters 
 * ========== 
 * catalogue: 		The catalogue object to free 
 * 
 * source: catalogue.c 
 */ 
extern void catalogue_free(CATALOGUE *catalogue); 

#ifdef __cplusplus 
} 
#endif /* __cplusplus */ 

#endif /* CATALOGUE_H */ 


