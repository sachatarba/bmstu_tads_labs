#include <stdio.h>
#include "../inc/tourism_t.h"
#include "../inc/country_t.h"
#include "../inc/table_countries.h"


#include <ctype.h>

int main(void)
{
    countries_table_t table;    
    create_table(&table, 3);
    append_country(stdin, &table);
    append_country(stdin, &table);
    append_country(stdin, &table);

    print_table(stdout, &table);


    // tourism_t tour;
    // tourism_name_t name;
    // country_t country;
    // read_country(stdin, &country);
    // print_country(stdout, &country);
    // fprintf(, "bebra");
    // read_enum(stdin, &tour, SPORTS);
    // printf("%d\n", tour.sports.main_sport);
    // read_excursions(stdin, &tour);
    // print_excursions(stdout, &tour);
    // read_main_tour_name(stdin, &name);
    // print_main_tour_name(stdout, name);
    // char c = 'a';
    // scanf("%c", &c);
    // printf("%c", tolower(c));
}
