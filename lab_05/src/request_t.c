#include "../inc/request_t.h"

#include <stdlib.h>

request_t *create_req(double min_in, double max_in, double min_proc, double max_proc)
{
    request_t *temp = malloc(sizeof(request_t));
    temp->min_in = min_in;
    temp->max_in = max_in;
    temp->min_proc = min_proc;
    temp->max_proc = max_proc;
    temp->addr = temp;
    
    return temp;
}

void free_req(request_t **req)
{
    free(*req);
    *req = NULL;
}
