#include "../inc/closed_hash.h"

#include <stdlib.h>
#include <stdio.h>

#define TRIES 2

closed_hash_table_t *create_cl_hash_table(size_t size)
{
    closed_hash_table_t *ht = malloc(sizeof(closed_hash_table_t));

    if (!ht)
        return ht;

    ht->data = calloc(sizeof(int), size);
    
    if (!ht->data)
    {
        free(ht);
        ht = NULL;
        return ht;
    }

    ht->size = size;
    ht->tries = TRIES; 
    ht->cur_tries = 0;
    ht->count = 0;
    ht->average = 0;

    return ht;
}

size_t cl_hash(closed_hash_table_t *ht, DATA_TYPE data)
{
    return data % ht->size;
}

void free_cl_hash_table(closed_hash_table_t *ht)
{
    if (ht)
    {
        if (ht->data)
        {
            free(ht->data);
            ht->data = NULL;
        }

        free(ht);
    }
}

int cl_find(closed_hash_table_t *ht, int data, size_t *tries)
{
    size_t ind = cl_hash(ht, data);
    
    *tries = 1;
    
    while (ht->data[ind] && *tries <= ht->size)
    {
        if (ht->data[ind] == data)
        {
            // printf("Элемент с значением %d найден в таблице с попытки №%zu\n", data, tries);
            // tries = -1;
            // break;
            // *count = tries;
            return 1;
        }
        ++*tries;
        ind = (ind + 1) % ht->size;
    }

    // if (tries != (size_t) -1)
    // {
    //     // printf("Элемента с значением %d нет в таблице, число попыток = %zu\n", data, tries);
    //     return 0;
    // }


    return 0;
}

void cl_insert(closed_hash_table_t **ht, DATA_TYPE data)
{
    size_t tries = 1;

    size_t ind = cl_hash(*ht, data);
    // printf("in ins: %d", data);

    if (!(*ht)->data[ind])
    {
        (*ht)->data[ind] = data;
        (*ht)->cur_tries += tries;
        ++(*ht)->count;
        (*ht)->average = (*ht)->cur_tries / ((double) (*ht)->count); 
        // printf("Среднее число сравнений: %lf\n", (*ht)->average);
    }
    else
    {
        while ((*ht)->data[ind] && (*ht)->data[ind] != data)
        {
            ind = (ind + 1) % (*ht)->size;
            ++tries;

            if (tries - 1 > (*ht)->size)
            {
                printf("В таблице больше нет места, таблица была реструктурирована!\n");
                *ht = restruct_cl_ht(*ht);
                ind = cl_hash(*ht, data);
                // break;
            }

            // TODO
            // if (tries > (*ht)->tries)
            // {
            //     *ht = restruct_cl_ht(*ht);
            //     printf("Превышено максимальное число сравнений, таблица была реструктурирована!\n");
            //     cl_insert(ht, data);
            // }
        }

        // if (tries <= (*ht)->tries)
        // {
        // if (data == 31)
            // printf("ind %zu, data %d, size: %zu", ind, data, (*ht)->size);
        (*ht)->data[ind] = data; 
        // }

        // cl_insert(ht, data);
        (*ht)->cur_tries += tries;
        ++(*ht)->count;
        (*ht)->average = (*ht)->cur_tries / ((double) (*ht)->count);
        // printf("Среднее число сравнений: %lf\n", (*ht)->average);

        if ((*ht)->average > (*ht)->tries)
        {
            *ht = restruct_cl_ht(*ht);
            printf("Среднее число сравнений %zu превысило максимальное, таблица была реструктурирована!\n", (*ht)->tries);
            cl_insert(ht, data);
        }
        
    }   
    // printf("Среднее число сравнений: %lf\n", (*ht)->average); 
}

closed_hash_table_t *restruct_cl_ht(closed_hash_table_t *ht)
{
    // int *new = calloc(sizeof(DATA_TYPE),  ht->size * 2);
    closed_hash_table_t *new = create_cl_hash_table(ht->size * 3);
    new->tries = ht->tries;

    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->data[i])
        {
            // printf("data ins: %d", ht->data[i]);
            cl_insert(&new, ht->data[i]);
        }
    }

    free_cl_hash_table(ht);

    return new;
}

void look_up_cl_hash_table1(closed_hash_table_t *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->data[i])
        {
            printf("%d\n", ht->data[i]);
        }
        else
        {
            printf("-----\n");
        }
    }
}

void look_up_cl_hash_table2(closed_hash_table_t *ht)
{
    for (size_t i = 0; i < ht->size; ++i)
    {
        if (ht->data[i])
        {
            printf("POS: %zu, DATA:%d\n", i, ht->data[i]);
        }
    }

    printf("Среднее число сравнений: %lf\n", ht->average);
}
// void cl_del(closed_hash_table_t *ht);
