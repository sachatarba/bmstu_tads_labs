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
    unsigned char mantissa[MANTISSA_SIZE];
    int exponent;
    sign_t sign;
} long_float_t;

int set_sign(long_float_t *long_number, char symbol);

void shift_number(long_float_t *lf);

int copy_mantissa(long_float_t *long_number, const char *string, char **end);

int copy_exponent(long_float_t *long_number, const char *string, char **end);

int read_long_float(long_float_t *long_number);

void normalize_number(long_float_t *lf);

void print_long_float(long_float_t *long_number);

int mul_long_floats(long_float_t *l, long_float_t *r, long_float_t *res);

void print_long_float(long_float_t *long_number);

void print_error(int rc);
