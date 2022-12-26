#include "../inc/tree_t.h"
#include "../inc/avl_tree.h"
#include "../inc/mytime.h"
#include "../inc/tree_node.h"
#include "../inc/tree.h"
#include "../inc/closed_hash.h"
#include "../inc/open_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const char menu[] = 
"\n\
1. Создание дерева выражений по умолчанию\n\
2. Создание дерева выражений по умолчанию с вычисленными узлами\n\
3. Создание двоичного дерева поиска по умолчанию\n\
4. Создание сбалансированного дерева по умолчанию\n\
5. Создание закрытой хеш таблицы по умолчанию\n\
6. Создание открытой хеш таблицы по умолчанию\n\
7. Добавление узла в двоичное дерево поиска\n\
8. Добавление узла в сбалансированное дерево поиска\n\
9. Добавление элемента в закрытую хеш таблицу\n\
10. Добавление элемента в открытую хеш таблицу\n\
11. Просмотр закрытой хеш таблицы\n\
12. Просмотр открытой хеш таблицы\n\
13. Поиск элемента в двоичном дереве поиска\n\
14. Поиск элемента в сбалансированном дереве\n\
15. Поиск элемента в закрытой хеш таблице\n\
16. Поиск элемента в открытой хеш таблице\n\
17. Установка пользовательского значения числа сравнений\n\
18. Замер времени\n\n\
";

