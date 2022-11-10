#include "../inc/error_t.h"

void print_error(error_t rc)
{
    switch (rc)
    {
    case ERR_INV_PTR:
        printf("%s\n", "ERR_INV_PTR");
        break;
    case ERR_READING:
        printf("%s\n", "ERR_READING");
        break;
    case ERR_NO_NAME:
        printf("%s\n", "ERR_NO_NAME");
        break;
    case ERR_EMPTY_INPUT:
        printf("%s\n", "ERR_EMPTY_INPUT");
        break;
    case ERR_NO_FILE:
        printf("%s\n", "ERR_NO_FILE");
        break;
    case ERR_BUFF_OVERLOAD:
        printf("%s\n", "ERR_BUFF_OVERLOAD");
        break;
    case ERR_BAD_SIZE:
        printf("%s\n", "ERR_BAD_SIZE");
        break;
    case ERR_BAD_COMMAND:
        printf("%s\n", "ERR_BAD_COMMAND");
        break;   
    }
}
