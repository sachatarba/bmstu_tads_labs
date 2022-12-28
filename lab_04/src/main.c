#include <stdio.h>
#include <assert.h>

#include "../inc/stack_array_t.h"
#include "../inc/stack_list_t.h"
#include "../inc/mytime.h"

const char main_menu[] = 
"\n\
1. Работа с реализацией стека при помощи списка\n\
2. Работа с реализацией стека при помощи массива\n\
3. Замер времени и памяти\n\
4. Выход из программы\n\n\
";

const char arr_operations_menu[] = 
"\n\
1. Добавление элемента в стек\n\
2. Удаление элемента из стека\n\
3. Просмотр состояния стека\n\
4. Завершение работы со стеком и возврат в главное меню\n\n\
";

const char list_operations_menu[] = 
"\n\
1. Добавление элемента в стек\n\
2. Удаление элемента из стека\n\
3. Просмотр состояния стека\n\
4. Вывод освобожденных адресов элементов стека\n\
5. Завершение работы со стеком и возврат в главное меню\n\n\
";

// const char *freed_addrs_menu = 
// "
// 4. Вывод освобожденных адресов элементов стека\n
// ";

// const

int main(void)
{
    stack_array_t arr;
    stack_list_t list;

    int command = 0;
    int rc = 0;

    while (command != 4 && rc == 0)
    {
        printf(main_menu);

        printf("Введите номер команды: ");
        
        if (scanf("%d", &command) == 1)
        {
            printf("\n");
            switch (command)
            {
                case 1:
                {
                    list = create_stack_list();

                    while (rc == 0 && command != 5)
                    {
                        printf(list_operations_menu);
                        printf("Введите номер команды: ");

                        if (scanf("%d", &command) == 1)
                        {
                            printf("\n");

                            switch (command)
                            {
                                case 1:
                                {
                                    if (!is_full_stack_list(list))
                                    {
                                        push_stack_list(list);
                                        printf("Элемент добавлен в стек!\n");
                                    }
                                    else
                                    {
                                        rc = 1;
                                        printf("Переполнение стека!\n");
                                    }
                                    break;
                                }
                                case 2:
                                {
                                    void *p = NULL;
                                    if (pop_stack_list(list, &p) == 0)
                                        printf("Элемент, содержащий значение %p удален!\n", p);
                                    else
                                        printf("Попытка удаления из пустого стека!\n");
                                    break;
                                }
                                case 3:
                                {
                                    look_up_stack_list(list);
                                    break;
                                }
                                case 4:
                                {
                                    look_up_freed_addresses();
                                    break;
                                }
                                case 5:
                                {
                                    printf("Стек удален!\n");
                                    break;
                                }
                                default:
                                {
                                    rc = 1;
                                    printf("Неверный ввод команды!\n");
                                    break;
                                }
                            }
                        }
                        else
                        {
                            rc = 1;
                            printf("Неверный ввод команды!\n");
                        }   

                    }

                    destroy_stack_list(list);
                    break;
                }
                case 2:
                {
                    arr = create_stack_arr();

                    while (rc == 0 && command != 4)
                    {
                        printf(arr_operations_menu);
                        printf("Введите номер команды: ");

                        if (scanf("%d", &command) == 1)
                        {
                            printf("\n");

                            switch (command)
                            {
                                case 1:
                                {
                                    if (!is_full_stack_arr(arr))
                                    {
                                        void *p = NULL;
                                        printf("Введите адрес в формате шестнадцатеричного числа: ");

                                        if (scanf("%p", &p) == 1)
                                        {
                                            printf("\n");
                                            push_stack_arr(arr, p);
                                            printf("Элемент добавлен в стек!\n");
                                        }
                                        else
                                        {
                                            rc = 1;
                                            printf("Неверный ввод!\n");
                                        }
                                    }
                                    else
                                    {
                                        rc = 1;
                                        printf("Переполнение стека!\n");
                                    }
                                    break;
                                }
                                case 2:
                                {
                                    void *p = NULL;
                                    if (pop_stack_arr(arr, &p) == 0)
                                        printf("Элемент, содержащий значение %p удален!\n", p);
                                    else
                                        printf("Попытка удаления из пустого стека!\n");
                                    break;
                                }
                                case 3:
                                {
                                    look_up_stack_arr(arr);
                                    break;
                                }
                                case 4:
                                {
                                    printf("Стек удален!\n");
                                    // command = 0;
                                    break;
                                }
                                default:
                                {
                                    rc = 1;
                                    printf("Неверный ввод команды!\n");
                                    break;
                                }
                            }
                        }
                        else
                        {
                            rc = 1;
                            printf("Неверный ввод команды!\n");
                        }   

                    }

                    destroy_stack_arr(arr);
                    command = 0;
                    break;
                }
                case 3:
                {
                    stack_array_t a = create_stack_arr();
                    stack_list_t ls = create_stack_list();
                    
                    struct timespec b;
                    struct timespec e;
                    unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;

                    
                    for (size_t i = 0; i < 100; ++i)
                    {
                        timespec_get(&b, TIME_UTC);
                        push_stack_arr(a, NULL);
                        timespec_get(&e, TIME_UTC);
                        t1 += calc_elapsed_time(&b, &e);
                    }

                    t1 /= 100;
                    // timespec_get(&b, TIME_UTC);
                    
                    for (size_t i = 0; i < 100; ++i)
                    {
                        timespec_get(&b, TIME_UTC);
                        push_stack_list(ls);
                        timespec_get(&e, TIME_UTC);
                        t2 += calc_elapsed_time(&b, &e);
                    }

                    // timespec_get(&e, TIME_UTC);

                    t2 /= 100;

                    void *p = NULL;
                    // timespec_get(&b, TIME_UTC);
                    
                    for (size_t i = 0; i < 100; ++i)
                    {
                        timespec_get(&b, TIME_UTC);
                        pop_stack_arr(a, &p);
                        timespec_get(&e, TIME_UTC);
                        t3 += calc_elapsed_time(&b, &e);
                    }

                    // timespec_get(&e, TIME_UTC);

                    t3 /= 100;

                    for (size_t i = 0; i < 100; ++i)
                    {
                        timespec_get(&b, TIME_UTC);
                        pop_stack_list(ls, &p);
                        timespec_get(&e, TIME_UTC);
                        t4 += calc_elapsed_time(&b, &e);
                    }

                    t4 /= 100;

                    printf("Среднее время работы функции push структуры стека реализованного при помощи массива: %llu (нс), при помощи списка: %llu (нс)\n", t1, t2);
                    printf("Среднее время работы функции pop структуры стека реализованного при помощи массива: %llu (нс), при помощи списка: %llu (нс)\n", t3, t4);
                    printf("-------------------------------------------------------------------------------------------------------------------------\n");
                    printf("Память в байтах, которую занимают 100 элементов стека, реализованного при помощи массива: %llu, при помощи списка: %llu\n", sizeof(stack_array_t) + 100LLU * sizeof(void *), sizeof(stack_list_t) + 100 * get_node_size() );
            
                    break;
                }
                case 4:
                {
                    break;
                }
                default:
                {
                    printf("Неверный номер команды!\n");
                    break;
                }
            }
        }
        else
        {
            printf("Неверный ввод!\n");
            rc = 1;
        }
    } 

    // void *p = NULL;
    // assert(p);

    // stack_array_t arr = create_stack_arr();
    // stack_list_t lst = create_stack_list();
    // scanf("%p", &p);

    // for (size_t i = 0; i < 3; ++i)
    // {
    //     // scanf("%p", &p);
    //     // push_stack_arr(arr, p);
    //     push_stack_list(lst);
    // }
    // push_stack_arr(arr, p);
    // push_stack_list(lst, p);
    // pop_stack_arr(arr, &p);
    // printf("%p\n", p);
    // pop_stack_list(lst, &p);
    // look_up_stack_list(lst);
    // destroy_stack_list(lst);
    // look_up_freed_addresses();
    // look_up_stack_arr(arr);
    // destroy_stack_arr(arr);
    // printf("%p\n", p);

    printf("Завершение программы!\n");
    // printf("%llu %llu", sizeof(stack_array_t) + 1000LLU * sizeof(void *), sizeof(stack_list_t) + 1000 * get_node_size());
    return rc;   
}