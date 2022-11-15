#include <stdbool.h>

#include "../inc/transform.h"
#include "../inc/utils.h"

/// @brief переводит matr_t к sparse_matr_t
/// @param matr 
/// @param sp_matr 
/// @return разреженное представление матрицы
error_t transform_to_sparse_matr(matr_t *matr, sparse_matr_t **sp_matr)
{
    error_t rc = OK;

    if (matr)
    {
        size_t count = 0;

        for (size_t i = 0; i < matr->rows; ++i)
        {
            for (size_t j = 0; j < matr->cols; ++j)
            {
                if (matr->body[i][j] != 0)
                    ++count;
            }
        }

        *sp_matr = create_sparse_matr(matr->rows, matr->cols, count);
        
        bool is_first_elm_of_row = true;
        if (*sp_matr)
        {
            size_t elms_count = 0;
            for (size_t i = 0; i < matr->rows; ++i)
            {                
                for (size_t j = 0; j < matr->cols; ++j)
                {
                    if (matr->body[i][j] != 0)
                    {
                        (*sp_matr)->elems[elms_count] = matr->body[i][j];
                        (*sp_matr)->cols_ind[elms_count] = j;
                        
                        if (is_first_elm_of_row == true)
                        {
                            (*sp_matr)->row_begin_ind[i] = elms_count;
                            // printf("%zu", (*sp_matr)->row_begin_ind[i]);
                            is_first_elm_of_row = false;
                        }
                        
                        ++elms_count;
                    }
                }

                if (is_first_elm_of_row == true)
                {
                    (*sp_matr)->row_begin_ind[i] = -1;
                }
                else
                {
                    is_first_elm_of_row = true;
                }
                
            }
        }
        else
        {
            rc = ERR_ALLOC_MATR;
        }
    }
    else
    {
        rc = ERR_INV_STRUCT_PTR;
    }

    // printf("|");
    // print_array_size_t((*sp_matr)->row_begin_ind, (*sp_matr)->rows);
    // printf("|");
    return rc;
}
