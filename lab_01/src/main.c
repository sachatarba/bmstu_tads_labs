#include <stdio.h>
#include <string.h>

#include "../headers/utils.h"
#include "../headers/long_float.h"

int main(void)
{
    int rc = 0;
    long_float_t lf;
    memset(&lf, 0, sizeof(lf));
    rc = read_long_float(&lf);
    // char buff[100];
    // scanf("%s", buff);
    // fgets(buff, 100, stdin);
    // // int array[100];
    // // size_t len = 0;
    // // // printf("bebra1");
    // char *new_buff = strip(buff);
    // printf("%s", new_buff);
    // // copy_digits_to_array(new_buff, array, &len);
    // // print_array(lf.mantissa, lf.digits);
    print_long_float(&lf);
    // char a[10] = "bebra";
    // char **end = NULL;
    // copy_mantissa(&lf, buff, (const char**) end);
    // print_array(lf.mantissa, lf.digits, '\0');

    return rc;
}
