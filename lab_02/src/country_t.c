#include "../inc/country_t.h"
#include "../inc/string_utils.h"
#include "../inc/error_t.h"

error_t read_main_tour_type(FILE *fp, country_t *country)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (country != NULL)
        {
            switch (country->main_tour_name)
            {
            case EXCURSIONS:
                rc = read_excursions(fp, &country->main_tour_type);
                break;
            
            case BEACHFRONT:
                rc = read_beachfront(fp, &country->main_tour_type);
                break;

            case SPORTS:
                rc = read_sports(fp, &country->main_tour_type);
                break;

            default:
                rc = ERR_NO_NAME;
                break;
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


error_t print_main_tour_type(FILE *fp, country_t *country)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (country != NULL)
        {
            switch (country->main_tour_name)
            {
            case EXCURSIONS:
                rc = print_excursions(fp, &country->main_tour_type);
                break;
            
            case BEACHFRONT:
                rc = print_beachfront(fp, &country->main_tour_type);
                break;

            case SPORTS:
                rc = print_sports(fp, &country->main_tour_type);
                break;

            default:
                rc = ERR_NO_NAME;
                break;
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

error_t read_country(FILE *fp, country_t *country)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (country != NULL)
        {
            if (fp == stdin)
                printf("Введите навзание страны: ");
            rc = read_string(fp, country->name, BUFF);

            if (rc == OK)
            {
                if (fp == stdin)
                        printf("Введите число житилей: ");

                // if (fscanf(fp, "%zu\n", &country->number_of_inhabitants) == 1)
                if (read_size_number(fp, &country->number_of_inhabitants) == OK)
                {
                    if (fp == stdin)
                        printf("Введите навзание столицы: ");
                    
                    rc = read_string(fp, country->capital, BUFF);

                    if (rc == OK)
                    {
                        if (fp == stdin)
                            printf("Введите навзание материка:");
                        rc = read_string(fp, country->mainland, BUFF);

                        if (rc == OK)
                        {
                            if (fp == stdin)
                                printf("Введите прививку/пцр:");
                            rc = read_string(fp, country->vaccination, BUFF);

                            if (rc == OK)
                            {
                                 
                                if (fp == stdin)
                                    printf("Введите тип туризма:");
                                rc = read_main_tour_name(fp, &country->main_tour_name);
                                
                               if (rc == OK)
                               {
                                    rc = read_main_tour_type(fp, country);
                               }
                            }
                        }
                    }
                }
                else
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

error_t print_country(FILE *fp, country_t *country)
{
    error_t rc = OK;

    if (fp != NULL)
    {
        if (country != NULL)
        {
            fprintf(fp, "Название страны: %s\n", country->name);
            fprintf(fp, "Число жителей: %zu\n", country->number_of_inhabitants);
            fprintf(fp, "Столица: %s\n", country->capital);
            fprintf(fp, "Материк: %s\n", country->mainland);
            fprintf(fp, "Вакцинация/тест: %s\n", country->vaccination);
            print_main_tour_name(fp, country->main_tour_name);
            print_main_tour_type(fp, country);
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
