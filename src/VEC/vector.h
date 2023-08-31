#ifndef SAPC_VECTOR_H
#define SAPC_VECTOR_H

typedef struct {
	void* data;
	int elem_size;
	int elem_count;
	int elem_reserved;
} sap_vector;

sap_vector sap_vec_create(int elem_size, int to_reserve);

void sap_vec_reserve(sap_vector* vec, int elem_count);

void sap_vec_add(sap_vector* vec, void* elem);

void sap_vec_remove(sap_vector* vec, int index);

#define VEC_CREATE(OBJ) sap_vec_create(sizeof(typeof(OBJ)), 8); \
                        sap_vec_add(&OBJ);

#endif //SAPC_VECTOR_H
