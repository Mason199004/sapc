#ifndef SAPC_PP_H
#define SAPC_PP_H
#include "../IO/IO.h"

typedef struct {
	char* data;
	long size;
} sap_scs_file;

sap_scs_file sap_pp_phase1(sap_file* src_file);

sap_scs_file sap_pp_phase2(sap_scs_file* src_file);

typedef enum {
	pp_directive,
	identifier,
	pp_number,
	char_const,
	string_lit,
	punctuator,
	uchar_name,
	reg_char
} sap_pp_token_type;

typedef struct {
	char* str;
	int len;
	sap_pp_token_type type;
} sap_pp_token;

typedef struct {
	sap_pp_token* tokens;
	int count;
} sap_pp_token_arr;

sap_pp_token_arr sap_pp_phase3(sap_scs_file* src);

#endif //SAPC_PP_H
