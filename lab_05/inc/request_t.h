#ifndef __REQUEST_T_H__
#define __REQUEST_T_H__

#include "../inc/mytime.h"

struct request
{
    double min_in;
    double max_in;
    double min_proc;
    double max_proc;

    float in_time;
    void *addr;
};

typedef struct request request_t; 

request_t *create_req(double min_in, double max_in, double min_proc, double max_proc);

void free_req(request_t **req);

#endif //  __REQUEST_T_H__
