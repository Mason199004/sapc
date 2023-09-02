#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "IO.h"

long sap_file_size(FILE* file)
{
	long pos = ftell(file);
	fseek(file, 0, SEEK_END);
	long size = ftell(file);
	fseek(file, pos, SEEK_SET);
	return size;
}

sap_file sap_read_file(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		return (sap_file){NULL, -1};
	}
	long size = sap_file_size(file);
	uint8_t* data = malloc(size);
	if (data == NULL)
	{
		return (sap_file){NULL, -1};
	}
	fread(data, size, 1, file);

	fclose(file);
	return (sap_file){data, size};
}
