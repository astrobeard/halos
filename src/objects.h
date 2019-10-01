/* 
 * This file declares all objects for the halos package 
 */ 

#ifndef OBJECTS_H 
#define OBJECTS_H 

#ifdef __cplusplus 
extern "C" { 
#endif /* __cplusplus */ 

#include <stdio.h> /* for FILE struct */ 

typedef struct halo { 

	/* 
	 * The core object for a halo 
	 */ 

	double scale; 
	unsigned long id; 
	double desc_scale; 
	long desc_id; 
	unsigned long num_prog; 
	long pid; 
	long upid; 
	long desc_pid; 
	unsigned short phantom; 
	double sam_mvir; 
	double mvir; 
	double rvir; 
	double rs; 
	double vrms; 
	unsigned short mmp; 
	double scale_of_last_mm; 
	double vmax; 
	double x; 
	double y; 
	double z; 
	double vx; 
	double vy; 
	double vz; 
	double jx; 
	double jy; 
	double jz; 
	double spin; 
	unsigned long breadth_first_id; 
	unsigned long depth_first_id; 
	unsigned long tree_root_id; 
	unsigned long orig_halo_id; 
	unsigned long snap_num; 
	unsigned long next_coprogenitor_depthfirst_id; 
	unsigned long last_progenitor_depthfirst_id; 
	unsigned long last_mainleaf_depthfirst_id; 
	double tidal_force; 
	unsigned long tidal_id; 
	double rs_klypin; 
	double mmvir_all; 
	double m200b; 
	double m200c; 
	double m500c; 
	double m2500c; 
	double xoff; 
	double voff; 
	double spin_bullock; 
	double b_to_a; 
	double c_to_a; 
	double ax; 
	double ay; 
	double az; 
	double b_to_a500c; 
	double c_to_a500c; 
	double ax500c; 
	double ay500c; 
	double az500c; 
	double t_over_u; 
	double m_pe_behroozi; 
	double m_pe_diemer; 
	double macc; 
	double mpeak; 
	double vacc; 
	double vpeak; 
	double halfmass_scale; 
	double acc_rate_inst; 
	double acc_rate_100Myr; 
	double acc_rate_1tdyn; 
	double acc_rate_2tdyn; 
	double acc_rate_mpeak; 
	double mpeak_scale; 
	double acc_scale; 
	double first_acc_scale; 
	double first_acc_mvir; 
	double first_acc_vmax; 
	double vmax_at_mpeak; 
	double tidal_force_tdyn; 
	double log_vmax_over_maxvmax; 
	double time_to_future_merger; 
	double future_merger_mmp; 

} HALO; 

typedef struct catalogue {

	unsigned long population; 
	char *src_file_name; 
	FILE *src_file; 
	HALO **halos; 

} CATALOGUE; 


#ifdef __cplusplus 
} 
#endif /* __cplusplus */ 

#endif /* OBJECTS_H */ 

