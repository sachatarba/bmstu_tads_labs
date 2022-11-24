#include <stdlib.h>
#include <stdio.h>

#include "../inc/sparse_matr_t.h"
#include "../inc/utils.h"

void free_sparse_matr(sparse_matr_t *sp_matr)
{
    if (sp_matr)
    {
        free(sp_matr->elems);
        sp_matr->elems = NULL;
        
        free(sp_matr->cols_ind);
        sp_matr->cols_ind = NULL;

        free(sp_matr->row_begin_ind);
        sp_matr->row_begin_ind = NULL;

        free(sp_matr);
        sp_matr = NULL;
    }
}

sparse_matr_t *create_sparse_matr(size_t rows, size_t cols, size_t elems_count)
{
    if (rows <= 0 || cols <= 0)
        return NULL;
    
    sparse_matr_t *sp_matr = malloc(sizeof(sparse_matr_t));
    
    if (sp_matr == NULL)
    {
        // printf("bebra");
        return NULL;
    }

    sp_matr->elems = malloc(sizeof(int) * elems_count);
    sp_matr->cols_ind = malloc(sizeof(size_t) * elems_count);
    sp_matr->row_begin_ind = malloc(sizeof(size_t) * rows);

    if (!sp_matr->elems || !sp_matr->cols_ind || !sp_matr->row_begin_ind)
    {
        free_sparse_matr(sp_matr);
        // printf("lol");
        return sp_matr;
    }

    sp_matr->rows = rows;
    sp_matr->cols = cols;
    sp_matr->elems_count = elems_count;

    // printf("%p", (void *)sp_matr);
    return sp_matr;
}

int get_elm(sparse_matr_t *sp_matr, size_t row, size_t col)
{
    int ret = 0;
    size_t ind_of_row_begin = sp_matr->row_begin_ind[row];

    if (ind_of_row_begin == (size_t) -1)
        return ret;

    size_t ind_of_row_end = (row < sp_matr->rows - 1) ? sp_matr->row_begin_ind[row + 1] : sp_matr->elems_count;
    // ind_of_row_end = (ind_of_row_end == (size_t) -1) ? sp_matr->elems_count : ind_of_row_end;

    size_t i = row + 1; 
    while (ind_of_row_end == (size_t) -1 && i < sp_matr->rows)
    {
        ind_of_row_end = sp_matr->row_begin_ind[i++];
    }
    
    if (ind_of_row_end == (size_t) -1)
        ind_of_row_end = sp_matr->elems_count;

    for (size_t i = ind_of_row_begin; i < ind_of_row_end; ++i)
    {
        if (sp_matr->cols_ind[i] == col)
        {
            ret = sp_matr->elems[i];
            break;
        }
    }

    return ret;
}

