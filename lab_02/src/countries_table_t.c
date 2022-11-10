#include "../inc/countries_table_t.h"
#include "../inc/string_utils.h"

#define RESIZE 2
// #define GET_SPORT(str) for (size_t i = 0; i < NAMES_SIZE) if (!strcmp(str, names[2][i])) break, i;

const char *sports[] = 
{ "горные лыжи", 
  "серфинг", 
  "восхождения" 
};


error_t create_table(countries_table_t *countries, size_t size)
{
    error_t rc = OK;

    if (countries != NULL)
    {
        countries->resize = RESIZE;
        countries->size_allocated = size > 0 ? size * countries->resize : countries->resize;
        countries->size = 0;
        countries->country = malloc(sizeof(country_t) * countries->size_allocated);

        if (countries->country == NULL)
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

error_t free_table(countries_table_t *countries)
{
    error_t rc = OK;

    if (countries != NULL)
    {
        free(countries->country);
        countries->size = 0;
        countries->size_allocated = 0;
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}

error_t append_country(FILE *fp, countries_table_t *countries)
{
    error_t rc = OK;

    if (countries->size >= countries->size_allocated)
    {
        rc = resize_countries_table(countries, countries->size_allocated * countries->resize);
    }

    if (rc == OK && (rc = read_country(fp, &(countries->country[countries->size]))) == OK)
    {
        ++countries->size;
    }

    return rc;
}


error_t resize_countries_table(countries_table_t *countries, size_t new_size)
{
    error_t rc = OK;

    if (countries != NULL)
    {
        if (new_size > 0)
        {
            country_t *countries_temp = realloc(countries->country, new_size * sizeof(country_t));

            if (countries_temp != NULL)
            {
                countries->country = countries_temp;
                countries->size_allocated = new_size;

                if (new_size < countries->size)
                {
                    countries->size = new_size;
                }
            }
            else
            {
                rc = ERR_INV_PTR;
            }
        }
        else
        {
            rc = ERR_BAD_SIZE;
        }
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}

error_t delete_country_by_name(countries_table_t *countries, char *name)
{
    error_t rc = OK;

    if (countries != NULL && name != NULL)
    {
        for (size_t i = 0; i < countries->size; ++i)
        {
            if (!strcmp(countries->country[i].name, name))
            {
                
                for (size_t j = i; j < countries->size - 1; ++j) // 0 1 -> 1
                {
                    countries->country[j] = countries->country[j + 1];
                }

                --countries->size;
                --i;
            }
        }

        if (countries->size && countries->size_allocated / countries->size >= 3) // TODO: задефайнить в константу с нормальным именем
        {
            rc = resize_countries_table(countries, countries->size_allocated / 3 * countries->resize);
        }

    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}

error_t print_table(FILE *fp, countries_table_t *countries)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (countries != NULL)
        {
            for (size_t i = 0; i < countries->size; ++i)
            {
                fprintf(fp, "---------------------------------------------------\n");
                print_country(fp, countries->country + i);
            }
            fprintf(fp, "---------------------------------------------------\n");
        }
        else
        {
            rc = ERR_INV_PTR;
        }
    }
    else
    {
        rc = ERR_NO_FILE;
    }

    return rc;
}

int get_sport(char *sport)
{
    for (size_t i = 0; i < NAMES_SIZE; ++i) 
        if (!strcmp(sport, sports[i]))
            return i;
    return -1;
}

error_t find_by_mainland_and_sport(countries_table_t *table)
{
    error_t rc = OK;

    if (table != NULL)
    {
        char mainland[BUFF] = "\0";
        char sport[BUFF] = "\0";

        printf("Введите материк: ");
        rc = read_string(stdin, mainland, BUFF);
        if (rc == OK)
        {
            printf("Введите вид спорта: ");
            rc = read_string(stdin, sport, BUFF);
        }

        if (rc == OK)
        {
            int sport_index = get_sport(sport);

            for (size_t i = 0; i < table->size; ++i)
            {   
                printf("---------------------------------------------------\n");
                if (!strcmp(table->country[i].mainland, mainland) && table->country[i].main_tour_name == SPORTS\
                 && sport_index == (int) table->country[i].main_tour_type.sports.main_sport)
                    print_country(stdout, &table->country[i]);
            }

            printf("---------------------------------------------------\n");
        }
    }
    else
    {
        rc = ERR_INV_PTR;
    }

    return rc;
}
