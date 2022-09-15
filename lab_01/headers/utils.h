#include <stddef.h>

typedef enum
{
    BACK,
    FORWARD
} direction_t;

int is_sign(const char symbol);

int is_end(const char symbol);

char *strip(char *string);

int is_string_whitespace(const char *string);

const char *copy_digits_to_array(const char *digits, char *array, size_t *len);

void print_array(char *array, const size_t len, const char separator);

const char *iter_string_while_whitespace(const char *string, direction_t direction);
