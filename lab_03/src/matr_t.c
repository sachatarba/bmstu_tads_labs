#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <math.h>

#include "../inc/utils.h"
#include "../inc/matr_t.h"

#define RESIZE 2
#define MAX_SIZE 5000
#define EPS 1e-7

error_t create_matr(matr_t *matr, size_t rows, size_t cols)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (rows > 0 && cols > 0)
        {
            matr->body = calloc(rows * RESIZE, sizeof(long long*));

            if (matr->body != NULL)
            {
                for (size_t i = 0; i < rows * RESIZE; ++i)
                {
                    matr->body[i] = calloc(cols * RESIZE, sizeof(long long));
                    // memset(matr->body[i], 0, sizeof(long long) * RESIZE + 1);

                    if (matr->body[i] == NULL)
                    {
                        rc = ERR_ALLOC_MATR;
                    }
                }

                if (rc == OK)
                {
                    matr->rows = rows;
                    matr->rows_allocated = rows * RESIZE;
                    matr->cols = cols;
                    matr->cols_allocated = cols * RESIZE;
                    matr->alloc_resize = RESIZE; 
                }
                else
                {
                    free_matr(matr);
                }
            }
            else
            {
                rc = ERR_ALLOC_MATR;
            }
        }
        else if (rows <= 0)
        {
            rc = ERR_BAD_ROWS;
        }
        else
        {
            rc = ERR_BAD_COLS;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}


