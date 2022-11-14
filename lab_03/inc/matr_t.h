#ifndef __MATR_T_H__
#define __MATR_T_H__

#include <stddef.h>
#include <stdio.h>

#include "../inc/error_t.h"

struct matr
{
    long long **body;

    size_t rows;
    size_t cols;

    size_t rows_allocated;
    size_t cols_allocated;

    size_t alloc_resize; 
};

typedef struct matr matr_t;

error_t create_matr(matr_t *matr, size_t rows, size_t cols);

error_t free_matr(matr_t *matr);

error_t resize_matr(matr_t *matr, size_t new_rows_size, size_t new_cols_size);

error_t read_matr(FILE *fp, matr_t *matr);

error_t print_matr(FILE *fp, matr_t *matr);

error_t del_row(matr_t *matr, size_t row_ind);

error_t del_col(matr_t *matr, size_t col_ind);

error_t append_row(matr_t *matr, long long *row);

error_t append_col(matr_t *matr, long long *col);

error_t mul_matr(matr_t *l, matr_t *r, matr_t *res);

error_t find_min_of_matr(matr_t *matr, size_t *row, size_t *col);

error_t copy_matr(matr_t *dst, matr_t *src);

error_t read_matr_by_coords(FILE *fp, matr_t *matr);

error_t rand_sparse_matr_by_percent(matr_t *matr, size_t rows, size_t cols, size_t discharge_percentage);

#endif