error_t print_sparse_matr_table(sparse_matr_t *sp_matr)
{
    error_t rc = OK;
    
    if (sp_matr)
    {
        for (size_t i = 0; i < sp_matr->rows; ++i)
        {
            for (size_t j = 0; j < sp_matr->cols; ++j)
                printf("%d ", get_elm(sp_matr, i, j));
            printf("\n");
        }    
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t mul_sp_matr_and_sp_vector(sparse_matr_t *sp_matr, sparse_matr_t *sp_vector, sparse_matr_t **result)
{
    error_t rc = OK;

    if (sp_matr && sp_vector)
    {
        if (sp_matr->cols == sp_vector->rows)
        {
            *result = create_sparse_matr(sp_matr->rows, 1, sp_matr->rows);
            int *vector = calloc(sp_vector->rows, sizeof(int));

            // printf("\n");
            // print_array_size_t(sp_vector->row_begin_ind, sp_vector->rows);
            // printf("\n");
            for (size_t i = 0; i < sp_vector->rows; ++i)
            {
                if (sp_vector->row_begin_ind[i] != (size_t) -1)
                    vector[i] = sp_vector->elems[sp_vector->row_begin_ind[i]];
                else
                    vector[i] = 0; 
            }
            // printf("ajjkjijijoi\n");
            // printf("\n|");
            // print_array_int(vector, sp_vector->rows);
            // printf("|\n");
            int sum = 0;
            int count = 0;
            for (size_t i = 0; i < sp_matr->rows; ++i)
            {
                sum = 0;
                for (size_t j = 0; j < sp_vector->rows; ++j)
                {
                    if (vector[j] != 0)
                    {
                        sum += get_elm(sp_matr, i, j) * vector[j];
                        // printf("\nelm(%ld, %ld): %d\n",i, j, get_elm(sp_matr, i, j));
                    }
                }

                if (sum != 0)
                {
                    // printf("\nsum: %d\n", sum);
                    (*result)->elems[count] = sum;
                    (*result)->cols_ind[count] = 0;
                    (*result)->row_begin_ind[i] = count++;
                }
                else
                {
                    (*result)->row_begin_ind[i] = (size_t) -1;
                }
            }
            // (*result)->rows = count;
            (*result)->elems_count = count;
        }
        else
        {
            rc = ERR_BAD_SIZE;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

// error_t read_sparse_matr(FILE *fp, sparse_matr_t *sp_matr)
// {
//     error_t rc = OK;

//     if (fp)
//     {
//         if (fp == stdin)
//             printf("Введите число строк: ");
        
//         int rows, cols, elems = 0;
//         fscanf(fp, "%d", &rows);

//         if (rows <= 0)
//             rc = ERR_BAD_SIZE;

//         if (rc == OK)
//         {    
//             if (fp == stdin)
//                 printf("\nВведите число столбцов: ");
//             fscanf(fp, "%d", &cols);

//             if (cols <= 0)
//                 rc = ERR_BAD_SIZE;
            
//             if (rc == OK)
//             {
//                 if (fp == stdin)
//                     printf("\nВведите число ненулевых элементов: ");
//                 fscanf(fp, "%d", &elems);

//                 if (elems <= 0)
//                     rc = ERR_BAD_SIZE;
                
//                 if (rc == OK)
//                 {
//                     sparse_matr_t *sp_matr = create_sparse_matr(rows, cols, elems);

//                     if (!sp_matr)
//                         rc = ERR_PTR;

//                     if (rc == OK)
//                     {
//                         if (fp == stdin)
//                             printf("\nВведите ненулевые элементы: ");
                        
//                         int i = 0;
//                         while (i < elems && rc == OK)
//                         {
//                             fscanf(fp, "%d", sp_matr->elems + i);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     else
//     {
//         rc = ERR_FILE_PTR;
//     }

//     return rc;
// }


// error_t print_sparse_matr(FILE *fp, sparse_matr_t *sp_matr)
// {
//     // print_array_int(sp_matr->elems, sp_matr->elems_count);
//     // printf("\n");
//     for (size_t i = 0; i < sp_matr->elems_count; ++i)
//     {
//         int elm = get_elm(sp_matr, 0, i);
//         if (elm != 0)
//             fprintf(fp, "Номер строки: %zu, значение элемента: %d", i, elm);
//         // if (sp_matr->row_begin_ind[i] != (size_t) -1)
//             // fprintf(fp, "%zu", sp_matr->row_begin_ind[i]);   
//     }

//     return 0;
// }


error_t print_sparse_matr(FILE *fp, sparse_matr_t *sp_matr)
{
    error_t rc = OK;
    
    if (sp_matr)
    {
        for (size_t i = 0; i < sp_matr->rows; ++i)
        {
            for (size_t j = 0; j < sp_matr->cols; ++j)
            {
                int elm =  get_elm(sp_matr, i, j);

                if (elm != 0)
                {
                    fprintf(fp, "Номер строки: %zu, значение элемента: %d", i, elm);
                    fprintf(fp, "\n");
                }
            }
                // printf("%d ", get_elm(sp_matr, i, j));
            // printf("\n");
        }    
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}
