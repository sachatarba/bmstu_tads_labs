#include <stddef.h>

#define MANTISSA_SIZE 30

typedef enum
{
    MINUS,
    PLUS
} sign_t;

typedef struct
{
    size_t digits;
    char mantissa[MANTISSA_SIZE];
    int exponent;
    sign_t sign;
} long_float_t;

int set_sign(long_float_t *long_number, char symbol);

int copy_mantissa(long_float_t *long_number, const char *string, char **end);

int read_long_float(long_float_t *long_number);

void print_long_float(long_float_t *long_number);

void mul_long_floats(long_float_t *long_number_1, long_float_t *long_number_2);

void print_long_float(long_float_t *long_number);
