#include "../inc/graph.h"
#include "../inc/algs.h"

#include <stdlib.h>

#include "../inc/mytime.h"

#define TEST1 "test1.txt"
#define TEST2 "test2.txt"
#define TEST3 "test3.txt"

const char menu[] =
"\n\
1. Тест 1\n\
2. Тест 2\n\
3. Тест 3\n\
4. Ввести граф с консоли\n\
";

int main(void)
{
    while (1)
    {
        int command = 0;
        printf(menu);
        printf("Введите номер команды: ");
        if (scanf("%d", &command) != 1 || command < 1 || command > 4)
        {
            printf("\nОшибка ввода номера команды!\n");
            return 1;
        }
        printf("\n");
        switch (command)
        {
            case 1:
            {
                FILE *fp = fopen("graph.gv", "w");
                
                graph_t gp, new;
                FILE *fin = fopen(TEST1, "r");
                read_graph(fin, &gp);
                make_dot_by_graph(fp, &gp);
                new = gp;
                int a = 0;
                fscanf(fin, "%d", &a);
                // print_matr(gp.adjacency_matr, gp.num_of_vertices);
                struct timespec b;
                struct timespec e;
                timespec_get(&b, TIME_UTC);
                originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                timespec_get(&e, TIME_UTC);
                printf("Время работы (нс): %llu Размер занятой памяти: %zu\n", calc_elapsed_time(&b, &e), sizeof(graph_t));
                // print_matr(new.adjacency_matr, new.num_of_vertices);
                fclose(fp);
                fclose(fin);
                system("dot -Tpng graph.gv > image.png");
                break;
            }

            case 2:
            {
                FILE *fp = fopen("graph.gv", "w");
                
                graph_t gp, new;
                FILE *fin = fopen(TEST2, "r");
                read_graph(fin, &gp);
                make_dot_by_graph(fp, &gp);
                new = gp;
                // print_matr(gp.adjacency_matr, gp.num_of_vertices);
                // originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                int a = 0;
                fscanf(fin, "%d", &a);
                // print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                struct timespec b;
                struct timespec e;
                timespec_get(&b, TIME_UTC);
                originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                timespec_get(&e, TIME_UTC);
                printf("Время работы (нс): %llu Размер занятой памяти: %zu\n", calc_elapsed_time(&b, &e), sizeof(graph_t));
                // print_matr(new.adjacency_matr, new.num_of_vertices);
                fclose(fp);
                fclose(fin);
                system("dot -Tpng graph.gv > image.png");
                break;
            }

            case 3:
            {
                FILE *fp = fopen("graph.gv", "w");
                
                FILE *fin = fopen(TEST3, "r");
                graph_t gp, new;
                read_graph(fin, &gp);
                make_dot_by_graph(fp, &gp);
                new = gp;
                // print_matr(gp.adjacency_matr, gp.num_of_vertices);
                int a = 0;
                fscanf(fin, "%d", &a);
                struct timespec b;
                struct timespec e;
                timespec_get(&b, TIME_UTC);
                originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                timespec_get(&e, TIME_UTC);
                printf("Время работы (нс): %llu Размер занятой памяти: %zu\n", calc_elapsed_time(&b, &e), sizeof(graph_t));
                // originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                // print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                // print_matr(new.adjacency_matr, new.num_of_vertices);
                fclose(fp);
                fclose(fin);
                system("dot -Tpng graph.gv > image.png");
                break;

            }

            case 4:
            {
                FILE *fp = fopen("graph.gv", "w");
                
                graph_t gp, new;
                if (read_graph(stdin, &gp))
                    return 1;
                make_dot_by_graph(fp, &gp);
                new = gp;
                print_matr(gp.adjacency_matr, gp.num_of_vertices);
                // originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                // print_unattainable(new.adjacency_matr, new.num_of_vertices, 2);
                
                int a = 0;
                printf("Введите вершину для проверки достижимости: ");
                if (scanf("%d", &a) != 1 || a < 1 || a > 100)
                {
                    printf("\nОшибка ввода веришны!\n");
                    return 1;
                }
                printf("\n");
                struct timespec b;
                struct timespec e;
                timespec_get(&b, TIME_UTC);
                originalFloydWarshall(new.adjacency_matr, new.num_of_vertices);
                print_unattainable(new.adjacency_matr, new.num_of_vertices, a);
                timespec_get(&e, TIME_UTC);
                printf("Время работы (нс): %llu Размер занятой памяти: %zu\n", calc_elapsed_time(&b, &e), sizeof(graph_t));
                // print_matr(new.adjacency_matr, new.num_of_vertices);
                fclose(fp);
                system("dot -Tpng graph.gv > image.png");
                break;

            }
        }
    }
}
