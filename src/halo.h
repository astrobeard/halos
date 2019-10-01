
#ifndef HALO_H
#define HALO_H 

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */ 

#include "objects.h" 

/* 
 * Allocate memory for and return a pointer to a halo object 
 * 
 * source: halo.c 
 */ 
extern HALO *halo_initialize(void); 

/* 
 * Free up the memory stored in a halo pointer. 
 * 
 * source: halo.c 
 */ 
extern void halo_free(HALO *halo); 


#ifdef __cplusplus 
} 
#endif /* __cplusplus */ 

#endif /* HALO_H */ 

