#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

double rand_double(size_t min, size_t max, size_t precision)
{
  srand(time(NULL));

  double value;

  // получить случайное число как целое число с порядком precision
  value = rand() % (int)pow(10, precision);

  // получить вещественное число
  value = min + (value / pow(10, precision)) * (max - min);

  return value;
}

/// @brief приостанавливает выполнение программы на некторое время в микросекундах
/// @param  время в микро секундах
void sleep_usecs(double usecs)
{
    // struct timespec t;
    // t.tv_sec
    usleep(usecs);
}

void rand_sleep(size_t min, size_t max, size_t precision)
{
    double a = rand_double(min, max, precision);

    sleep_usecs(a);
}
