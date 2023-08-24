#ifndef SAPC_IO_H
#define SAPC_IO_H
#include <stdint.h>
#include <stdio.h>

typedef struct {
	uint8_t* data;
	long size;
} sap_file;

sap_file sap_read_file(const char* path);

long sap_file_size(FILE* file);

#endif //SAPC_IO_H
