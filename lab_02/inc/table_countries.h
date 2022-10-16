#ifndef __TABLE_COUNTRIES_H__
#define __TABLE_COUNTRIES_H__

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/country_t.h"
#include "../inc/error_t.h"

struct countries_table
{
    size_t size_allocated;
    size_t size;
    size_t resize;
    country_t *country;
};

typedef struct countries_table countries_table_t;

error_t create_table(countries_table_t *countries, size_t size);

error_t free_table(country_t *countries);

error_t resize_countries_table(countries_table_t *countries, size_t new_size);

error_t append_country(FILE *fp, countries_table_t *countries);

error_t delete_country_by_name(countries_table_t *countries, char *name);

error_t print_table(FILE *fp, countries_table_t *countries);

#endif
