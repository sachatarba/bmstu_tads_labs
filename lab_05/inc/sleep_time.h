#ifndef __SLEEP_TIME_H__
#define __SLEEP_TIME_H__

#include <stddef.h>


double rand_double(size_t min, size_t max, size_t precision);

void sleep_usecs(double usecs);

void rand_sleep(size_t min, size_t max, size_t precision);

#endif //  __SLEEP_TIME_H__
