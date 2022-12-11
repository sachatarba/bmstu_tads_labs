#ifndef __QUEUE_ARRAY_T_H__
#define __QUEUE_ARRAY_T_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../inc/mytime.h"

struct queue_array
{
    void **p_data;
    void **data_beg;
    void **data_end;
    size_t size;
    size_t max_size;
};

typedef struct queue_array queue_array_t;

queue_array_t *create_array(size_t size);

bool is_full_array(queue_array_t *queue);

bool is_empty_array(queue_array_t *queue);

int push_array(queue_array_t *queue, void *data);

int pop_array(queue_array_t *queue, void **data);

void destroy_array(queue_array_t **queue_array);

void print(queue_array_t *queue);

void print_array(queue_array_t *queue);

#endif //  __QUEUE_ARRAY_T_H__
