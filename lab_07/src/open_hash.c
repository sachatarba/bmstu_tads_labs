#include "../inc/open_hash.h"
#include "../inc/comparator.h"
#include "../inc/list_t.h"

#include <stdlib.h>
#include <stdio.h>

#define TRIES 2

open_hash_table_t *create_op_hash_table(size_t size)
{
    open_hash_table_t *ht = malloc(sizeof(open_hash_table_t));

    if (!ht)
        return ht;

    ht->lists = calloc(sizeof(node_t *), size);

    if (!ht->lists)
    {
        free(ht);
        return NULL;
    }

    ht->size = size;
    ht->tries = TRIES;

    return ht;
}

size_t op_hash(open_hash_table_t *ht, DATA_TYPE data)
{
    return data % ht->size;
}

void free_op_hash_table(open_hash_table_t *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->lists[i])
            free_node(ht->lists + i);
    }
}

int op_find(open_hash_table_t *ht, DATA_TYPE data)
{
    size_t ind = op_hash(ht, data);

    size_t tries = 0;
    node_t *temp = find(ht->lists[ind], data, copmare_int, &tries);
    
    if (temp) {
        printf("Элемент со значением %d найден в таблице с попытки %zu\n", temp->data, tries);
        return 1;
    }
    else {
        printf("Элемент не найден в таблице, число попыток = %zu\n", tries);
        return 0;
    }
}

void op_insert(open_hash_table_t **ht, DATA_TYPE data)
{
    size_t ind = op_hash(*ht, data);

    push_back((*ht)->lists + ind, data);
}

void look_up_op_hash_table2(open_hash_table_t *ht);

void look_up_op_hash_table1(open_hash_table_t *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->lists[i])
        {
            printf("POS: %zu, DATA: ", i);
            list_int_lookup(ht->lists[i]);
        }
    }
}

open_hash_table_t *restruct_op_ht(open_hash_table_t *ht)
{
    open_hash_table_t *new = create_op_hash_table(ht->size * 3);

    DATA_TYPE temp = 0;
    // size_t ind = 0;
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->lists[i])
        {
            while (ht->lists[i] != NULL)
            {
                temp = pop_head(ht->lists + i);
                // ind = op_hash(new, temp);
                op_insert(&new, temp);
            }
        }
    }

    free_op_hash_table(ht);

    return new;
}