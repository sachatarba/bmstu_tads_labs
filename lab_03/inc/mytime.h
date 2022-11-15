#ifndef __MYTIME_H__
#define __MYTIME_H__

#include <time.h>
#include <sys/time.h>

long long get_time();

unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end);

#endif //  __MYTIME_H__
