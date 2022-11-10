#include <string.h>
#include <stdlib.h>

#include "../inc/sorts.h"

void bubble_sort(void *buff, size_t num, size_t size, int (*cmp)(const void *, const void *))
{
    void *temp = malloc(size);
    char *p = buff;

    for (size_t i = 0; i < num; ++i)
    {
        for (size_t j = 0; j < num - 1; ++j)
        {
            if (cmp(p + j * size, p + j * size + 1 * size) > 0)
            {
                memcpy(temp, p + j * size, size);
                memcpy(p + j * size, p + j * size + 1 * size, size);
                memcpy(p + j * size + 1 * size, temp, size);
            }
        }
    }

    free(temp);
}
