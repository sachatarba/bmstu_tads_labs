#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "../inc/tree_t.h"
#include "../inc/stack_array_t.h"
#include "../inc/mytime.h"


const char menu[] = 
"\n1. Постфиксный обход\n\
2. Инфиксный обход\n\
3. Префиксный обход\n\
4. Вычислить с помощью дерева\n\
5. Вычислить с помощью стека\n\
6. Замер времени\n\
7. Создание файла, визуализируещего дерево\n\
8. Ввести новые значения\n\
9. Выйти из программы\n\n\
";

int main()
{
    // char postfix[] = "ab+cde+**";
    // char postfix[] = "abcdef+*gh--+i+*+";
    // Node* root = construct(postfix);
    // printf("%zu", sizeof(Node));
    // stack_array_t s = create_stack_arr();
    // look_up_stack_arr(s);
    int command, rc = 0;

    while (rc == 0 && command != 9)
    {
        if (command == 8)
            command = 0;
        printf("Введите 9 чисел (от A до I) в диапазоне [-999, 999]: ");
        Node *root = read_expression();
        if (!root)
        {
            rc = 1;
        }
        printf("\n");
    while (rc == 0 && command != 8)
    {    
        if (command == 9)
            break;
        printf(menu);
        printf("Введите номер команды: ");
        if (scanf("%d", &command) != 1)
        {
            printf("\nОшибка ввода!\n");
            rc = 1;
        }
        printf("\n");
        switch (command)
        {
            
            case 1:
                printf("Постфиксный обход дерева: ");
                postorder(root);
                printf("\n");
                break;
            
            case 2:
                printf("Инфиксный обход дерева: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Префиксный обход дерева: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
            {
                double a = evaluate(root);
                printf("Результат вычисления с помощью дерева выражения: %d\n", (int) a);
                break;
            }
            case 5:
            {
                FILE *fp = fopen("./temp.txt", "w+");
                fpostorder(fp, root);
                fprintf(fp, "\n");
                fclose(fp);
                FILE *f = fopen("temp.txt", "r");
                char buff[1000];
                fgets(buff, 1000, f);
                fclose(f);
                buff[strlen(buff) - 1] = '\0';
                // printf("buff: %s\n", buff);
                double b = calc_poland_notation(buff);
                printf("Результат вычисления с помощью стека: %d\n", (int) b);
                system("rm -f ./temp.txt");
                break;
            }
            case 6:
            {
                struct timespec b;
                struct timespec e;
                unsigned long long t1 = 0, t2 = 0;

                for (size_t i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    evaluate(root);
                    timespec_get(&e, TIME_UTC);
                    t1 += calc_elapsed_time(&b, &e);
                }

                FILE *fp = fopen("./temp.txt", "w+");
                fpostorder(fp, root);
                fprintf(fp, "\n");
                fclose(fp);
                FILE *f = fopen("temp.txt", "r");
                char buff[1000];
                fgets(buff, 1000, f);
                fclose(f);
                buff[strlen(buff) - 1] = '\0';
                // double res = calc_poland_notation(buff);
                system("rm -f ./temp.txt");

                for (size_t i = 0; i < 100; ++i)
                {
                    timespec_get(&b, TIME_UTC);
                    calc_poland_notation(buff);
                    timespec_get(&e, TIME_UTC);
                    t2 += calc_elapsed_time(&b, &e);
                }

                printf("Среднее время вычислений при помощи дерева выражений: %llu\n", t1 / 100);
                printf("Среднее время вычислений выражения польской нотации при помощи стека: %llu\n", t2 / 100);
                break;
            }
            case 7:
            {
                FILE *f = fopen("test.gv", "w");

                assert(f);

                // btree_export_to_dot(f, "Tree_of_expression", root);
                make_gv(f, root);
                fclose(f);
                printf("Файл создан!\n");
                system("dot -Tpng test.gv > image.png");
                // system("mimeopen image.png");
                // system("dot -Tsvg test.gv > image.svg");
                // fclose(f);
                break;
            }
            case 8:
                // command = 0;
                break;
            case 9:
                printf("Завершение программы!\n");
                break;
            default:
                printf("Неверный номер команды!");
                break;
            }
        }
    }


    printf("\n");
    
    // stack_array_t s1 = create_stack_arr(), s2 = create_stack_arr(), s3 = create_stack_arr(), s4 = create_stack_arr();
    // to_stack(root, s1, s2);

    // printf("\n\n\n");
    // look_up_stack_arr(s1);
    // reverse_stack(s2, s4);
    // reverse_stack(s1, s3);
    // // look_up_stack_arr(s);
    // int b = calc_in_stack(s3, s4);
    // printf("Res: %d\n", (int) b);
    // char buff[] = "1 2 3 4 5 6 + * 7 8 - - + 9 + * +";
    // pop_stack_arr()
    return 0;
}