#ifndef __ERROR_T_H__
#define __ERROR_T_H__

enum error_t
{
    OK,
    ERR_INV_PTR,
    ERR_READING,
    ERR_NO_NAME,
    ERR_EMPTY_INPUT,
    ERR_NO_FILE,
    ERR_BUFF_OVERLOAD,
    ERR_BAD_SIZE
};

typedef enum error_t error_t;

#endif
