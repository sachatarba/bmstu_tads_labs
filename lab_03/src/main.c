#include <stdio.h>

#include "../inc/matr_t.h"
#include "../inc/sparse_matr_t.h"
#include "../inc/transform.h"
#include "../inc/utils.h"

int main(void)
{
    matr_t m1, m2;
    sparse_matr_t *m3, *m4, *m5 = NULL;
    read_matr(stdin, &m1);
    read_matr(stdin, &m2);
    transform_to_sparse_matr(&m1, &m3);
    transform_to_sparse_matr(&m2, &m4);
    mul_sp_matr_and_sp_vector(m3, m4, &m5);
    // read_matr(stdin, &m1);
    // transform_to_sparse_matr(&m1, &m2);
    // rand_sparse_matr_by_percent(&m1, 100, 100, 100);
    // printf("%p", (void*) m2);
    // print_array_int(m2->elems, m2->elems_count);
    // printf("\n");
    // print_array_size_t(m2->cols_ind, m2->elems_count);
    // printf("\n");
    // print_array_size_t(m2->row_begin_ind, m2->rows);
    // read_matr_by_coords(stdin, &m2);


    
    // print_matr(stdout, &m1);
    print_sparse_matr_table(m5);
    // print_matr(stdout, &m1);
}
