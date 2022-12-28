#ifndef __UTILS_H__
#define __UTILS_H__

#include <stddef.h>

#include "../inc/error_t.h"

error_t realloc_array(long long **arr, size_t new_size);

error_t alloc_array(long long **arr, size_t size);

void print_array_int(int *arr, size_t size);

#include <unistd.h>
void print_array_size_t(size_t *arr, size_t size);
void print_array_long(long *arr, size_t size);
void print_array_SSIZE_t(ssize_t *arr, size_t size);

#endif  // __UTILS_H__
