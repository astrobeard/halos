/* 
 * This file implements the core routines of the catalogue object 
 */ 

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
#include "catalogue.h" 
#include "halo.h" 
#include "io/input.h" 

/* 
 * Allocate memory for an return a pointer to a catalogue object 
 * 
 * Parameters 
 * ========== 
 * file: 		The path to the file containing the halo catalogue 
 * 
 * header: catalogue.h 
 */ 
extern CATALOGUE *catalogue_initialize(char *file) {

	CATALOGUE *catalogue = (CATALOGUE *) malloc (sizeof(CATALOGUE)); 
	catalogue -> src_file_name = (char *) malloc (strlen(file) * sizeof(char)); 
	strcpy(catalogue -> src_file_name, file); 
	if (catalogue_open_file(catalogue)) { 
		catalogue_free(catalogue); 
		return NULL; 
	} else { 
		return catalogue; 
	} 

} 

/* 
 * Free up the memory stored in a catalogue object 
 * 
 * Parameters 
 * ========== 
 * catalogue: 		The catalogue object to free 
 * 
 * header: catalogue.h 
 */ 
extern void catalogue_free(CATALOGUE *catalogue) {

	if (catalogue != NULL) {

		if ((*catalogue).src_file_name != NULL) {
			free(catalogue -> src_file_name); 
			catalogue -> src_file_name = NULL; 
		} else {} 

		if ((*catalogue).src_file != NULL) {
			fclose(catalogue -> src_file); 
			catalogue -> src_file = NULL; 
		} else {} 

		if ((*catalogue).halos != NULL) {
			unsigned long i; 
			for (i = 0l; i < (*catalogue).population; i++) {
				halo_free(catalogue -> halos[i]); 
			} 
			free(catalogue -> halos); 
			catalogue -> halos = NULL; 
		} else {} 

		free(catalogue); 
		catalogue = NULL; 

	} else {} 

} 

