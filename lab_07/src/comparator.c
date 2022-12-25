#include "../inc/comparator.h"

int copmare_int(const void *a, const void *b)
{
    return *((int *) a) - *((int *) b);
}
