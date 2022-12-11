#ifndef __QUEUE_LIST_T_H__
#define __QUEUE_LIST_T_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

struct node
{
    void *data;
    struct node *next;
};

typedef struct node node_t;

struct queue_list
{
    node_t *head;
    node_t *end;
    size_t size;
    size_t max_size;
};

typedef struct queue_list queue_list_t;

queue_list_t *create_list(size_t size);

bool is_full_list(queue_list_t *queue);

bool is_empty_list(queue_list_t *queue);

int push_list(queue_list_t *queue, void *data);

int pop_list(queue_list_t *queue, void **data);

void destroy_list(queue_list_t **queue_list);

void print_list(queue_list_t *queue);

// void print(queue_list_t *queue);

#endif //  __QUEUE_LIST_T_H__
