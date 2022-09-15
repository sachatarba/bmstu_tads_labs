#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


#include "../headers/long_float.h"
#include "../headers/utils.h"

#define BUFF_SIZE 100

#define ERR_OK                0
#define ERR_READING           1
#define ERR_EMPTY             2
#define ERR_NOT_NUMBER        3
#define ERR_READING_MANTISSA  4
#define ERR_READING_EXPONENT  5

#define RADIX 10

#define NO_SPACE '\0'

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

// void normalize_number(long_float_t *long_number)
// {

// }

void print_long_float(long_float_t *long_number)
{
    print_array(long_number->mantissa, long_number->digits, NO_SPACE);
    printf(" E %d\n", long_number->exponent);
}

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
