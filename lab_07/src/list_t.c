#include "../inc/list_t.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void free_node(node_t **head)
{
    while (head != NULL && *head != NULL)
    {
        pop_back(head);
    }
}


void push_back(node_t **head, const DATA_TYPE data)
{
    if (*head == NULL)
    {
        *head = malloc(sizeof(node_t));
        (*head)->data = data;
        (*head)->next = NULL;
    }
    else
    {
        node_t *cur = *head;
        
        while (cur->next != NULL)
        {
            cur = cur->next;
        }

        cur->next = malloc(sizeof(node_t));
        cur->next->data = data;
        cur->next->next = NULL;
    }
}

void list_int_lookup(node_t *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

node_t *find(node_t *head, const DATA_TYPE data, int (*comparator)(const void *, const void *), size_t *tries)
{
    node_t *cur_node = head;
    node_t *ret_find = NULL;

    while (cur_node != NULL && ret_find == NULL)
    {
        if (comparator(&cur_node->data, &data) == 0)
        {
            ret_find = cur_node;
        }
        else
        {
            ++*tries;
        }

        cur_node = cur_node->next;
    }

    return ret_find;
}

DATA_TYPE pop_head(node_t **head)
{
    size_t ret_data = 0;

    if (head != NULL && *head != NULL)
    {
        node_t *temp = *head;
        *head = (*head)->next;
        ret_data = temp->data;
        free(temp);
    }
    
    return ret_data;
}

DATA_TYPE pop_back(node_t **head)
{
    size_t ret_number = 0;

    if (head != NULL)
    { 
        if (*head != NULL)
        {
            node_t *temp_cur = *head;
            node_t *temp_next = temp_cur->next;

            if (temp_next == NULL)
            {
                ret_number = temp_cur->data;
                free(temp_cur);
                *head = NULL;
            }
            else
            {
                while (temp_next->next != NULL)
                {
                    temp_cur = temp_next;
                    temp_next = temp_cur->next;
                }

                ret_number = temp_next->data;
                free(temp_next);
                temp_cur->next = NULL;
            }
        }
    }

    return ret_number;
}
