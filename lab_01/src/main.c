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
    printf("Программа для умножения действительных чисел");
    printf("Числа вводятся в одну строку с обязательной точкой в мантиссе,\n мантисса и порядок разделяются большой или маленькой буквой E\n");
    for (size_t i = 0; i < NUMEBRS_TO_MUL && rc == ERR_OK; ++i)
    {
        printf("Введите %ld - ое числое для умножения:\n", i);
        printf("|-----------------------------| E |---|\n");
        rc = read_long_float(arr + i);
        print_error(rc);
    }
    if (rc == ERR_OK && ((rc = mul_long_floats(arr, arr + 1, arr + 2)) == ERR_OK))
    {
        printf("Вычисленное значение: ");
        print_long_float(arr + 2);
    }

    return rc;
}
