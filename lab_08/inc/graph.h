#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stddef.h>

#define MAX_SIZE 100

struct graph
{
    int adjacency_matr[MAX_SIZE][MAX_SIZE];
    size_t num_of_vertices;
};

typedef struct graph graph_t;

int read_graph(FILE *fp, graph_t *gp);

void make_dot_by_graph(FILE *fp, graph_t *gp);

#endif //  __GRAPH_H__
