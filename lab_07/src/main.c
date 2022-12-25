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


int main(void)
{
    Node *root = create_default_expr_tree();
    // double a = evaluate(root);
    
    Node *root1 = create_default_expr_tree();

    while (1)
    {
        int command = 0;
        // printf(menu);
        printf("Введите номер команды: ");
        if (scanf("%d", &command) != 1 || command < 1)
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
                    int *temp = malloc(sizeof(int));
                    *temp = array[0];
                    struct tree_node_t *node = node_create((void *)temp);
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
                    avl_node_t *avl = create_avl_node(array[0]);
                    for (int i = 1; i < 100 && array[i]; ++i)
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
                closed_hash_table_t *ht = create_cl_hash_table(10);

                cl_insert(&ht, 1);
                // cl_insert(&ht, 11);
                // cl_insert(&ht, 21);
                // cl_insert(&ht, 31);
                // cl_insert(&ht, 2);
                // cl_insert(&ht, 3);
                // cl_insert(&ht, 32);
                // cl_insert(&ht, 29);
                cl_insert(&ht, 30);
                cl_insert(&ht, 40);
                look_up_cl_hash_table2(ht);
                cl_find(ht, 1);
                cl_find(ht, 11);
                cl_find(ht, 21);
                cl_find(ht, 31);
                cl_find(ht, 2);
                cl_find(ht, 3);
                cl_find(ht, 32);
                cl_find(ht, 29);
                cl_find(ht, 30);
                cl_find(ht, 0);
                break;
            }
            case 6:
            {
                open_hash_table_t *ht = create_op_hash_table(10);

                op_insert(&ht, 1);
                op_insert(&ht, 11);
                op_insert(&ht, 21);
                op_insert(&ht, 31);
                op_insert(&ht, 2);
                op_insert(&ht, 29);
                op_insert(&ht, 30);
                op_insert(&ht, 0);
                look_up_op_hash_table1(ht);
                op_find(ht, 1);
                op_find(ht, 11);
                op_find(ht, 21);
                op_find(ht, 31);
                op_find(ht, 2);
                op_find(ht, 29);
                op_find(ht, 30);
                op_find(ht, 0);
                ht = restruct_op_ht(ht);
                look_up_op_hash_table1(ht);
            }
            default:
                break;
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
