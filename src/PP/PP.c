#include <stdint.h>
#include <stdlib.h>
#include "PP.h"


//on error size is location where error occurred
sap_scs_file sap_pp_phase1(sap_file* src_file)
{
	int removed = 0;
	unsigned char c;
	for (int i = 0; i < src_file->size; ++i)
	{
		if ((c = src_file->data[i]) >= 127)
		{
			return (sap_scs_file) {NULL, i};
		}
		if (c < 32)
		{
			if (c != 9 && c != 10)
			{
				src_file->data[i] = 0;
				removed++;
			}
		}
	}

	char* new_data = malloc(src_file->size - removed);
	if (new_data == NULL)
	{
		return (sap_scs_file) {NULL, -1};
	}
	int j = 0;
	for (int i = 0; i < src_file->size; ++i)
	{
		if (src_file->data[i] == 0)
		{
			j++;
			continue;
		}
		new_data[i - j] = src_file->data[i];
	}
	free(src_file->data);
	return (sap_scs_file) {new_data, src_file->size - j};
}

sap_scs_file sap_pp_phase2(sap_scs_file* src_file)
{
	if (src_file->data[src_file->size - 1] != '\n')
	{
		src_file->size++;
		src_file->data = realloc(src_file->data, src_file->size);
		if (src_file->data == NULL)
		{
			return (sap_scs_file) {NULL, -1};
		}
	}
	if (src_file->data[src_file->size - 2] == '\\')
	{
		return (sap_scs_file) {NULL, src_file->size - 2};
	}
	int removed = 0;
	for (int i = 0; i < src_file->size - 1; ++i)
	{
		if (src_file->data[i] == '\\' && src_file->data[i + 1] == '\n')
		{
			src_file->data[i] = 0;
			src_file->data[i + 1] = 0;
			removed += 2;
		}
	}

	char* new_data = malloc(src_file->size - removed);
	if (new_data == NULL)
	{
		return (sap_scs_file) {NULL, -1};;
	}

	char c;
	int j = 0;
	for (int i = 0; i < src_file->size; ++i)
	{
		c = src_file->data[i];
		if (c == 0)
		{
			j++;
			continue;
		}
		new_data[i - j] = src_file->data[i];
	}

	free(src_file->data);
	return (sap_scs_file) {new_data, src_file->size - j};
}