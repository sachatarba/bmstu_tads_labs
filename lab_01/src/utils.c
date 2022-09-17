#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/utils.h"


// Проверка является ли символ знаком
int is_sign(const char symbol)
{
    int rc = 0;

    if (symbol == '+' || symbol == '-')
    {
        rc = 1;
    }

    return rc;
}

// Проверка конца строки
int is_end(const char symbol)
{
    int rc = 0;

    if (symbol == '\0' || symbol == '\r' || symbol == '\n')
    {
        rc = 1;
    }

    return rc;
}

// Итерация по строке, пока символ является пробельным
// Направление итерации задается параметром direction 
const char *iter_string_while_whitespace(const char *string, direction_t direction)
{
    switch (direction)
    {
    case FORWARD:
        while (isspace(*string))
        {
            ++string;
        }

        break;
    
    case BACK:
        while (isspace(*string))
        {
            --string;
        }

        break;
    }

    return string;
}


// Копирует цифры из строки, пока не встретится первый символ, не являющийся цифрой.
const char *copy_digits_to_array(const char *digits, unsigned char *array, size_t *len)
{
    size_t i = 0;

    while (isdigit(*digits) && i < *len)
    {
        array[i++] = *(digits++) - '0';
    }

    *len = i;

    return digits;
}

// Копирует цифры из массива src в массив dst
void copy_elems(int *src, unsigned char *dst, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        dst[i] = (unsigned char) src[i];
    }
}


// Проверяет является ли строка пробельной
int is_string_whitespace(const char *string)
{
    int rc = 1;

    while (*string)
    {
        if (!isspace(*(string++)))
        {
            rc = 0;
        }
    }

    return rc;
}


// Удаляет пробелы с конца и начала строки
char *strip(char *string)
{
    char *start = (char*) iter_string_while_whitespace(string, FORWARD);

    size_t len = strlen(string);

    string = (char*) iter_string_while_whitespace(string + len - 1, BACK);

    *(string + 1) = '\0';

    return start;
}


// Печать массива char
void print_array(const unsigned char *array, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%u", array[i]);
    }
}

// Печать массива int
void print_array_int(const int *array, const size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%d", array[i]);
    }
}
