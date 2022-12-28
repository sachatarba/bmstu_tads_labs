#ifndef __NODE_T_H__
#define __NODE_T_H__

#include <stdbool.h>
#include <stdio.h>

// Структура данных для хранения узла бинарного дерева
typedef struct Node Node;

struct Node
{
    int data;
    Node *left, *right;
    int is_num;
};

void fpostorder(FILE *fp, Node* root);

Node *read_expression();

Node *create_node(int data, Node *left, Node *right, int is_num);

// Функция для проверки, является ли данный токен оператором
bool isOperator(int c);

void make_gv(FILE *fp, Node *node);

void btree_export_to_dot(FILE *f, const char *tree_name, Node *tree);

// Печатаем постфиксное выражение для дерева выражений
void postorder(Node* root);

// Печатаем инфиксное выражение для дерева выражений
void inorder(Node* root);

void preorder(Node* root);

double evaluate(Node* root);

// Функция для построения дерева выражений из заданного постфиксного выражения
Node* construct(char *postfix);

#endif //  __NODE_T_H__
