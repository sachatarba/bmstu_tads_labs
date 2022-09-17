#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/long_float.h"
#include "../headers/utils.h"

#define BUFF_SIZE 100

#define MAX_EXPONENT 100000

#define ERR_OK                0
#define ERR_READING           1
#define ERR_EMPTY             2
#define ERR_NOT_NUMBER        3
#define ERR_READING_MANTISSA  4
#define ERR_READING_EXPONENT  5

#define ERR_OVERFLOW 1

#define RADIX 10

#define NO_SPACE '\0'

// Сдвиг мантиссы в конец
void shift_number(long_float_t *lf)
{
    memmove(lf->mantissa + MANTISSA_SIZE - lf->digits, lf->mantissa, lf->digits);
    memset(lf->mantissa, 0, MANTISSA_SIZE - lf->digits);
}


// Установка знака длинного числа
int set_sign(long_float_t *long_number, const char symbol)
{
    int rc = ERR_OK;

    if (symbol == '+' || isdigit(symbol))
    {
        long_number->sign = PLUS;
    }
    else if (symbol == '-')
    {
        long_number->sign = MINUS;
    }
    else
    {
        rc = ERR_READING;
    }

    return rc;
}

// Копирование мантиссы из строки
int copy_mantissa(long_float_t *long_number, const char *string, char **end)
{
    int rc = ERR_OK;

    size_t digits = MANTISSA_SIZE;

    char *end_string = (char *) copy_digits_to_array(string, long_number->mantissa, &digits);

    if (*(end_string) == '.')
    {
        ++end_string;
        long_number->exponent = digits;
        long_number->digits = MANTISSA_SIZE - digits;

        *end = (char *) copy_digits_to_array(end_string, long_number->mantissa + digits, &long_number->digits);
        long_number->digits += digits;
    }
    else
    {
        rc = ERR_NOT_NUMBER;
    }

    return rc;
}

// Копирование экспоненты из строки
int copy_exponent(long_float_t *long_number, const char *string, char **end)
{
    int rc = ERR_OK;

    string = iter_string_while_whitespace(string, FORWARD);

    if (*string == 'E' || *string == 'e')
    {
        ++string;
        string = iter_string_while_whitespace(string, FORWARD);

        int exp = strtol(string, end, RADIX);
        long_number->exponent += exp;
    }
    else
    {
        rc = ERR_READING;
    }

    return rc;
}


/// Чтение длинного числа 
int read_long_float(long_float_t *long_number)
{
    int rc = ERR_OK;
    char buff[BUFF_SIZE] = { '\0' };
    
    if (fgets(buff, BUFF_SIZE, stdin) != NULL)
    {
        char *string = strip(buff);

        if (!is_string_whitespace(string))
        {
            if (set_sign(long_number, *string) == ERR_OK)
            {
                if (is_sign(*string))
                {                   
                    ++string;
                }

                char *end_mantissa = NULL;
                if (copy_mantissa(long_number, string, &end_mantissa) == ERR_OK)
                {
                    char *end_exponent = NULL;
                    if (copy_exponent(long_number, end_mantissa, &end_exponent) == ERR_OK)
                    {
                        if (!is_end(*end_exponent))
                        {
                            rc = ERR_READING_EXPONENT;
                        }
                        else
                        {
                            shift_number(long_number);
                        }
                    }
                    else
                    {
                        rc = ERR_READING_EXPONENT;
                    }
                }
                else
                {
                    rc = ERR_READING_MANTISSA;
                }
                
            }
            else
            {
                rc = ERR_NOT_NUMBER;
            }
        }
        else
        {
            rc = ERR_EMPTY;
        } 
    }
    else
    {
        rc = ERR_READING;
    }

    return rc;
}

// Нормализация числа
void normalize_number(long_float_t *lf)
{
    for (size_t i = MANTISSA_SIZE - lf->digits; i < MANTISSA_SIZE; ++i)
    {
        if (lf->mantissa[i] == 0)
        {
            --lf->digits;
            --lf->exponent;
        }
        else
        {
            break;
        }
    }
}


// Удаление незначащих нулей
// void remove_zeros(long_float_t *lf)
// {
//     size_t i = MANTISSA_SIZE - lf->digits;
//     while (lf->mantissa[i] == 0 && i < MANTISSA_SIZE)
//     {
//         --lf->digits;
//         ++i;
//     }
// }


// Умножение чдлинных чисел
int mul_long_floats(long_float_t *l, long_float_t *r, long_float_t *res)
{
    int rc = ERR_OK;

    memset(res, 0, sizeof(long_float_t));
    normalize_number(l);
    normalize_number(r);

    size_t length = MANTISSA_SIZE * 2;
    int *buff = malloc(sizeof(int) * length);

    res->sign = l->sign * r->sign;
    res->exponent = l->exponent + r->exponent;
    res->digits = l->digits + r->digits;

    for (size_t i = MANTISSA_SIZE - 1; i != (size_t) -1; --i)
    {
        for (size_t j = MANTISSA_SIZE - 1; j != (size_t) -1; --j)
        {
            buff[i + j + 1] += l->mantissa[i] * r->mantissa[j];
        }
    }
    
    for (size_t i = length; i > 0; i--) {
        buff[i - 1] += buff[i] / 10;
        buff[i] %= 10; 
    }

    const int size = res->digits < MANTISSA_SIZE ? res->digits : MANTISSA_SIZE;
    copy_elems(buff + (length - res->digits), res->mantissa + (MANTISSA_SIZE - size), size);
    res->digits = size;

    normalize_number(res);
    
    free(buff);

    return rc;
}

// Печать длинного числа 
void print_long_float(long_float_t *lf)
{
    if (lf->digits == 0)
    {
        printf("0e0\n");
    }
    else if (abs(lf->exponent) >= MAX_EXPONENT )
    {
        printf("Переполнение экспоненты!\n");
    }
    else
    {
        if (lf->sign == MINUS)
        {
            printf("-");
        }
    
        printf("0.");
        print_array(lf->mantissa + MANTISSA_SIZE - lf->digits, lf->digits);
        printf("e%d\n", lf->exponent);
    }
}


// Печать ошибки
void print_error(int rc)
{
    switch (rc)
    {
    case ERR_READING:
        printf("Ошибка чтения строки\n");
        break;

    case ERR_EMPTY:
        printf("Введена пробельная строка\n");
        break;

    case ERR_NOT_NUMBER:
        printf("Введенная мантисса не является числом вещественного типа\n");
        break;

    case ERR_READING_MANTISSA:
        printf("Ошибка чтения мантиссы\n");
        break;

    case ERR_READING_EXPONENT:
        printf("Ошибка чтения порядка\n");
        break;

    default:
        printf("Число успешно считано\n");
        break;
    }
}
