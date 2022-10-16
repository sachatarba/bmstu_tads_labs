#ifndef __TOURISM_T_H__
#define __TOURISM_T_H__

#include <stddef.h>

#include "../inc/error_t.h"
#include "../inc/abstract_enum_t.h"

enum tourism_name
{
    EXCURSIONS,
    BEACHFRONT,
    SPORTS     
};

typedef enum tourism_name tourism_name_t;

union tourism
{
    struct 
    {
        enum
        {
           NATURE,
           HISTORY,
           ART,
        } type_of_objets;

        size_t number_of_objects;
    } excursions;

    struct
    {
        enum
        {
           WINTER,
           SPRING,
           SUMMER,
           AUTUMN
        } main_season;

        size_t air_temperature;
        size_t water_temperature;
    } beachfront;

    struct 
    {
        enum
        {
           SKIING,
           SURFING,
           CLIMBING
        } main_sport;

        size_t min_holiday_cost;
    } sports;  
};

typedef union tourism tourism_t;

error_t find_name(tourism_name_t name, char *name_to_find, abstract_enum_t *ind);

error_t read_enum(FILE *fp, tourism_t *tour, tourism_name_t name);

error_t read_main_tour_name(FILE *fp, tourism_name_t *name);

void print_main_tour_name(FILE *fp, tourism_name_t name);

error_t read_excursions(FILE *fp, tourism_t *tour);

error_t print_excursions(FILE *fp, tourism_t *tour);

error_t read_beachfront(FILE *fp, tourism_t *tour);

error_t print_beachfront(FILE *fp, tourism_t *tour);

error_t read_sports(FILE *fp, tourism_t *tour);

error_t print_sports(FILE *fp, tourism_t *tour);

#endif
