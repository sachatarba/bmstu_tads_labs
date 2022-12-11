#include <stdlib.h>

#include <stdio.h>

#include "../inc/queue_list_t.h"

queue_list_t *create_list(size_t size)
{
    queue_list_t *queue = malloc(sizeof(queue_list_t));

    queue->max_size = size;
    queue->head = NULL;
    queue->end = NULL;
    queue->size = 0;

    return queue;
}

bool is_full_list(queue_list_t *queue)
{
    return queue->max_size == queue->size;
}

bool is_empty_list(queue_list_t *queue)
{
    return queue->size == 0;
}

int push_list(queue_list_t *queue, void *data)
{
    if (is_full_list(queue))
        return 1;
    
    node_t *node = malloc(sizeof(node_t));
    // data = node;
    node->data = data;
    node->next = NULL;

    if (is_empty_list(queue))
    {
        queue->head = node;
        queue->end = node;
    }
    else
    {
        // node->next = queue->head;
        // queue->head = node;
        queue->end->next = node;
        queue->end = node;
    }

    ++queue->size;

    return 0;
}

int pop_list(queue_list_t *queue, void **data)
{
    if (is_empty_list(queue))
        return 1;
    
    *data = queue->head->data;

    node_t *temp = queue->head;
    queue->head = queue->head->next;
    free(temp);
    --queue->size;

    if (is_empty_list(queue))
        queue->end = NULL;

    return 0;
}

void destroy_list(queue_list_t **queue_list)
{
    void *p = NULL;

    while ((*queue_list)->head)
    {
        pop_list(*queue_list, &p);
    }

    free(*queue_list);
    *queue_list = NULL;
}

void print_list(queue_list_t *queue)
{
    if (queue->size == 0)
    {
        printf("Очередь пуста!\n");
    }
    else
    {
        for (node_t *temp = queue->head; temp; temp = temp->next)
        {
            printf("%d\n", *((int*) temp->data));
        }
    } 
}

// void print(queue_list_t *queue);
