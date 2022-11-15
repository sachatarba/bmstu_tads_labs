#include <stdio.h>
#include <stdlib.h>

#include "../inc/matr_t.h"
#include "../inc/sparse_matr_t.h"
#include "../inc/transform.h"
#include "../inc/utils.h"
#include "../inc/mytime.h"

int main(void)
{
    matr_t m1, m2;
    matr_t *res = malloc(sizeof(res));
    sparse_matr_t *m3, *m4, *m5 = NULL;
    struct timespec beg1;
    struct timespec beg2;
    struct timespec end1;
    struct timespec end2;
    // read_matr(stdin, &m1);
    // read_matr(stdin, &m2);
    rand_sparse_matr_by_percent(&m1, 100, 100, 15);
    rand_sparse_matr_by_percent(&m2, 100, 1, 15);
    transform_to_sparse_matr(&m1, &m3);
    transform_to_sparse_matr(&m2, &m4);
    timespec_get(&beg1, TIME_UTC);
    mul_sp_matr_and_sp_vector(m3, m4, &m5);
    timespec_get(&end1, TIME_UTC);
    timespec_get(&beg2, TIME_UTC);
    mul_matr(&m1, &m2, res);
    timespec_get(&end2, TIME_UTC);
    unsigned long long t1 = calc_elapsed_time(&beg1, &end1);
    unsigned long long t2 = calc_elapsed_time(&beg2, &end2);
    printf("Время разреженного умножения: %lld Время обычного: %lld\n", t1, t2);
    // print_sparse_matr_table(m4);
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


    
    // print_matr(stdout, res);
    // print_sparse_matr_table(m5);
    // print_matr(stdout, &m1);
}
