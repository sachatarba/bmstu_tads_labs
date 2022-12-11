#include <stdio.h>

#include "../inc/queue_array_t.h"
#include "../inc/queue_list_t.h"
#include "../inc/sleep_time.h"
#include "../inc/request_t.h"
#include <unistd.h>

#include <time.h>

#include "../inc/processing_machine.h"
#include "../inc/mytime.h"

const char main_menu[] =
"\n\
1. Моделирование\n\
2. Работа с очередью, реализованной при помощи массива\n\
3. Работа с очередью, реализованной при помощи списка\n\
4. Замеры времени и памяти\n\
5. Выход из программы\n\n\
";

const char stack_menu[] = 
"\n\
1. Добавление элемента в очередь\n\
2. Удаление элемента из очереди\n\
3. Вывод очереди\n\
4. Выход в главное меню\n\n\
";

int main(void)
{
    // // queue_array_t *queue = create_array(100);
    // queue_list_t *queue = create_list(100);
    
    // for (size_t i = 0; i < 100; ++i)
    // {
    //     request_t *temp = create_req(i, 1, 2, 3);
    //     // push_array(queue, temp);
    //     push_list(queue, temp);
    // }

    // for (size_t i = 0; i < 100; i++)
    // {
    // //     void *p = NULL;
    //     request_t *temp = NULL;
    //     // pop_array(queue, (void **) &temp);
    //     pop_list(queue, (void **) &temp);
    //     printf("%lf\n", temp->min_in);
    //     free_req(&temp);
    // }
    
    // // // print(queue);

    // // destroy_array(&queue);
    // destroy_list(&queue);
    // // sleep_usecs(rand_double());
    // // rand_sleep(1 * 1000000, 10 * 1000000, 6);
    // // printf("\n");

    int command = 0;

    int rc = 0;

    while (rc == 0)
    {
        printf(main_menu);
        printf("Введите номер команды!: ");
        if (scanf("%d", &command) != 1)
        {
            printf("\nОшибка ввода!\n");
            rc = 1;
        }
        printf("\n");
        switch (command)
        {
            // printf(stack_menu);
            case 1:
            {
                request_t *r1, *r2;
                int type = 0;
                r1 = create_req(1, 5, 0, 4);
                r2 = create_req(0, 1 , 0, 1);
                printf("Выберете способ реализации очереди: с помощью массива или списка (0 или 1): ");
                if (scanf("%d", &type) != 1 && (type != 0 || type != 1))
                {
                    printf("\nОшибка ввода!\n");
                    rc = 1;
                }
                else
                {
                    process(type, r1, r2);
                }
                break;
            }
            case 2:
            {
                queue_array_t *arr = create_array(10000);
                while (rc == 0)
                {
                    printf(stack_menu);
                    printf("Введите номер команды!: ");
                    if (scanf("%d", &command) != 1)
                    {
                        printf("\nОшибка ввода!\n");
                        rc = 1;
                    }
                    printf("\n");
                    switch (command)
                    {
                        case 1:
                        {
                            int *a = malloc(sizeof(int));
                            printf("Введите число, которое хотите добавить в очередь!: ");
                            if (scanf("%d", a) != 1)
                            {
                                printf("\nОшибка ввода!\n");
                                rc = 1;
                            }
                            else
                            {
                                printf("\n");
                                if (!is_full_array(arr))
                                {
                                    push_array(arr, a);
                                }
                                else
                                {
                                    printf("Переполнение очереди!");
                                }
                            }
                            break;
                        }

                        case 2:
                        {
                            if (!is_empty_array(arr))
                            {
                                int *a;
                                printf("Элемент со значением %d удален из очереди!\n", (pop_array(arr, (void **) &a), *a));
                                free(a);
                            }
                            else
                            {
                                printf("Попытка удаления из пустой очереди!\n");
                            }
                            break;
                        }

                        case 3:
                        {
                            print_array(arr);
                            break;
                        }
                        case 4:
                        {
                            printf("\nВозврат в главное меню\n");
                            break;
                        }
                        default:
                        {
                            printf("Неверный номер команды!\n");
                            rc = 1;
                            break;
                        }
                    }

                    if (command == 4)
                    {
                        command = 0;
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                queue_list_t *list = create_list(10000);
                while (rc == 0)
                {
                    printf(stack_menu);
                    printf("Введите номер команды!: ");
                    if (scanf("%d", &command) != 1)
                    {
                        printf("\nОшибка ввода!\n");
                        rc = 1;
                    }
                    printf("\n");
                    switch (command)
                    {
                        case 1:
                        {
                            int *a = malloc(sizeof(int));
                            printf("Введите число, которое хотите добавить в очередь!: ");
                            if (scanf("%d", a) != 1)
                            {
                                printf("\nОшибка ввода!\n");
                                rc = 1;
                            }
                            else
                            {
                                printf("\n");
                                if (!is_full_list(list))
                                {
                                    push_list(list, a);
                                }
                                else
                                {
                                    printf("Переполнение очереди!");
                                }
                            }
                            break;
                        }

                        case 2:
                        {
                            if (!is_empty_list(list))
                            {
                                int *a = NULL;
                                printf("Элемент со значением %d удален из очереди!\n", (pop_list(list, (void **) &a), *a));
                                free(a);
                            }
                            else
                            {
                                printf("Попытка удаления из пустой очереди!\n");
                            }
                            break;
                        }

                        case 3:
                        {
                            print_list(list);
                            break;
                        }
                        case 4:
                        {
                            printf("\nВозврат в главное меню\n");
                            break;
                        }
                        default:
                        {
                            printf("Неверный номер команды!\n");
                            rc = 1;
                            break;
                        }
                    }

                    if (command == 4)
                    {
                        break;
                    }
                }
                break;
            }
            case 4:
            {
                queue_array_t *a = create_array(100);
                queue_list_t *ls = create_list(100);

                struct timespec b;
                struct timespec e;
                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;

                for (size_t i = 0; i < 100; ++i)
                {
                    int *n = malloc(sizeof(int));
                    *n =  i;
                    timespec_get(&b, TIME_UTC);
                    push_array(a, n);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                }

                t1 /= 100;
                // timespec_get(&b, TIME_UTC);

                for (size_t i = 0; i < 100; ++i)
                {
                    int *n = malloc(sizeof(int));
                    *n =  i;
                    timespec_get(&b, TIME_UTC);
                    push_list(ls, n);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                // timespec_get(&e, TIME_UTC);

                t2 /= 100;

                int *p = NULL;
                // timespec_get(&b, TIME_UTC);

                for (size_t i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    pop_array(a, (void **) &p);
                    timespec_get(&e, TIME_UTC);
                    free(p);
                    t3 += calc_elapsed_time(&b, &e);
                }

                // timespec_get(&e, TIME_UTC);

                t3 /= 100;

                for (size_t i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    pop_list(ls, (void **) &p);
                    timespec_get(&e, TIME_UTC);
                    free(p);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 100;

                printf("Среднее время работы функции push структуры очереди реализованной при помощи массива: %llu (нс), при помощи списка: %llu (нс)\n", t1, t2);
                printf("Среднее время работы функции pop структуры очереди реализованной при помощи массива: %llu (нс), при помощи списка: %llu (нс)\n", t3, t4);
                printf("-------------------------------------------------------------------------------------------------------------------------\n");
                printf("Память в байтах, которую занимают 100 элементов очереди, реализованной при помощи массива: %llu, при помощи списка: %lu\n", sizeof(queue_array_t) + 100LLU * sizeof(void *), sizeof(queue_list_t) + 100 * sizeof(node_t ));

                break;
            }
            case 5:
            {
                printf("Выход из программы!\n");
                break;
            }
            default:
            {
                printf("Неверный номер команды!\n");
                rc = 1;
                break;
            }

            if (command == 5)
            {
                command = 0;
                break;
            }
        }
        if (command == 5)
            break;
    }


    // printf("Память в байтах, которую занимают 100 элементов очереди, реализованной при помощи массива: %llu, при помощи списка: %lu\n", sizeof(queue_array_t) + 1000LLU * sizeof(void *), sizeof(queue_list_t) + 1000 * sizeof(node_t ));
    return 0;
}
