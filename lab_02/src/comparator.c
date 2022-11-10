#include <string.h>

#include "../inc/comparator.h"
#include "../inc/countries_with_keys_t.h"

int compare_countries_by_name(const void *country_1, const void *country_2)
{
    return strcmp(((country_t *) country_1)->name, ((country_t *) country_2)->name);
}

int compare_keys_by_name(const void* key_1, const void* key_2)
{
    return strcmp(((struct keys *) key_1)->name, ((struct keys *) key_2)->name);
}
