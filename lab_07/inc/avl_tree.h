#ifndef __AVL_TREE_T_H__
#define __AVL_TREE_T_H__

typedef struct node avl_node_t;

#include <stdio.h>

struct node // структура для представления узлов дерева
{
	int key;
	unsigned char height;
	avl_node_t *left;
	avl_node_t *right;
};

avl_node_t *create_avl_node(int k);


unsigned char height(avl_node_t* p);


int bfactor(avl_node_t* p);


void fixheight(avl_node_t* p);


avl_node_t* rotateright(avl_node_t* p);



avl_node_t* rotateleft(avl_node_t* q);



avl_node_t* balance(avl_node_t* p);


avl_node_t* insert(avl_node_t* p, int k);


avl_node_t* avl_remove(avl_node_t* p, int k);


void avl_tree_export_to_dot(FILE *f, const char *tree_name, avl_node_t *tree);

#endif //  __AVL_TREE_T_H__
