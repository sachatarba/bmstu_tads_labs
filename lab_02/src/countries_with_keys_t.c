#include "../inc/countries_with_keys_t.h"
#include "../inc/comparator.h"

void sort_keys(countries_with_keys_t *countries, void (*sort)(void*, size_t, size_t, int (*cmp)(const void *, const void *)),\
int (*cmp)(const void *, const void *))
{
    sort(countries->keys, countries->countries->size, sizeof(*countries->keys), cmp);
}

error_t print_countries_in_order_of_keys(FILE *fp, countries_with_keys_t *table)
{
    error_t rc = OK;

    if (table != NULL)
    {
        for (size_t i = 0; i < table->countries->size; ++i)
        {
            fprintf(fp, "---------------------------------------------------\n");
            print_country(fp, &table->countries->country[table->keys[i].id]);
        }
        fprintf(fp, "---------------------------------------------------\n");
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}

error_t create_table_keys(countries_table_t *countries, countries_with_keys_t *keys)
{
    error_t rc = OK;

    if (countries != NULL)
    {
        if (keys != NULL)
        {
            keys->countries = countries;

            keys->keys = malloc(sizeof(*(keys->keys)) * countries->size);

            for (size_t i = 0; i < countries->size; ++i)
            {
                strcpy(keys->keys[i].name, countries->country[i].name);
                keys->keys[i].id = i;
            }
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}

error_t print_keys(FILE *fp, countries_with_keys_t *keys)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (keys != NULL)
        {
            for (size_t i = 0; i < keys->countries->size; ++i)
            {
                fprintf(fp, "--------------------------------------------\n");
                fprintf(fp, "ID: %zu\n", keys->keys[i].id);
                fprintf(fp, "Название страны: %s\n", keys->keys[i].name);
            }
            fprintf(fp, "--------------------------------------------\n");
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }

    return rc;
}

error_t free_keys(countries_with_keys_t *keys)
{
    error_t rc = OK;

    if (keys != NULL)
    {
        free(keys->keys);
        keys->keys = NULL;
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}
