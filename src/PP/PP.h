#ifndef SAPC_PP_H
#define SAPC_PP_H
#include "../IO/IO.h"

typedef struct {
	char* data;
	long size;
} sap_scs_file;

sap_scs_file sap_pp_phase1(sap_file* src_file);

sap_scs_file sap_pp_phase2(sap_scs_file* src_file);

#endif //SAPC_PP_H
