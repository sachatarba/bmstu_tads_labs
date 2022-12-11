#include <stdio.h>
#include <assert.h>

#include "../inc/queue_array_t.h"

int push_array(queue_array_t *queue, void *data)
{
    if (is_full_array(queue))
        // assert(0);
        return 1;

    // data = queue->data_end;

    if (is_empty_array(queue))
    {
        queue->data_beg = queue->p_data;
        queue->data_end = queue->data_beg;
    }

    *queue->data_end = data;
    ++queue->data_end;
    ++queue->size;

    return 0;
}

int pop_array(queue_array_t *queue, void **data)
{
    if (is_empty_array(queue))
        return 1;

    *data = *queue->data_beg;
    ++queue->data_beg;
    --queue->size;

    if (is_empty_array(queue))
    {
        queue->data_beg = NULL;
        queue->data_end = NULL;
    }

    return 0;
}

queue_array_t *create_array(size_t size)
{
    queue_array_t *queue = calloc(sizeof(queue_array_t), 1);
    queue->p_data = malloc(sizeof(void *) * size);
    queue->size = 0;
    queue->data_beg = NULL;
    queue->data_end = NULL;
    queue->max_size = size;

    return queue;
}

bool is_full_array(queue_array_t *queue)
{
    return queue->size == queue->max_size;
}

bool is_empty_array(queue_array_t *queue)
{
    return queue->size == 0;
}

void destroy_array(queue_array_t **queue)
{
    free((*queue)->p_data);
    free(*queue);
    *queue = NULL;
}

void print_array(queue_array_t *queue)
{
    if (queue->size == 0)
    {
        printf("Очередь пуста!\n");
    }
    else
    {
        void **p = queue->data_beg;
        for (size_t i = 0; i < queue->size; i++)
        {
            printf("%d\n", *((int*) *p));
            ++p;
        }
    } 
}
