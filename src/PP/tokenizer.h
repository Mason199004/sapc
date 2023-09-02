#ifndef SAPC_TOKENIZER_H
#define SAPC_TOKENIZER_H

bool sap_tokenizer_is_keyword(const char* str, int len);

bool sap_tokenizer_is_identifier(const char* str, int len);

int sap_tokenizer_is_string_lit(const char* str, int len);

bool sap_tokenizer_is_punctuator(const char* str, int len);

#endif //SAPC_TOKENIZER_H
