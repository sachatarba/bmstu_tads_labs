#include <stdlib.h>

#include "../inc/matr_t.h"
#include "../inc/sparse_matr_t.h"
#include "../inc/mytime.h"
#include "../inc/transform.h"

const char main_menu[] = 
"\
1. Ввод матрицы\n\
2. Замер времени\n\
3. Выход из программы\n\
";

const char input_menu[] =
"\
1. Классический поэлементный ввод\n\
2. Покоординатный ввод\n\
3. Ввод по проценту разреженности\n\
";


const char operations_menu[] =
"\
1. Обычный алгоритм умножения\n\
2. Разреженный алгоритм умножения\n\
3. Возврат в главное меню\n\
";

int main(void)
{
    int rc = OK;

    int command = 0;

    while (rc == OK)
    {
        printf("\n%s\n", main_menu);
        printf("Введите номер команды: ");
        if (scanf("%d", &command) != 1)
        {
            printf("\n");
            printf("Неверно введена команда!\n");
            rc = ERR_BAD_COMMAND;
            break;
        }
        printf("\n");
        switch (command)
        {
            matr_t matr;
            matr_t vector;
            sparse_matr_t *sp_matr;
            sparse_matr_t *sp_vector;

            case 1:
            {
                printf("\n%s\n", input_menu);
                printf("Введите номер команды: ");
                if (scanf("%d", &command) != 1)
                {
                    printf("\n");
                    printf("Неверно введена команда!\n");
                    rc = ERR_BAD_COMMAND;
                }
                printf("\n");
                switch (command)
                {
                    case 1:
                    {
                        printf("Ввод матрицы:\n");
                        rc = read_matr(stdin, &matr);
                        if (rc == OK)
                        {
                            printf("Ввод вектора-столбца:\n");
                            // rc = read_matr(stdin, &vector);
                            rc = read_vector(stdin, &vector);
                        }
                        break;
                    }
                    case 2:
                    {
                        printf("Ввод матрицы:\n");
                        rc = read_matr_by_coords(stdin, &matr);
                        
                        // rc = read_matr_by_coords(stdin, &matr);
                        if (rc == OK)
                        {
                            rc = read_vector_by_coords(stdin, &vector);
                            printf("Ввод вектора-столбца:\n");
                        } 
                        break;  
                    }
                    case 3:
                    {
                        int rows, cols;
                        int percent = 0;
                        printf("Введите число строк и столбцов: ");
                        if (scanf("%d %d", &rows, &cols) != 2)
                        {
                            rc = ERR_READING;
                            printf("\nОшибка чтения!\n");
                        }
                        printf("\n");
                        printf("Введите процент заполненности матрицы (число [0, 100]): ");
                        if (scanf("%d", &percent) != 1)
                        {
                            rc = ERR_BAD_PERCENT;
                            printf("\nОшибка чтения процента!\n");
                        }
                        printf("\n");
                        if (percent < 0 || percent > 100)
                        {
                            rc = ERR_BAD_PERCENT;
                            printf("\nНеверно указан процент!\n");
                        }
                        if (rc == OK)
                        {
                            rc = rand_sparse_matr_by_percent(&matr, rows, cols, percent);
                            
                            if (rc == OK)
                                rand_sparse_matr_by_percent(&vector, cols, 1, percent);
                        }
                        break;
                    }
                    default:
                        rc = ERR_BAD_COMMAND;
                        break;
                }

                while (rc == OK && command != 5)
                {
                    printf("\n%s\n", operations_menu);
                    printf("Введите номер команды: ");
                    if (scanf("%d", &command) != 1)
                    {
                        printf("\n");
                        printf("Неверно введена команда!\n");
                        rc = ERR_BAD_COMMAND;
                    }
                    printf("\n");
                    switch (command)
                    {
                        case 1:
                        {
                            matr_t *res = malloc(sizeof(matr_t));
                            rc = mul_matr(&matr, &vector, res);
                            printf("\n--------------\n");
                            if (res->rows <= 10)
                                print_matr(stdout, res);
                            else
                            {
                                sparse_matr_t *sp_res = NULL;
                                transform_to_sparse_matr(res, &sp_res);
                                print_sparse_matr(stdout, sp_res);
                            }
                            printf("--------------\n");
                            break;
                        }
                        case 2:
                        {
                            sparse_matr_t *res1 = NULL;
                            transform_to_sparse_matr(&matr, &sp_matr);
                            transform_to_sparse_matr(&vector, &sp_vector);
                            rc = mul_sp_matr_and_sp_vector(sp_matr, sp_vector, &res1);
                            if (rc == OK)
                            {
                            printf("\n--------------\n");
                            print_sparse_matr(stdout, res1);
                            printf("--------------\n");
                            }
                            else
                            {
                                printf("\nОшибка умножения!\n");
                            }
                            break;
                        }
                        case 3:
                        {
                            printf("\nВозврат в главное меню\n");
                            break;
                        }
                        case 4:
                        {
                            printf("\n--------------\n");
                            print_matr(stdout, &matr);
                            printf("--------------\n");
                            break;
                        }
                        case 5:
                        {
                            printf("\n--------------\n");
                            print_matr(stdout, &vector);
                            printf("--------------\n");
                            break;
                        }
                        default:
                        {
                            rc = ERR_BAD_COMMAND;
                            break;
                        }
                    }
                }
                break;
            }

            case 2:
            {
                int rows = 0, cols = 0;
                printf("Введите размеры матрицы для замера времени: ");
                if (scanf("%d %d", &rows, &cols) != 2)
                {
                    rc = ERR_READING;
                    printf("\nОшибка чтения!\n");
                }
                printf("\n");
                if (rc == OK)
                {
                    if (rows > 0 && cols > 0)
                    {
                        matr_t m1, m2;
                        matr_t *res = malloc(sizeof(res));
                        sparse_matr_t *m3, *m4, *m5 = NULL;
                        // matr_t *m = NULL;
                        // matr_t *vector = NULL;
                        // sparse_matr_t *sp_m = NULL;
                        // sparse_matr_t *sp_vector = NULL;
                        // sparse_matr_t *sp_res = NULL;
                        // struct timespec beg;
                        // struct timespec end;
                        // unsigned long long t1, t2;
                        for (size_t percent = 0; percent <= 100; ++percent)
                        {
                            struct timespec beg1;
                            struct timespec beg2;
                            struct timespec end1;
                            struct timespec end2;
                            rand_sparse_matr_by_percent(&m1, rows, cols, percent);
                            rand_sparse_matr_by_percent(&m2, cols, 1, percent);
                            transform_to_sparse_matr(&m1, &m3);
                            transform_to_sparse_matr(&m2, &m4);
                            timespec_get(&beg1, TIME_UTC);
                            mul_sp_matr_and_sp_vector(m3, m4, &m5);
                            timespec_get(&end1, TIME_UTC);
                            timespec_get(&beg2, TIME_UTC);
                            mul_matr(&m1, &m2, res);
                            timespec_get(&end2, TIME_UTC);
                            unsigned long long t1 = calc_elapsed_time(&beg1, &end1);
                            unsigned long long t2 = calc_elapsed_time(&beg2, &end2);
                            // printf("Время разреженного умножения: %lld Время обычного: %lld\n", t1, t2);

                            // rand_sparse_matr_by_percent(m, rows, cols, percent);
                            // rand_sparse_matr_by_percent(vector, cols, 1, percent);
                            // transform_to_sparse_matr(m, &sp_m);
                            // transform_to_sparse_matr(vector, &sp_vector);
                            // matr_t *res = malloc(sizeof(matr_t));
                            // timespec_get(&beg, TIME_UTC);
                            // mul_matr(m, vector, res); 
                            // timespec_get(&end, TIME_UTC);
                            // free_matr(m);
                            // free_matr(vector);
                            // free_matr(res);
                            // // t1 = calc_elapsed_time(&beg, &end);
                            // timespec_get(&beg, TIME_UTC);
                            // mul_sp_matr_and_sp_vector(sp_m, sp_vector, &sp_res); 
                            // timespec_get(&end, TIME_UTC);
                            // print_sparse_matr_table(sp_res);
                            // free_sparse_matr(sp_m);
                            // free_sparse_matr(sp_res);
                            // free_sparse_matr(sp_vector);
                            // t2 = calc_elapsed_time(&beg, &end);
                            printf("-------------------------------------------------------------------------------------------------------------\n");
                            printf("Процент заполненности: %zu, Время умножения обычным алгоритмом: %lld, Время умножения разр. алгоритмом: %lld\n", percent, t2, t1);
                            printf("-------------------------------------------------------------------------------------------------------------\n");
                            // free(res);
                        }
                        free_matr(res); 
                    }
                    else
                    {
                        rc = ERR_BAD_SIZE;
                        printf("\nНеверные размеры матрицы!\n");
                    }
                }
                break;
            }

            case 3:
            {
                printf("\nЗавершение программы!\n");
                break;
            }
            default:
            {
                rc = ERR_BAD_COMMAND;
                printf("\nНеверный номер команды\n");
                break;
            }
        }
    }  

    return rc;  
}