error_t free_matr(matr_t *matr)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (matr->body != NULL)
        {
            for (size_t i = 0; i < matr->rows_allocated; ++i)
            {
                if (matr->body[i] != NULL)
                {
                    free(matr->body[i]);
                    matr->body[i] = NULL;
                }
                else
                {
                    rc = ERR_INV_PTR;
                }
            }

            free(matr->body);
            matr->body = NULL;
            matr->rows = 0;
            matr->cols = 0;
            matr->rows_allocated = 0;
            matr->cols_allocated = 0;
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t read_matr(FILE *fp, matr_t *matr)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        int64_t rows = 0, cols = 0;

        if (fp == stdin)
            printf("Введите число строк и столбцов: ");
        if (fscanf(fp, "%" PRId64 "%" PRId64, &rows, &cols) == 2)
        {
            if (rows > 0 && cols > 0)
            {
                if (fp == stdin)
                    printf("Введите элементы: ");
                if ((rc = create_matr(matr, rows, cols)) == OK)
                {
                    for (size_t cur_row = 0; cur_row < matr->rows; ++cur_row)
                    {
                        for (size_t cur_col = 0; cur_col < matr->cols; ++cur_col)
                        {
                            if (fscanf(fp, "%lld", &matr->body[cur_row][cur_col]) != 1)
                            {
                                rc = ERR_READING;
                            }
                        }
                    }

                    if (rc != OK)
                    {
                        free_matr(matr);
                    }
                }
            }
            else if (rows <= 0)
            {
                rc = ERR_BAD_ROWS;
            }
            else
            {
                rc = ERR_BAD_COLS;
            }
        }
        else
        {
            rc = ERR_READING;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t read_matr_by_coords(FILE *fp, matr_t *matr)
{
     error_t rc = OK;

    if (matr != NULL)
    {
        int64_t rows = 0, cols = 0;
        if (fp == stdin)
            printf("Введите число строк и столбцов: ");
        if (fscanf(fp, "%" PRId64 "%" PRId64, &rows, &cols) == 2)
        {
            if (rows > 0 && cols > 0)
            {
                if ((rc = create_matr(matr, rows, cols)) == OK)
                {
                    if (fp == stdin)
                        printf("Введите число элементов, которые вы хотите заполнить: ");
                    
                    int size, row, col, elm = 0;
                    fscanf(fp, "%d", &size);
                    if (size > 0)
                        for (size_t cur_elm= 0; cur_elm < (size_t) size; ++cur_elm)
                        {
                            if (fp == stdin)
                                printf("Введите строку, столбец и значения элемента матрицы: ");
                            fscanf(fp, "%d %d %d", &row, &col, &elm);

                            if (row >=0 && col >=0 && row < rows && col < cols)
                                matr->body[row][col] = elm;
                            else
                                rc = ERR_BAD_SIZE;
                        }
                    else
                        rc = ERR_BAD_SIZE;

                    if (rc != OK)
                    {
                        free_matr(matr);
                    }
                }
            }
            else if (rows <= 0)
            {
                rc = ERR_BAD_ROWS;
            }
            else
            {
                rc = ERR_BAD_COLS;
            }
        }
        else
        {
            rc = ERR_READING;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;   
}

error_t print_matr(FILE *fp, matr_t *matr)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (matr->body != NULL)
        {
            if (matr->cols > 0 && matr->rows > 0)
            {
                for (size_t cur_row = 0; cur_row < matr->rows; ++cur_row)
                {
                    for (size_t cur_col = 0; cur_col < matr->cols; ++cur_col)
                    {
                        if (matr->body[cur_row] != NULL)
                        {
                            fprintf(fp, "%lld ", matr->body[cur_row][cur_col]);
                        }
                    }

                    printf("\n");
                }
            }
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t del_row(matr_t *matr, size_t row_ind)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (row_ind < matr->rows)
        {
            if (matr->body != NULL)
            {
                free(matr->body[row_ind]);
                for (size_t cur_row = row_ind; cur_row < matr->rows_allocated - 1; ++cur_row)
                {
                    matr->body[cur_row] = matr->body[cur_row + 1];
                }
                
                matr->body[matr->rows_allocated - 1] = NULL;
                --matr->rows;
                --matr->rows_allocated;
            }
            else
            {
                rc = ERR_INV_PTR;
            }
        }
        else
        {
            rc = ERR_BAD_ROW_IND;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t del_col(matr_t *matr, size_t col_ind)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (col_ind < matr->cols)
        {
            if (matr->body != NULL)
            {
                for (size_t cur_row = 0; cur_row < matr->rows; ++cur_row)
                {
                    if (matr->body[cur_row] != NULL)
                    {
                        for (size_t cur_col = col_ind; cur_col < matr->cols - 1; ++cur_col)
                        {
                            matr->body[cur_row][cur_col] = matr->body[cur_row][cur_col + 1];
                        }
                    }
                    else
                    {
                        rc = ERR_INV_PTR;
                    }
                }

                if (rc == OK)
                {
                    --matr->cols;
                }
            }
            else
            {
                rc = ERR_INV_PTR;
            }
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t resize_matr(matr_t *matr, size_t new_rows_size, size_t new_cols_size)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (matr->body != NULL)
        {
            if (new_rows_size > 0 && new_cols_size > 0)
            {
                // TODO: добавить проверку на то, что размер изменился
                long long **temp = realloc(matr->body, new_rows_size * sizeof(long long*));
                // memset(temp, 0, new_rows_size * sizeof(long long*));

                if (temp != NULL)
                {
                    matr->body = temp;

                    for (size_t cur_row = 0; cur_row < matr->rows_allocated; ++cur_row)
                    {
                        if (realloc_array(&matr->body[cur_row], new_cols_size) != OK)
                        {
                            rc = ERR_REALLOC;
                        }
                    }

                    if (rc == OK)
                    {
                        for (size_t cur_row = matr->rows_allocated; cur_row < new_rows_size; ++cur_row)
                        {
                            if (alloc_array(&matr->body[cur_row], new_cols_size) != OK)
                            {
                                rc = ERR_ALLOC;
                            }
                        }
                    }

                    if (rc == OK)
                    {
                        matr->cols_allocated = new_cols_size;
                        matr->rows_allocated = new_rows_size; 
                    }
                }
                else
                {
                    rc = ERR_REALLOC;
                }
            }
            else if (new_rows_size <= 0)
            {
                rc = ERR_BAD_ROWS;
            }
            else
            {
                rc = ERR_BAD_COLS;
            }
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t append_row(matr_t *matr, long long *row)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (row != NULL)
        {
            if (matr->rows < matr->rows_allocated)
            {
                memcpy(matr->body[matr->rows], row, sizeof(long long) * matr->cols);
                ++matr->rows;
            }
            else
            {
                if ((rc = resize_matr(matr, matr->rows_allocated * matr->alloc_resize, matr->cols_allocated)) == OK)
                {
                    memcpy(matr->body[matr->rows], row, sizeof(long long) * matr->cols);
                    ++matr->rows;
                }
            }
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t append_col(matr_t *matr, long long *col)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (col != NULL)
        {
            if (matr->cols < matr->cols_allocated)
            {
                for (size_t cur_row = 0; cur_row < matr->rows; ++cur_row)
                {
                    matr->body[cur_row][matr->cols] = col[cur_row];
                }

                ++matr->cols;
            }
            else
            {
                if ((rc = resize_matr(matr, matr->rows_allocated, matr->cols_allocated * matr->alloc_resize)) == OK)
                {
                    for (size_t cur_row = 0; cur_row < matr->rows; ++cur_row)
                    {
                        matr->body[cur_row][matr->cols] = col[cur_row];
                    }

                    ++matr->cols;
                }
            }
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t copy_matr(matr_t *dst, matr_t *src)
{
    error_t rc = OK;

    if (dst != NULL && src != NULL)
    {
        free_matr(dst);
        rc = create_matr(dst, src->rows, src->cols);

        if (rc == OK)
        {
            for (size_t i = 0; i < dst->rows; ++i)
            {
                for (size_t j = 0; j < dst->cols; ++j)
                {
                    dst->body[i][j] = src->body[i][j];
                }
            }
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t mul_matr(matr_t *l, matr_t *r, matr_t *res)
{
    error_t rc = OK;

    if (l != NULL && r != NULL && res != NULL)
    {
        if (l->cols == r->rows)
        {
            matr_t temp;
            
            rc = create_matr(&temp, l->rows, r->cols);

            if (rc == OK)
            {
                for (size_t i = 0; i < l->rows; ++i)
                {
                    for (size_t j = 0; j < r->cols; ++j)
                    {
                        temp.body[i][j] = 0;
                        
                        for (size_t k = 0; k < l->cols; ++k)
                        {
                            temp.body[i][j] += l->body[i][k] * r->body[k][j];
                        }
                    }
                }

                copy_matr(res, &temp);
                free_matr(&temp);
            }
        }
        else
        {
            rc = ERR_MUL_MTR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t find_min_of_matr(matr_t *matr, size_t *row, size_t *col)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        long long min = matr->body[0][0];

        for (size_t i = 0; i < matr->rows; ++i)
        {
            for (size_t j = 0; j < matr->cols; ++j)
            {
                if (matr->body[i][j] < min)
                {
                    *row = i;
                    *col = j;
                    min = matr->body[i][j];
                }
            }
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    return rc;
}

error_t rand_sparse_matr_by_percent(matr_t *matr, size_t rows, size_t cols, size_t discharge_percentage)
{
    error_t rc = OK;

    if (matr != NULL)
    {
        if (rows > 0 && cols > 0)
        {
            if (discharge_percentage <= 100)
            {
                rc = create_matr(matr, rows, cols);
                srand(time(NULL));
                if (rc == OK)
                {
                    size_t not_zero_elms_num = rows * cols * discharge_percentage / 100;
                    size_t r = 0, c = 0;

                    for (size_t i = 0; i < not_zero_elms_num; ++i)
                    {
                        r = rand() % rows;
                        c = rand() % cols;

                        while (matr->body[r][c] != 0)
                        {
                            r = rand() % rows;
                            c = rand() % cols;
                        }

                        matr->body[r][c] = rand() % MAX_SIZE;
                    }
                    
                }
            }
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
