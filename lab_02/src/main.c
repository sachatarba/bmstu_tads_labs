#include <stdio.h>
#include "../inc/tourism_t.h"
#include "../inc/country_t.h"
#include "../inc/countries_table_t.h"
#include "../inc/sorts.h"
#include "../inc/comparator.h"
#include "../inc/countries_with_keys_t.h"
#include "../inc/mytime.h"
#include "../inc/string_utils.h"



const char info[BUFF * 10] =
{
"\n\
0. Выход из программы\n\
1. Чтение из файла таблицы\n\
2. Добавление в таблицу\n\
3. Удаление по имени\n\
4. Сортировка и вывод ключей\n\
5. Сортировка и вывод таблицы\n\
6. Вывод таблицы по отсортированным ключам\n\
7. Вывод информации о сортировках\n\
8. Вывод таблицы\n\
9. Вывод ключей\n\
10. Поиск по материку и виду спорта\n\
"
};

typedef void (*sort_t)(void *, size_t, size_t, int (*cmp)(const void*, const void *));

int main(void)
{
    error_t rc = OK;

    size_t command = 1;
    int sort_type = 0;

    sort_t sorts[] = { qsort, bubble_sort };

    countries_table_t table;
    create_table(&table, 0);

    countries_with_keys_t keys;

    FILE *fp;

    char buff[BUFF] = "\0";
    char name[BUFF] = "\0";

    while (!rc && command != 0)
    {
        printf("%s\n", info);
        printf("Введите номер команды: ");

        rc = read_size_number(stdin, &command);
        printf("\n");
        switch (command)
        {
        case 0:
            printf("Завершение программы\n");
            break;

        case 1:

            fp = fopen("/home/sachatarba/tasd_labs/lab_02/src/in.txt", "r");

            if (fp != NULL)
            {
                while (!feof(fp))
                {
                    rc = append_country(fp, &table);
                }
            }
            else
            {
                rc = ERR_NO_FILE;
            }
            break;

        case 2:

            rc = append_country(stdin, &table);
            break;

        case 3:

            printf("Введите название страны: ");
            rc = read_string(stdin, name, BUFF);
            if (rc == OK)
                rc = delete_country_by_name(&table, name);

            break;

        case 4:

            sort_type = 0;
            printf("Сортировать при помощи qsort/bubble_sort (0/1): ");
            fgets(buff, BUFF, stdin);
            sort_type = atoi(buff);
            printf("\n");

            if (sort_type == 0 || sort_type == 1)
            {
                create_table_keys(&table, &keys);
                sorts[sort_type](keys.keys, keys.countries->size, sizeof(struct keys), compare_keys_by_name);
                print_keys(stdout, &keys);
            }
            else
            {
                printf("Введено не 1 или 0\n");
            }

            break;

        case 5:

            sort_type = 0;
            printf("Сортировать при помощи qsort/bubble_sort (0/1): ");
            fgets(buff, BUFF, stdin);
            sort_type = atoi(buff);

            if (sort_type == 0 || sort_type == 1)
            {
                sorts[sort_type](table.country, table.size, sizeof(country_t), compare_countries_by_name);
                print_table(stdout, &table);
            }
            else
            {
                printf("Введено не 1 или 0\n");
            }

            break;
        
        case 6:
                print_countries_in_order_of_keys(stdout, &keys);
            break;
        
        case 7:
        {
            countries_table_t table_to_sort[4];
            countries_with_keys_t keys_to_sort[4];

            const char filename[] = "/home/sachatarba/tasd_labs/lab_02/src/in.txt";


            for (size_t i = 0; i < 2; ++i)
            {   
                create_table(table_to_sort + i, 0);
                fp = fopen(filename, "r");

                while (!feof(fp))
                {
                    append_country(fp, table_to_sort + i);
                }

                
                struct timespec beg;
                struct timespec end;
                timespec_get(&beg, TIME_UTC);
                sorts[i](table_to_sort[i].country, table_to_sort[i].size, sizeof(country_t), compare_countries_by_name);
                timespec_get(&end, TIME_UTC);
                printf("Время замера сортировки (%s) таблицы (нс): %llu\n", i == 0 ? "qsort" : "bubble_sort", calc_elapsed_time(&beg, &end)); 
                free_table(table_to_sort + i);
                fclose(fp);
            }

            for (size_t i = 2; i < 4; ++i)
            {   
                create_table(table_to_sort + i, 0);
                fp = fopen(filename, "r");

                while (!feof(fp))
                {
                    append_country(fp, table_to_sort + i);
                }

                create_table_keys(table_to_sort + i, keys_to_sort + i);
                struct timespec beg;
                struct timespec end;
                timespec_get(&beg, TIME_UTC);
                sorts[i % 2](keys_to_sort[i].keys, keys_to_sort[i].countries->size, sizeof(struct keys), compare_keys_by_name);
                timespec_get(&end, TIME_UTC);
                printf("Время замера сортировки (%s) таблицы ключей (нс): %llu\n", i == 2 ? "qsort" : "bubble_sort", calc_elapsed_time(&beg, &end)); 
                free_table(table_to_sort + i);
                free_keys(keys_to_sort + i);
                fclose(fp);
            }

            break;
        }

        case 8:
            print_table(stdout, &table);
            break;


        case 9:
            create_table_keys(&table, &keys);
            print_keys(stdout, &keys);
            break;

        case 10:
            rc = find_by_mainland_and_sport(&table);
            break;
        
        default:
            rc = ERR_BAD_COMMAND;
            break;
        }

    }
}
