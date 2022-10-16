#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../inc/string_utils.h"
#include "../inc/error_t.h"

#define BUFF_SIZE 200

// Итерация по строке, пока символ является пробельным
// Направление итерации задается параметром direction 
const char *iter_string_while_whitespace(const char *string, direction_t direction)
{
    while (isspace(*string))
    {
            string += direction;
    }

    return string;
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

char *string_to_lower(char *string)
{
    char *sb = string;

    while (*string)
    {
        *string = tolower(*string);
        ++string;
    }

    return sb;
}

error_t read_string(FILE *fp, char *dst, size_t max_size)
{
    error_t rc = OK;

    size_t size = max_size + BUFF_SIZE;
    char *buff = malloc(size * sizeof(char));
    
    if (buff != NULL)
    {
        if (fgets(buff, size, fp) != NULL)
        {
            char *buff_strip = strip(buff);

            if (buff_strip != NULL && strlen(buff_strip) > 0)
            {
                if (strlen(buff_strip) <= max_size - 1)
                {
                    strcpy(dst, buff_strip);
                }
                else
                {
                    rc = ERR_BUFF_OVERLOAD;
                }
            }
            else
            {
                rc = ERR_EMPTY_INPUT;
            }
        }
        else
        {
            rc = ERR_READING;
        }

        free(buff);
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}