#ifndef SAPC_STR_H
#define SAPC_STR_H

int sap_str_first_nonspace(const char* str);

int sap_str_first_space(const char* str);

bool sap_strn_matches(const char* to_cmp, int len, int count, ...);



#endif //SAPC_STR_H
