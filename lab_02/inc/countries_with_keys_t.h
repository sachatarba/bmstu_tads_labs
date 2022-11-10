#ifndef __COUNTRIES_WITH_KEYS_T__
#define __COUNTRIES_WITH_KEYS_T__


#include "../inc/countries_table_t.h"

struct countries_with_keys
{
    countries_table_t *countries;
    
    struct keys
    {
        size_t id; // число, показывающее, на какой позиции находится запись в таблице 
        char name[BUFF]; // названия страны - ключ
    } *keys;
};

typedef struct countries_with_keys countries_with_keys_t;

void sort_keys(countries_with_keys_t *countries, void (*sort)(void*, size_t, size_t, int (*cmp)(const void *, const void *)),\
int (*cmp)(const void *, const void *));

error_t print_countries_in_order_of_keys(FILE *fp, countries_with_keys_t *countries);

error_t create_table_keys(countries_table_t *countries, countries_with_keys_t *keys);

error_t print_keys(FILE *fp, countries_with_keys_t *keys);

error_t free_keys(countries_with_keys_t *keys);

#endif
