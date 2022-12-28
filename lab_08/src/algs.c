#include "../inc/algs.h"

#define MIN(a, b) ((a) > (b)) ? (b) : (a)

#define NUM_TO_FILL 100000

#include <stdio.h>

void originalFloydWarshall(int matrix[][MAX_SIZE], int numberOfVert) {
    //Пробегаемся по всем вершинам и ищем более короткий путь
    //через вершину k
    for(int k = 0; k < numberOfVert; k++) {
        for(int i = 0; i < numberOfVert; i++) {
            for(int j = 0; j < numberOfVert; j++) {
                //Новое значение ребра равно минимальному между старым
                //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
                matrix[i][j] = MIN(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    
    return;
}

void print_unattainable(int matrix[][MAX_SIZE], int numberOfvert, int vertex) {

    printf("Недостижимые вершины из вершины номер %d:\n", vertex);
    int count = 0;
    for (size_t i = 0; i < (size_t) numberOfvert; ++i)
        // for (size_t j = 0; j < numberOfvert; ++j)
        if (matrix[vertex - 1][i] >= NUM_TO_FILL) {
            printf("%zu\n", i + 1);
            ++count;
        }

    if (count == 0)
        printf("Таких вершин нет!\n");
}

void print_matr(int matrix[][MAX_SIZE], int size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// void originalFloydWarshall(int **matrix, int numberOfVert) {
//     //Пробегаемся по всем вершинам и ищем более короткий путь
//     //через вершину k
//     for(int k = 0; k < numberOfVert; k++) {
//         for(int i = 0; i < numberOfVert; i++) {
//             for(int j = 0; j < numberOfVert; j++) {
//                 //Новое значение ребра равно минимальному между старым
//                 //и суммой ребер i <-> k + k <-> j (если через k пройти быстрее)
//                 matrix[i][j] = MIN(matrix[i][j], matrix[i][k] + matrix[k][j]);
//             }
//         }
//     }
    
//     return;
// }
