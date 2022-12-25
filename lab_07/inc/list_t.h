#ifndef __LIST_T_H__
#define __LIST_T_H__

#include <stddef.h>

#define DATA_TYPE int

typedef struct node_lst node_t;

struct node_lst
{
    DATA_TYPE data;
    node_t *next;
};

void push_back(node_t **head, const DATA_TYPE data);

DATA_TYPE pop_back(node_t **head);

DATA_TYPE pop_head(node_t **head);

void free_node(node_t **head);

node_t *find(node_t *head, const DATA_TYPE data, int (*comparator)(const void *, const void *), size_t *tries);

void list_int_lookup(node_t *head);

#endif //  __LIST_T_H__
