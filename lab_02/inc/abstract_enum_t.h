#ifndef __ABSTRACT_ENUM_T_H__
#define __ABSTRACT_ENUM_T_H__

#include <stdio.h>

#include "../inc/error_t.h"

enum abstract_enum
{
    ABSTRACT_ELM
};

typedef enum abstract_enum abstract_enum_t;

// struct abstruct_names
// {
//     char **names;
//     abstract_enum_t names_values;
// };

// typedef struct abstruct_names abstruct_names_t

// error_t read_abstract_enum(FILE *fp, abstract_enum_t *enm, char **abstract_names);

#endif
