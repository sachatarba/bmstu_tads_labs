#ifndef __ERROR_T_H__
#define __ERROR_T_H__


enum error
{
    OK,
    ERR_FILE_PTR,
    ERR_PTR,
    ERR_BAD_SIZE,
    ERR_REALLOC,
    ERR_ALLOC,
    ERR_BAD_ROWS,
    ERR_BAD_COLS,
    ERR_INV_PTR,
    ERR_INV_STRUCT_PTR,
    ERR_MUL_MTR,
    ERR_BAD_ROW_IND,
    ERR_READING,
    ERR_ALLOC_MATR,
    ERR_PERCENT
};

typedef enum error error_t;

#endif  // __ERROR_T_H__
