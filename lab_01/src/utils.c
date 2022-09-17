#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/utils.h"

int is_sign(const char symbol)
{
    int rc = 0;

    if (symbol == '+' || symbol == '-')
    {
        rc = 1;
    }

    return rc;
}

int is_end(const char symbol)
{
    int rc = 0;

    if (symbol == '\0' || symbol == '\r' || symbol == '\n')
    {
        rc = 1;
    }

    return rc;
}

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

void copy_elems(int *src, unsigned char *dst, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        dst[i] = (unsigned char) src[i];
        // printf("%d", src[i]);
    }
}

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

char *strip(char *string)
{
    char *start = (char*) iter_string_while_whitespace(string, FORWARD);

    size_t len = strlen(string);

    string = (char*) iter_string_while_whitespace(string + len - 1, BACK);

    *(string + 1) = '\0';

    return start;
}

void print_array(const unsigned char *array, const size_t len, const char separator)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%u%c", array[i], separator);
    }
}

void print_array_int(const int *array, const size_t len, const char separator)
{
    for (size_t i = 0; i < len; ++i)
    {
        printf("%d%c", array[i], separator);
    }
}
