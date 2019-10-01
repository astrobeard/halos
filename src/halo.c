/* 
 * This file implements the core routines of the halo object 
 */ 

#include <stdlib.h> 
#include "halo.h" 

/* 
 * Allocate memory for and return a pointer to a halo object 
 * 
 * header: halo.h 
 */ 
extern HALO *halo_initialize(void) {

	return (HALO *) malloc (sizeof(HALO)); 

} 

/* 
 * Free up the memory stored in a halo pointer. 
 * 
 * header: halo.h 
 */ 
extern void halo_free(HALO *halo) {

	if (halo != NULL) {
		free(halo); 
		halo = NULL; 
	} else {} 

}

