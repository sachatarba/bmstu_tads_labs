#ifndef __COUNTRY_T_H__
#define __COUNTRY_T_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include "../inc/tourism_t.h"

#define BUFF 100 

struct country
{
    char name[BUFF];
    size_t number_of_inhabitants;
    char capital[BUFF];
    char mainland[BUFF];
    char vaccination[BUFF];
    tourism_name_t main_tour_name;
    tourism_t main_tour_type;
};

typedef struct country country_t;

error_t read_country(FILE *fp, country_t *country);

error_t print_country(FILE *fp, country_t *country);

error_t read_main_tour_type(FILE *fp, country_t *country);

#endif
