#include <stdio.h>
#include <string.h>

#include "../headers/utils.h"
#include "../headers/long_float.h"

#define ERR_OK 0

#define LONG_NUMBERS   3
#define NUMEBRS_TO_MUL 2


int main(void)
{
    int rc = ERR_OK;

    long_float_t arr[LONG_NUMBERS];
    memset(arr, 0, sizeof(long_float_t) * LONG_NUMBERS);

    for (size_t i = 0; i < NUMEBRS_TO_MUL && rc == ERR_OK; ++i)
    {
        rc = read_long_float(arr + i);
        print_error(rc);
    }
    if (rc == ERR_OK && ((rc = mul_long_floats(arr, arr + 1, arr + 2)) == ERR_OK))
    {
        printf("Вычисленное значение: ");
        print_long_float(arr + 2);
    }

    // long_float_t l;
    // read_long_float(&l);
    // print_long_float(&l);
    // print_array(l.mantissa, MANTISSA_SIZE, '\0');
    return rc;
}
