#include <stdint.h>
#include <stdlib.h>
#include "PP.h"
#include "../STR/str.h"
#include "../VEC/vector.h"


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

//rvalue is number of chars in returned token, 0 means invalid token
int sap_pp_into_token(const char* str, int len, sap_pp_token* out_token)
{
	if (*str == '#')
	{
		out_token->type = pp_directive;
		out_token->str = str;

		int i = 0;
		while (str[i] != '\n')
		{
			i++;
		}

		out_token->len = i;
		return i;
	}

	if (len == 1)
	{
		out_token->type = reg_char;
		out_token->len = 1;
		out_token->str = str;
		return 1;
	}

	return 0;
}

sap_pp_token_arr sap_pp_phase3(sap_scs_file* src)
{
	int start = sap_str_first_nonspace(src->data);
	int end = sap_str_first_space(src->data + start);

	sap_vector tokens = sap_vec_create(sizeof(sap_pp_token), src->size / 2);

	sap_pp_token tok;
	int i = 0;
	loop: while (start < end)
	{
		i = sap_pp_into_token(src->data + start, end - start, &tok);
		if (i == 0)
		{
			end--;
			continue;
		}

		sap_vec_add(&tokens, &tok);
		start += i;
	}

	if (end < src->size)
	{
		start = sap_str_first_nonspace(src->data + start) + start;
		end = sap_str_first_space(src->data + start) + end;
		i = 0;
		goto loop;
	}

	sap_vec_reserve(&tokens, tokens.elem_count);

	sap_pp_token_arr arr;
	arr.count = tokens.elem_count;
	arr.tokens = tokens.data;

	return arr;
}