#include "vector.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

sap_vector sap_vec_create(int elem_size, int to_reserve)
{
	sap_vector vec;
	memset(&vec, 0, sizeof(sap_vector));

	vec.data = malloc(elem_size * to_reserve);
	vec.elem_reserved = to_reserve;
	vec.elem_size = elem_size;
	return vec;
}

void sap_vec_reserve(sap_vector* vec, int elem_count)
{
	void* temp = realloc(vec->data, elem_count * vec->elem_size);
	if (temp != nullptr)
	{
		vec->data = temp;
		vec->elem_reserved = elem_count;
		if (vec->elem_count > vec->elem_reserved)
		{
			vec->elem_count = elem_count;
		}
	}
	else
	{
		__assert("realloc failed", __FILE__, __LINE__);
	}
}

void sap_vec_add(sap_vector* vec, void* elem)
{
	if (vec->elem_count >= vec->elem_reserved)
	{
		sap_vec_reserve(vec, vec->elem_reserved * 2);
	}

	memcpy(vec->data + (vec->elem_size * vec->elem_count++), elem, vec->elem_size);
}

void sap_vec_remove(sap_vector* vec, int index)
{
	int start = vec->elem_size * index;
	int end = start + vec->elem_size;

	for (int i = end; i < vec->elem_count * vec->elem_size; i++)
	{
		((uint8_t*)vec->data)[start] = ((uint8_t*)vec->data)[end];
		start++;
		end++;
	}

	vec->elem_count--;
}

