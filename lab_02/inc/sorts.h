#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

void bubble_sort(void *buff, size_t num, size_t size, int (*cmp)(const void *, const void *));

#endif