int main(void)
{
    Node *root = create_default_expr_tree();
    // double a = evaluate(root);
    
    Node *root1 = create_default_expr_tree();
    evaluate_to_tree(root1);
    closed_hash_table_t *cl_ht = create_cl_hash_table(5);
    open_hash_table_t *op_ht = create_op_hash_table(5);
    int *temp = malloc(sizeof(int));
    *temp = 0;
    struct tree_node_t *node = node_create((void *)temp);
    avl_node_t *avl = NULL;

    while (1)
    {
        printf(menu);
        int command = 0;
        // printf(menu);
        printf("Введите номер команды: ");
        if (scanf("%d", &command) != 1)
        {
            printf("\nОшибка ввода номера команды!\n");
            return 1;
        }
        printf("\n");
        switch (command)
        {
            case 1:
            {
                FILE *f = fopen("expr.gv", "w");

                assert(f);

                // btree_export_to_dot(f, "Tree_of_expression", root);
                make_gv(f, root);
                fclose(f);
                printf("Файл создан!\n");
                system("dot -Tpng expr.gv > expr.png");
                break;
            }
            case 2:
            {
                FILE *f = fopen("expr_calced.gv", "w");

                assert(f);

                // btree_export_to_dot(f, "Tree_of_expression", root);
                evaluate_to_tree(root1);
                tree_export_to_dot(f, "calced", root1);
                fclose(f);
                printf("Файл создан!\n");
                system("dot -Tpng expr_calced.gv > expr_calced.png");
                break;
            }
            case 3:
            {
                int array[100] = { 0 };
                int size = 0;
                inorder_get(root1, array, &size);

                if (size > 0)
                {
                    // int *temp = malloc(sizeof(int));
                    // if (temp)
                    if (*( (int *)node->name) == 0)
                    {
                        *temp = array[0];
                    // struct tree_node_t *node = node_create((void *)temp);
                        node->name = (void*) temp;
                    }
                    for (int i = 1; i < 100 && array[i]; ++i)
                    {
                        temp = malloc(sizeof(int));
                        *temp = array[i];
                        struct tree_node_t *n = node_create((void *)temp);
                        btree_insert(node, n);
                    }
                    // temp = malloc(sizeof(int));
                    // *temp = 20000000;
                    // struct tree_node_t *n = node_create((void *)temp);
                    // btree_insert(node, n);
                    FILE *f = fopen("btree.gv", "w");

                    assert(f);

                    // btree_export_to_dot(f, "Tree_of_expression", root);
                    // evaluate_to_tree(root1);
                    btree_export_to_dot(f, "btree", node);
                    fclose(f);
                    printf("Файл создан!\n");
                    system("dot -Tpng btree.gv > btree.png");
            
                }
                else
                {
                    printf("Дерево выражений пустое!\n");
                }
                break;    
            }
            case 4:
            {               
                int array[100] = { 0 };
                int size = 0;
                inorder_get(root1, array, &size);

                if (size > 0)
                {
                    // int *temp = malloc(sizeof(int));
                    // *temp = array[1];
                    // struct tree_node_t *node = node_create((void *)temp);
                    // avl_node_t *avl = create_avl_node(array[0]);
                    for (int i = 0; i < 100 && array[i]; ++i)
                    {
                        //  = malloc(sizeof(int));
                        // *temp = array[i];
                        // avl_node_t *n = create_avl_node(array[i]);
                        avl = insert(avl, array[i]);
                    }

                    FILE *f = fopen("avltree.gv", "w");

                    assert(f);

                    // btree_export_to_dot(f, "Tree_of_expression", root);
                    // evaluate_to_tree(root1);
                    // btree_export_to_dot(f, "avltree", node);
                    avl_tree_export_to_dot(f, "avl", avl);
                    fclose(f);
                    printf("Файл создан!\n");
                    system("dot -Tpng avltree.gv > avltree.png");
            
                }
                else
                {
                    printf("Дерево выражений пустое!\n");
                }
                break;    
            }
            case 5:
            {
                // int array[100] = { 0 };
                // int size = 0;
                // inorder_get(root1, array, &size);
                // closed_hash_table_t *ht = create_cl_hash_table(5);

                // cl_insert(&ht, 1);
                // cl_insert(&ht, 11);
                // cl_insert(&ht, 21);
                // cl_insert(&ht, 31);
                // cl_insert(&ht, 2);
                // cl_insert(&ht, 3);
                // cl_insert(&ht, 32);
                // cl_insert(&ht, 29);
                // cl_insert(&ht, 30);
                // cl_insert(&ht, 40);
                // cl_insert(&ht, 46);
                // cl_insert(&ht, 61);
                // look_up_cl_hash_table2(ht);
                // cl_find(ht, 1);
                // cl_find(ht, 11);
                // cl_find(ht, 21);
                // cl_find(ht, 31);
                // cl_find(ht, 2);
                // cl_find(ht, 3);
                // cl_find(ht, 32);
                // cl_find(ht, 29);
                // cl_find(ht, 30);
                // cl_find(ht, 0);
                int array[100] = { 0 };
                int size = 0;
                inorder_get(root1, array, &size);

                for (int i = 0; i < 100 && array[i]; ++i)
                {
                        //  = malloc(sizeof(int));
                        // *temp = array[i];
                        // avl_node_t *n = create_avl_node(array[i]);
                    cl_insert(&cl_ht, array[i]);
                }

                look_up_cl_hash_table2(cl_ht);
                break;
            }
            case 6:
            {

                // op_insert(&ht, 1);
                // op_insert(&ht, 11);
                // op_insert(&ht, 21);
                // op_insert(&ht, 41);
                // op_insert(&ht, 31);
                // op_insert(&ht, 2);
                // op_insert(&ht, 29);
                // op_insert(&ht, 30);
                // op_insert(&ht, 0);
                // look_up_op_hash_table1(ht);
                // op_find(ht, 1);
                // op_find(ht, 11);
                // op_find(ht, 21);
                // op_find(ht, 31);
                // op_find(ht, 2);
                // op_find(ht, 29);
                // op_find(ht, 30);
                // op_find(ht, 0);
                // ht = restruct_op_ht(ht);
                // printf("av: %lf", ht->average);
                // look_up_op_hash_table1(ht);
                
                int array[100] = { 0 };
                int size = 0;
                inorder_get(root1, array, &size);

                for (int i = 0; i < 100 && array[i]; ++i)
                {
                        //  = malloc(sizeof(int));
                        // *temp = array[i];
                        // avl_node_t *n = create_avl_node(array[i]);
                    op_insert(&op_ht, array[i]);
                }

                look_up_op_hash_table1(op_ht);
                break;
            }
            case 7:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля: ");
                // printf("%p %p", (void*)node->left, (void*)node->right);
                if (scanf("%d", &a) == 1 && a != 0)
                {
                    if (*( (int *)node->name) == 0)
                    {
                        *temp = a;
                        node->name = (void*) temp; 
                    }
                    else
                    {
                        temp = malloc(sizeof(int));
                        *temp = a;
                        struct tree_node_t *n = node_create((void *) temp);
                        btree_insert(node, n);
                    }
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                FILE *f = fopen("btree.gv", "w");

                assert(f);

                    // btree_export_to_dot(f, "Tree_of_expression", root);
                    // evaluate_to_tree(root1);
                btree_export_to_dot(f, "btree", node);
                fclose(f);
                // printf("Файл создан!\n");
                system("dot -Tpng btree.gv > btree.png");
                break;
            }
            case 8:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    avl = insert(avl, a);
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");

                FILE *f = fopen("avltree.gv", "w");

                assert(f);

                    // btree_export_to_dot(f, "Tree_of_expression", root);
                    // evaluate_to_tree(root1);
                    // btree_export_to_dot(f, "avltree", node);
                avl_tree_export_to_dot(f, "avl", avl);
                fclose(f);
                // printf("Файл создан!\n");
                system("dot -Tpng avltree.gv > avltree.png");
                break;
            }
            case 9:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    cl_insert(&cl_ht, a);
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 10:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    op_insert(&op_ht, a);
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 11:
            {
                look_up_cl_hash_table2(cl_ht);
                break;
            }
            case 12:
            {
                look_up_op_hash_table1(op_ht);
                break;
            }
            case 13:
            {
                extern int btries;
                int a = 0;
                printf("Введите целое число, отличное от нуля, для поиска: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    // op_insert(&op_ht, a);
                    struct timespec b, e;
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *btree = btree_lookup_2(node, (void *) &a);
                    timespec_get(&e, TIME_UTC);
                    printf("Время поиска: %llu\n", calc_elapsed_time(&b, &e));
                    if (btree)
                    {
                        printf("Элемент со значением %d найден, число сравнений = %d\n", a, btries);
                    }
                    else
                    {
                        printf("Элемент не найден, число сравнений = %d\n", btries);
                    }
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 14:
            {
                extern int avl_tries;
                int a = 0;
                printf("Введите целое число, отличное от нуля, для поиска: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    // op_insert(&op_ht, a);
                    struct timespec b, e;
                    timespec_get(&b, TIME_UTC);
                    avl_node_t *avl_temp = avl_tree_lookup_2(avl, a);
                    timespec_get(&e, TIME_UTC);
                    printf("Время поиска: %llu\n", calc_elapsed_time(&b, &e));
                    if (avl_temp)
                    {
                        printf("Элемент со значением %d найден, число сравнений = %d\n", a, avl_tries);
                    }
                    else
                    {
                        printf("Элемент не найден, число сравнений = %d\n", avl_tries);
                    }
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 15:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля, для поиска: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    // op_insert(&op_ht, a);
                    // struct timespec e, b;
                    size_t counter = 1;
                    // timespec_get(&b, TIME_UTC);
                    if (cl_find(cl_ht, a, &counter) == 1)
                    {
                        printf("Элемент с значением %d найден в таблице, число сравнений = %zu\n", a, counter);
                    }
                    else
                    {
                        printf("Элемент с значением %d НЕ найден в таблице, число сравнений = %zu\n", a, counter);
                    }
                    // timespec_get(&e, TIME_UTC);
                    // printf("Время поиска: %llu\n", calc_elapsed_time(&b, &e));
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 16:
            {
                int a = 0;
                printf("Введите целое число, отличное от нуля, для поиска: ");

                if (scanf("%d", &a) == 1 && a != 0)
                {
                    // avl = insert(avl, a);
                    // op_insert(&op_ht, a);
                    size_t counter = 1;
                    if (op_find(op_ht, a, &counter) == 1)
                    {
                        printf("Элемент с значением %d найден в таблице, число сравнений = %zu\n", a, counter);
                    }
                    else
                    {
                        printf("Элемент с значением %d НЕ найден в таблице, число сравнений = %zu\n", a, counter);
                    }
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break;
            }
            case 17:
            {
                int a = 0;
                printf("Введите число сравнений (больше 1): ");

                if (scanf("%d", &a) == 1 && a > 1)
                {
                    // avl = insert(avl, a);
                    // op_insert(&op_ht, a);
                    // op_find(op_ht, a);
                    op_ht->tries = a;
                    cl_ht->tries = a;
                }
                else
                {
                    printf("\nОшибка ввода!\n");
                }
                printf("\n");
                break; 
            }
            case 18:
            {
                {
                FILE *fp = fopen("test100.txt", "r");
                int num = 0;
                struct tree_node_t *nbtree = NULL;
                avl_node_t *navl = NULL;
                closed_hash_table_t *n_cl = create_cl_hash_table(10000);
                open_hash_table_t *n_op = create_op_hash_table(10000);
                int *t_num = NULL;
                int arr[100];
                int i = 0;
                
                while (fscanf(fp, "%d", &num) == 1)
                {
                    // printf("%d", num);
                    t_num = malloc(sizeof(int));
                    *t_num = num;
                    struct tree_node_t *t_node = node_create((void *) t_num); 
                    nbtree = btree_insert(nbtree, t_node);
                    navl = insert(navl, num);
                    cl_insert(&n_cl, num);
                    op_insert(&n_op, num);
                    arr[i++] = num;
                }

                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                // }

                struct timespec b, e;
                
                for (int i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *as = btree_lookup_2(nbtree, (void*) (arr + i));
                    assert(as);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                    // printf("элемент: %d, время поиска: %llu\n", *(int *)as->name, calc_elapsed_time(&b,&e));
                }

                t1 /= 100;


                size_t s = 0;
                for (int i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    avl_tree_lookup_2(navl, arr[i]);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                t2 /= 100;

                for (int i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    cl_find(n_cl, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t3 += calc_elapsed_time(&b, &e);
                }
                t3 /= 100;

                for (int i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    op_find(n_op, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 100;
                printf("Поиск на 100 элементах (среднее время)\n");
                printf("Время поиска в ДДП: %llu\n", t1);
                printf("Время поиска в АВЛ: %llu\n", t2);
                printf("Время поиска в З.Т: %llu\n", t3);
                printf("Время поиска в ОТ.Т: %llu\n", t4);
                }
                printf("\n");
                {
                FILE *fp = fopen("test500.txt", "r");
                int num = 0;
                struct tree_node_t *nbtree = NULL;
                avl_node_t *navl = NULL;
                closed_hash_table_t *n_cl = create_cl_hash_table(10000);
                open_hash_table_t *n_op = create_op_hash_table(10000);
                int *t_num = NULL;
                int arr[500];
                int i = 0;
                
                while (fscanf(fp, "%d", &num) == 1)
                {
                    // printf("%d", num);
                    t_num = malloc(sizeof(int));
                    *t_num = num;
                    struct tree_node_t *t_node = node_create((void *) t_num); 
                    nbtree = btree_insert(nbtree, t_node);
                    navl = insert(navl, num);
                    cl_insert(&n_cl, num);
                    op_insert(&n_op, num);
                    arr[i++] = num;
                }

                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                // }

                struct timespec b, e;
                size_t s = 0;
                for (int i = 0; i < 500; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *as = btree_lookup_2(nbtree, (void*) (arr + i));
                    assert(as);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                }

                t1 /= 500;

                for (int i = 0; i < 500; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    avl_tree_lookup_2(navl, arr[i]);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                t2 /= 500;

                for (int i = 0; i < 500; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    cl_find(n_cl, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t3 += calc_elapsed_time(&b, &e);
                }
                t3 /= 500;

                for (int i = 0; i < 500; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    op_find(n_op, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 500;
                printf("Поиск на 500 элементах (среднее время)\n");
                printf("Время поиска в ДДП: %llu\n", t1);
                printf("Время поиска в АВЛ: %llu\n", t2);
                printf("Время поиска в З.Т: %llu\n", t3);
                printf("Время поиска в ОТ.Т: %llu\n", t4);
                }
                printf("\n");
                {
                FILE *fp = fopen("test1000.txt", "r");
                int num = 0;
                struct tree_node_t *nbtree = NULL;
                avl_node_t *navl = NULL;
                closed_hash_table_t *n_cl = create_cl_hash_table(10000);
                open_hash_table_t *n_op = create_op_hash_table(10000);
                int *t_num = NULL;
                int arr[1000];
                int i = 0;
                
                while (fscanf(fp, "%d", &num) == 1)
                {
                    // printf("%d", num);
                    t_num = malloc(sizeof(int));
                    *t_num = num;
                    struct tree_node_t *t_node = node_create((void *) t_num); 
                    nbtree = btree_insert(nbtree, t_node);
                    navl = insert(navl, num);
                    cl_insert(&n_cl, num);
                    op_insert(&n_op, num);
                    arr[i++] = num;
                }

                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                // }

                struct timespec b, e;
                size_t s = 0;
                for (int i = 0; i < 1000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *as = btree_lookup_2(nbtree, (void*) (arr + i));
                    assert(as);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                }

                t1 /= 1000;

                for (int i = 0; i < 1000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    avl_tree_lookup_2(navl, arr[i]);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                t2 /= 1000;

                for (int i = 0; i < 1000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    cl_find(n_cl, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t3 += calc_elapsed_time(&b, &e);
                }
                t3 /= 1000;

                for (int i = 0; i < 1000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    op_find(n_op, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 1000;
                printf("Поиск на 1000 элементах (среднее время)\n");
                printf("Время поиска в ДДП: %llu\n", t1);
                printf("Время поиска в АВЛ: %llu\n", t2);
                printf("Время поиска в З.Т: %llu\n", t3);
                printf("Время поиска в ОТ.Т: %llu\n", t4);
                }
                printf("\n");
                {
                FILE *fp = fopen("test10000.txt", "r");
                int num = 0;
                struct tree_node_t *nbtree = NULL;
                avl_node_t *navl = NULL;
                closed_hash_table_t *n_cl = create_cl_hash_table(100000);
                open_hash_table_t *n_op = create_op_hash_table(100000);
                int *t_num = NULL;
                int arr[10000];
                int i = 0;
                
                while (fscanf(fp, "%d", &num) == 1)
                {
                    // printf("%d", num);
                    t_num = malloc(sizeof(int));
                    *t_num = num;
                    struct tree_node_t *t_node = node_create((void *) t_num); 
                    nbtree = btree_insert(nbtree, t_node);
                    navl = insert(navl, num);
                    cl_insert(&n_cl, num);
                    op_insert(&n_op, num);
                    arr[i++] = num;
                }

                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                // }

                struct timespec b, e;
                size_t s = 0;
                for (int i = 0; i < 10000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *as = btree_lookup_2(nbtree, (void*) (arr + i));
                    assert(as);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                }

                t1 /= 10000;

                for (int i = 0; i < 10000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    avl_tree_lookup_2(navl, arr[i]);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                t2 /= 10000;

                for (int i = 0; i < 10000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    cl_find(n_cl, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t3 += calc_elapsed_time(&b, &e);
                }
                t3 /= 10000;

                for (int i = 0; i < 10000; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    op_find(n_op, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 10000;
                printf("Поиск на 10000 элементах (среднее время)\n");
                printf("Время поиска в ДДП: %llu\n", t1);
                printf("Время поиска в АВЛ: %llu\n", t2);
                printf("Время поиска в З.Т: %llu\n", t3);
                printf("Время поиска в ОТ.Т: %llu\n", t4);
                }

                printf("\n");
                {
                FILE *fp = fopen("test10.txt", "r");
                int num = 0;
                struct tree_node_t *nbtree = NULL;
                avl_node_t *navl = NULL;
                closed_hash_table_t *n_cl = create_cl_hash_table(10000);
                open_hash_table_t *n_op = create_op_hash_table(10000);
                int *t_num = NULL;
                int arr[10];
                int i = 0;
                
                while (fscanf(fp, "%d", &num) == 1)
                {
                    // printf("%d", num);
                    t_num = malloc(sizeof(int));
                    *t_num = num;
                    struct tree_node_t *t_node = node_create((void *) t_num); 
                    nbtree = btree_insert(nbtree, t_node);
                    navl = insert(navl, num);
                    cl_insert(&n_cl, num);
                    op_insert(&n_op, num);
                    arr[i++] = num;
                }

                unsigned long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
                // }

                struct timespec b, e;
                size_t s = 0;
                for (int i = 0; i < 10; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    struct tree_node_t *as = btree_lookup_2(nbtree, (void*) (arr + i));
                    assert(as);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                    // printf("элемент: %d, время поиска: %llu\n", *(int *)as->name, calc_elapsed_time(&b,&e));
                }

                t1 /= 10;

                for (int i = 0; i < 10; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    avl_tree_lookup_2(navl, arr[i]);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                t2 /= 10;

                for (int i = 0; i < 10; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    cl_find(n_cl, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t3 += calc_elapsed_time(&b, &e);
                }
                t3 /= 10;

                for (int i = 0; i < 10; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    op_find(n_op, arr[i], &s);
                    timespec_get(&e, TIME_UTC);
                    t4 += calc_elapsed_time(&b, &e);
                }

                t4 /= 10;
                printf("Поиск на 10 элементах (среднее время)\n");
                printf("Время поиска в ДДП: %llu\n", t1);
                printf("Время поиска в АВЛ: %llu\n", t2);
                printf("Время поиска в З.Т: %llu\n", t3);
                printf("Время поиска в ОТ.Т: %llu\n", t4);
                }
                printf("\n");
                printf("Требуемая память\n");
                printf("10 элементов\n");
                printf("ДДП: %lu\n", sizeof(struct tree_node_t) * 10);
                printf("АВЛ: %lu\n", sizeof(avl_node_t) * 10);
                printf("З.Т: %lu\n", sizeof(int) * 10 + sizeof(closed_hash_table_t));
                printf("ОТ.Т: %lu\n", sizeof(node_t) + sizeof(node_t *) * 10 + sizeof(open_hash_table_t));
                printf("\n");
                // printf("Требуемая память\n");
                printf("100 элементов\n");
                printf("ДДП: %lu\n", sizeof(struct tree_node_t) * 100);
                printf("АВЛ: %lu\n", sizeof(avl_node_t) * 100);
                printf("З.Т: %lu\n", sizeof(int) * 100 + sizeof(closed_hash_table_t));
                printf("ОТ.Т: %lu\n", sizeof(node_t) + sizeof(node_t *) * 100 + sizeof(open_hash_table_t));
                printf("\n");
                // printf("Требуемая память\n");
                printf("500 элементов\n");
                printf("ДДП: %lu\n", sizeof(struct tree_node_t) * 500);
                printf("АВЛ: %lu\n", sizeof(avl_node_t) * 500);
                printf("З.Т: %lu\n", sizeof(int) * 500 + sizeof(closed_hash_table_t));
                printf("ОТ.Т: %lu\n", sizeof(node_t) + sizeof(node_t *) * 500 + sizeof(open_hash_table_t));
                printf("\n");
                // printf("Требуемая память\n");
                printf("1000 элементов\n");
                printf("ДДП: %lu\n", sizeof(struct tree_node_t) * 1000);
                printf("АВЛ: %lu\n", sizeof(avl_node_t) * 1000);
                printf("З.Т: %lu\n", sizeof(int) * 1000+ sizeof(closed_hash_table_t));
                printf("ОТ.Т: %lu\n", sizeof(node_t) + sizeof(node_t *) * 1000 + sizeof(open_hash_table_t));
                printf("\n");
                // printf("Требуемая память\n");
                printf("10000 элементов\n");
                printf("ДДП: %lu\n", sizeof(struct tree_node_t) * 10000);
                printf("АВЛ: %lu\n", sizeof(avl_node_t) * 10000);
                printf("З.Т: %lu\n", sizeof(int) * 10000 + sizeof(closed_hash_table_t));
                printf("ОТ.Т: %lu\n", sizeof(node_t) + sizeof(node_t *) * 10000 + sizeof(open_hash_table_t));

                break;
            }
            default:
            {
                printf("Неверный пункт меню!\n");
                break;
            }
        }

    }
    // evaluate_to_tree(root1);
    
    // FILE *fp = fopen("expr.gv", "w");
    // tree_export_to_dot(fp, "expr", root1);
    // int arr[100] = { 0 };
    // int ind = 0;
    // inorder_get(root1, arr, &ind);

    // int i = 0;
    // while (arr[i] && i < 100)
    // {
    //     printf("%d ", arr[i++]);
    // }
    // // make_gv(fp, root1);
    // printf("%lf\n", a);

    

    return 0;
}
