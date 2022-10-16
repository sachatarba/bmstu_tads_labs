#include <stdio.h>
#include <string.h>

#include "../inc/tourism_t.h"
#include "../inc/string_utils.h"
#include "../inc/error_t.h"

#define BUFF_SIZE 256

#define NAMES_SIZE 4
#define TOURS_SIZE 3

const char *types_of_main_tour[] = 
{
     "экскурсионный", "пляжный", "спортивный" 
};

const char *names[][NAMES_SIZE] = 
{
    { "природа", "история", "искусство" },

    { "зима", "весна", "лето", "осень" },

    { "горные лыжи", "серфинг", "восхождения" }

};

error_t find_name(tourism_name_t name, char *name_to_find, abstract_enum_t *ind)
{
    error_t rc = ERR_NO_NAME;

    for (int i = 0; i < NAMES_SIZE; ++i)
    {
        if (names[name][i] != NULL)
        {
            if (!strcmp(names[name][i], name_to_find))
            {
                *ind = i;
                rc = OK;
            }    
        }
    }

    return rc;
}

error_t find_main_tour(char *name_to_find, abstract_enum_t *ind)
{
    error_t rc = ERR_NO_NAME;

    for (int i = 0; i < TOURS_SIZE; ++i)
    {
        if (!strcmp(types_of_main_tour[i], name_to_find))
        {
            *ind = i;
            rc = OK;
        }
    }

    return rc;
}

error_t read_main_tour_name(FILE *fp, tourism_name_t *name)
{
    error_t rc = OK;

    char buff[BUFF_SIZE] = { '\0' };
    rc = read_string(fp, buff, BUFF_SIZE);

    if (rc == OK)
    {
        abstract_enum_t enm;
        rc = find_main_tour(buff, &enm);

        if (rc == OK)
        {
            *name = (tourism_name_t) enm;
        }
    }
    
    return rc;
}

void print_main_tour_name(FILE *fp, tourism_name_t name)
{
    fprintf(fp, "Основной вид туризма: %s\n", types_of_main_tour[name]);
}

error_t read_enum(FILE *fp, tourism_t *tour, tourism_name_t name)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            char buff[BUFF_SIZE] = { '\0' };

            if (fgets(buff, BUFF_SIZE, fp) != NULL)
            {
                abstract_enum_t ind;                
                char *buff_strip = strip(buff);

                if (buff_strip != NULL && strlen(buff_strip) > 0)
                {
                    string_to_lower(buff_strip);
                    rc = find_name(name, buff_strip, &ind);

                    if (rc == OK)
                    {
                        abstract_enum_t *ptr_to_enum_in_tour = (abstract_enum_t *) tour;
                        *ptr_to_enum_in_tour = ind; 
                    }
                }
                else
                {
                    rc = ERR_EMPTY_INPUT;
                }
            }
            else
            {
                rc = ERR_READING;
            }
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

error_t read_excursions(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            if ((rc = read_enum(fp, tour, EXCURSIONS)) == OK)
            {
                if (fscanf(fp, "%zu\n", &tour->excursions.number_of_objects) != 1)
                {
                    rc = ERR_READING;
                }
            }
            
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

error_t print_excursions(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            fprintf(fp, "Вид объектов: %s\n", names[EXCURSIONS][tour->excursions.type_of_objets]);
            fprintf(fp, "Число объектов: %zu\n", tour->excursions.number_of_objects);
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

error_t read_beachfront(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            if ((rc = read_enum(fp, tour, BEACHFRONT)) == OK)
            {
                if (fscanf(fp, "%zu\n %zu\n", &tour->beachfront.air_temperature, &tour->beachfront.water_temperature) != 2)
                {
                    rc = ERR_READING;
                }
            }           
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

error_t print_beachfront(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            fprintf(fp, "Основной сезон: %s\n", names[BEACHFRONT][tour->beachfront.main_season]);
            fprintf(fp, "Температура воздуха: %zu\n", tour->beachfront.air_temperature);
            fprintf(fp, "Температура воды: %zu\n", tour->beachfront.water_temperature);
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

error_t read_sports(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            if ((rc = read_enum(fp, tour, SPORTS)) == OK)
            {
                if (fscanf(fp, "%zu\n", &tour->sports.min_holiday_cost) != 1)
                {
                    rc = ERR_READING;
                }
            }
            
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

error_t print_sports(FILE *fp, tourism_t *tour)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (tour != NULL)
        {
            fprintf(fp, "Основной вид спорта: %s\n", names[SPORTS][tour->sports.main_sport]);
            fprintf(fp, "Минимальная стоимость отдыха: %zu\n", tour->sports.min_holiday_cost);
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
