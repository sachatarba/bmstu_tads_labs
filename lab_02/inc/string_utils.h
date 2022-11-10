#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include "../inc/error_t.h"

typedef enum
{
    BACK = -1,
    FORWARD = 1
} direction_t;

char *strip(char *string);

int is_string_whitespace(const char *string);

const char *iter_string_while_whitespace(const char *string, direction_t direction);

char *string_to_lower(char *string);

error_t read_string(FILE *fp, char *dst, size_t max_size);

error_t parse_number(char *buffer, long long *number);

error_t read_size_number(FILE *fp, size_t *size);

#endif 