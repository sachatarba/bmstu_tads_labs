#ifndef __SPARSE_MATR_T_H__
#define __SPARSE_MATR_T_H__

#include <stddef.h>
#include <stdio.h>

#include "../inc/error_t.h"

struct sparse_matr
{
    size_t rows;
    size_t cols;
    size_t elems_count;
    int *elems;
    size_t *cols_ind;
    size_t *row_begin_ind;
};

typedef struct sparse_matr sparse_matr_t;

void free_sparse_matr(sparse_matr_t *sp_matr);

void print_sp_matrix(sparse_matr_t *m);

sparse_matr_t *create_sparse_matr(size_t rows, size_t cols, size_t elems_count);

error_t read_sparse_matr(FILE *fp, sparse_matr_t *sp_matr);

error_t print_sparse_matr_table(sparse_matr_t *sp_matr);

error_t print_sparse_matr(FILE *fp, sparse_matr_t *sp_matr);

error_t mul_sparse_matr(sparse_matr_t *l, sparse_matr_t *r, sparse_matr_t *res);

error_t mul_sp_matr_and_sp_vector(sparse_matr_t *sp_matr, sparse_matr_t *sp_vector, sparse_matr_t **result);

// error_t mul_sp_matr_and_sp_vector(sparse_matr_t *sp_matr, sparse_matr_t *sp_vector, sparse_matr_t **result)

#endif  // __SPARSE_MATR_T_H__
