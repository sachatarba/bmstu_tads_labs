#ifndef __OPEN_HASH_H__
#define __OPEN_HASH_H__

// #define DATA_TYPE int

#include "../inc/list_t.h"

#include <stddef.h>

struct open_hash
{
    node_t **lists;
    size_t size;
    size_t tries;
    size_t cur_tries;
    size_t count;
    double average;
};

typedef struct open_hash open_hash_table_t;

open_hash_table_t *create_op_hash_table(size_t size);

size_t op_hash(open_hash_table_t *ht, DATA_TYPE data);

void free_op_hash_table(open_hash_table_t *ht);

int op_find(open_hash_table_t *ht, DATA_TYPE data, size_t *count);

void op_insert(open_hash_table_t **ht, DATA_TYPE data);

void look_up_op_hash_table2(open_hash_table_t *ht);

void look_up_op_hash_table1(open_hash_table_t *ht);

open_hash_table_t *restruct_op_ht(open_hash_table_t *ht);
// void cl_del(closed_hash_table_t *ht);

#endif
