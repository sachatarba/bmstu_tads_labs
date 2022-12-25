#ifndef __CLOSED_HASH_H__
#define __CLOSED_HASH_H__

#define DATA_TYPE int

#include <stddef.h>

struct closed_hash
{
    DATA_TYPE *data;
    size_t size;
    size_t tries;
    size_t cur_tries;
    size_t count;
    double average;
};

typedef struct closed_hash closed_hash_table_t;

closed_hash_table_t *create_cl_hash_table(size_t size);

size_t cl_hash(closed_hash_table_t *ht, DATA_TYPE data);

void free_cl_hash_table(closed_hash_table_t *ht);

int cl_find(closed_hash_table_t *ht, DATA_TYPE data);

void cl_insert(closed_hash_table_t **ht, DATA_TYPE data);

void look_up_cl_hash_table2(closed_hash_table_t *ht);

void look_up_cl_hash_table1(closed_hash_table_t *ht);

closed_hash_table_t *restruct_cl_ht(closed_hash_table_t *ht);
// void cl_del(closed_hash_table_t *ht);

#endif
