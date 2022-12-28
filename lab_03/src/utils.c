#include <stdio.h>
#include <stdlib.h>

#include "../inc/utils.h"

error_t realloc_array(long long **arr, size_t new_size)
{
    error_t rc = OK;

    long long *temp_arr = NULL;
    
    if (new_size > 0)
    {
        temp_arr = realloc(*arr, new_size * sizeof(long long));
    }
    else
    {
        rc = ERR_REALLOC;
    }

    if (temp_arr != NULL)
    {
        *arr = temp_arr;
    }
    else
    {
        rc = ERR_REALLOC;
    }

    return rc;
}

error_t alloc_array(long long **arr, size_t size)
{
    error_t rc = OK;

    long long *temp_arr = malloc(size * sizeof(long long));

    if (temp_arr != NULL)
    {
        *arr = temp_arr;
    }
    else
    {
        rc = ERR_ALLOC;
    }

    return rc;
}

void print_array_int(int *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
}

#include <unistd.h>
void print_array_long(long *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%ld ", arr[i]);
    }
}

void print_array_SSIZE_t(ssize_t *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%zd ", arr[i]);
    }
}

void print_array_size_t(size_t *arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%zu ", arr[i]);
    }
}
