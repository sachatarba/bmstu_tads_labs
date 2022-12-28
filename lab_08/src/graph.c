#include <string.h>

#include "../inc/graph.h"

#include <stdlib.h>

#define NUM_TO_FILL 100000

int read_graph(FILE *fp, graph_t *gp)
{
    // memset(gp, NUM_TO_FILL, sizeof(*gp));
    for (size_t i = 0; i < MAX_SIZE; ++i)
    {
        for (size_t j = 0; j < MAX_SIZE; ++j)
        {
            gp->adjacency_matr[i][j] = NUM_TO_FILL;
        }
    }
    int size = 0;
    
    if (fp == stdin)
        printf("Введите число вершин графа: ");
    
    if (fscanf(fp, "%d", &size) != 1 || size < 1 || size > MAX_SIZE)
    {
        if (fp == stdin)
            printf("\nОшибка ввода!\n");
        
        return 1;   
    }

    if (fp == stdin)
        printf("\n");

    int a = 0, b = 0;

    int ribs = 0;

    if (fp == stdin)
        printf("Введите число ребер в графе: ");
    
    if (fscanf(fp, "%d", &ribs) != 1 || ribs < 1 || ribs > MAX_SIZE * (MAX_SIZE - 1))
    {
        printf("\nОшибка ввода числа ребер\n");
        return 1;
    }    

    printf("\n");

    for (int i = 0; i < ribs; ++i)
    {
        if (fp == stdin)
            printf("Введите через пробел числа i j (начиная с 1), чтобы сформировать ребро из i-ой в j-ую вершину: ");
        
        if (fscanf(fp, "%d %d", &a, &b) != 2 || a < 1 || b < 1 || a > MAX_SIZE || b > MAX_SIZE)
        {
            printf("\nОшибка ввода вершин!\n");
            return 1;
        }

        printf("\n");

        if (gp->adjacency_matr[a - 1][b - 1] == 1)
        {
            if (fp == stdin)
                printf("Ошибка. Ребро уже было сформировано!\n");
            return 1;
        }
        else
        {
            gp->adjacency_matr[a - 1][b - 1] = 1;
        }
    }  

    gp->num_of_vertices = size;

    return 0;
}

void make_dot_by_graph(FILE *fp, graph_t *gp)
{
    fprintf(fp, "digraph gp {\n");

    for (size_t i = 0; i < gp->num_of_vertices ; ++i)
        for (size_t j = 0; j < gp->num_of_vertices; ++j)
        {
            if (gp->adjacency_matr[i][j] == 1)
                fprintf(fp, "v%zu -> v%zu\n", i + 1, j + 1);
        }
    fprintf(fp, "}\n");
}
