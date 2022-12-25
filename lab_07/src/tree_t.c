#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../inc/tree_t.h"
#include "../inc/stack_array_t.h"

Node *create_node(int data, Node *left, Node *right, int is_num)
{
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->left = left;
    node->right = right;
    node->is_num = is_num;

    return node;
}

// Функция для проверки, является ли данный токен оператором
bool isOperator(int c) {
    return ((char)c == '+' || (char)c == '-' || (char)c == '*' || (char)c == '/' || (char)c == '^');
}
 
// Печатаем постфиксное выражение для дерева выражений
void postorder(Node* root)
{
    if (root == NULL) {
        return;
    }
 
    postorder(root->left);
    postorder(root->right);
    if (!(root->is_num))
        printf("%c ", root->data);
    else
        printf("%d ", root->data);
}

void fpostorder(FILE *fp, Node* root)
{
    if (root == NULL) {
        return;
    }
 
    fpostorder(fp, root->left);
    fpostorder(fp, root->right);
    if (!(root->is_num))
        fprintf(fp, "%c ", root->data);
    else
        fprintf(fp, "%d ", root->data);
}

void preorder(Node* root)
{
    if (root == NULL) {
        // printf("end!\n");
        return;
    }

    if (!root->is_num)
        printf("%c ", root->data);
    else
        printf("%d ", root->data);
    
    preorder(root->left);
    // printf("<-left");
    // printf("right: ");
    preorder(root->right);
    // printf("<-right");
}

// Печатаем инфиксное выражение для дерева выражений
void inorder(Node* root)
{
    if (root == NULL) {
        return;
    }
 
    // если текущий токен является оператором, вывести открывающую скобку
    if (!(root->is_num)) {
        printf("(");
    }
 
    inorder(root->left);
    if (!(root->is_num))
        printf("%c ", root->data);
    else
        printf("%d ", root->data);
    inorder(root->right);
 
    // если текущий токен является оператором, вывести закрывающую скобку
    if (!(root->is_num)) {
        printf(")");
    }
}

void postorder_set(Node* root, int *arr, int *ind)
{
    if (root == NULL) {
        return;
    }
 
    postorder_set(root->left, arr, ind);
    postorder_set(root->right, arr, ind);
    if ((root->is_num))
    {
        root->data = arr[(*ind)++];
    }
}

void preorder_get(Node* root, int *arr, int *ind)
{
    if (root == NULL) {
        return;
    }
    
    if ((root->is_num))
    {
        arr[(*ind)++] = root->data;
    }
    preorder_get(root->left, arr, ind);
    preorder_get(root->right, arr, ind);
}

void inorder_get(Node* root, int *arr, int *ind)
{
    if (root == NULL) {
        return;
    }
    inorder_get(root->left, arr, ind);

    // if ((root->is_num))
    // {
        arr[(*ind)++] = root->data;
    // }

    inorder_get(root->right, arr, ind);
}

Node *read_expression()
{
    char buff[] = "abcdef+*gh--+i+*+";
    Node *node = construct(buff);
    int arr[9];

    for (size_t i = 0; i < 9; ++i)
        if (scanf("%d", arr + i) != 1 || abs(arr[i]) > 999)
        {
            printf("Ошбика ввода!");
            free(node);
            node = NULL;
            break;
        }
    int size = 0;
    postorder_set(node, arr, &size);
    // snprintf(buff, 20, A + (B * (C + (D * (E + F) - (G - H)) + I)));
    return node;
}

Node *create_default_expr_tree()
{
    char buff[] = "abcdef+*gh--+i+*+";
    Node *node = construct(buff);
    int arr[9] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    int size = 0;
    postorder_set(node, arr, &size);
    // snprintf(buff, 20, A + (B * (C + (D * (E + F) - (G - H)) + I)));
    return node;
}

bool isLeaf(Node* node) {
    return node->left == NULL && node->right == NULL;
}

double process(char op, double x, double y)
{
    if (op == '+') { return x + y; }
    if (op == '-') { return x - y; }
    if (op == '*') { return x * y; }
    if (op == '/') { return x / y; }
 
    return 0;
}
 
// Рекурсивная функция для оценки дерева бинарных выражений
double evaluate(Node* root)
{
    // базовый случай: неверный ввод
    if (root == NULL) {
        return 0;
    }
 
    // листья бинарного дерева выражений являются операндами
    if (isLeaf(root)) {
        return root->data;
    }
 
    // рекурсивно оцениваем левое и правое поддерево
    double x = evaluate(root->left);
    double y = evaluate(root->right);
 
    // применяем оператор в корне к значениям, полученным на предыдущем шаге
    return process(root->data, x, y);
}

double evaluate_to_tree(Node *root)
{
    // базовый случай: неверный ввод
    // printf("bruh");
    if (root == NULL) {
        return 0;
    }
 
    // листья бинарного дерева выражений являются операндами
    if (isLeaf(root) || root->is_num == 1) {
        // printf("leaf: %d", root->data);
        return root->data;
    }
    // printf("root: %d\n", root->data);
    // рекурсивно оцениваем левое и правое поддерево
    double x = evaluate_to_tree(root->left);
    double y = evaluate_to_tree(root->right);
 
    // применяем оператор в корне к значениям, полученным на предыдущем шаге
    root->data = process(root->data, x, y);
    // printf("x: %lf y: %lf, res: %d\n", x, y, root->data);
    root->is_num = 1;
    return root->data;
    // return process(root->data, x, y);
}

// Функция для построения дерева выражений из заданного постфиксного выражения
Node* construct(char *postfix)
{
    // базовый вариант
    if (strlen(postfix) == 0) {
        return NULL;
    }
 
    // создаем пустой stack для хранения указателей дерева
    stack_array_t s = create_stack_arr();
 
    // обход постфиксного выражения
    while (*postfix)
    {
        // если текущий токен является оператором
        if (isOperator(*postfix))
        {
            // извлекаем из stack два узла `x` и `y`
            Node* x = NULL;
            pop_stack_arr(s, &x);
 
            Node* y = NULL;
            pop_stack_arr(s, &y);
 
            // построить новое бинарное дерево, корнем которого является оператор, а
            // левый и правый дочерние элементы указывают на `y` и `x` соответственно
            Node* node = create_node(*postfix, y, x, 0);
 
            // поместить текущий узел в stack
            push_stack_arr(s, node);
        }
 
        // если текущий токен является операндом, создаем новый узел бинарного дерева
        // чей корень является операндом и помещаем его в stack
        else {
            push_stack_arr(s, create_node(*postfix, NULL, NULL, 1));
        }

        ++postfix;
    }
 
    // указатель на корень дерева выражений остается в stack
    return top_array(s);
}

typedef void (*ptr_action_t)(Node*, void*);


// // size_t cur = 0;
// // size_t max = 0;

// функции для вывода дерева в дот файл
void expr_node_to_dot(Node *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->data, tree->left->data);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->data, tree->right->data);
}


void tree_apply_pre(Node *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
    {
        return;
    }
    f(tree, arg);
    tree_apply_pre(tree->left, f, arg);
    tree_apply_pre(tree->right, f, arg);
}

void tree_export_to_dot(FILE *f, const char *tree_name, Node *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    tree_apply_pre(tree, expr_node_to_dot, f);

    fprintf(f, "}\n");
}

void make_gv(FILE *fp, Node *node)
{
    int arr[9];
    int size = 0;
    preorder_get(node, arr, &size);
    // char *buff = malloc(sizeof(char) * 1000);
    fprintf(fp, "digraph t {\nv1 [label = \"+\"]\nv2 [label = \"%d\"]\nv3 [label = \"*\"]\nv4 [label = \"%d\"]\nv5 [label = \"+\"]\nv6 [label = \"+\"]\nv7 [label = \"%d\"]\nv8 [label = \"-\"]\nv9 [label = \"*\"]\nv10 [label = \"%d\"]\nv11 [label = \"+\"]\nv12 [label = \"%d\"]\nv13 [label = \"%d\"]\nv14 [label = \"-\"]\nv15 [label = \"%d\"]\nv16 [label = \"%d\"]\nv17 [label = \"%d\"]\nv1 -> v2;\nv1 -> v3;\nv3 -> v4;\nv3 -> v5;\nv5 -> v6;\nv5 -> v17;\nv6 -> v7;\nv6 -> v8;\nv8 -> v9;\nv9 -> v10;\nv9 -> v11;\nv11 -> v12;\nv11 -> v13;\nv8 -> v14;\nv14 -> v15;\nv14 -> v16;\n}\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);
    // fprintf(fp, buff);
}

// void print_exp_tree_ev(FILE *fp, Node *node)
// {
//     int arr[9];
//     int size = 0;
//     preorder_get(node, arr, &size);
//     // char *buff = malloc(sizeof(char) * 1000);
//     fprintf(fp, "digraph t {\nv1 [label = \"%d\"]\nv2 [label = \"%d\"]\nv3 [label = \"%d\"]\nv4 [label = \"%d\"]\nv5 [label = \"%d\"]\nv6 [label = \"%d\"]\nv7 [label = \"%d\"]\nv8 [label = \"%d\"]\nv9 [label = \"%d\"]\nv10 [label = \"%d\"]\nv11 [label = \"%d\"]\nv12 [label = \"%d\"]\nv13 [label = \"%d\"]\nv14 [label = \"%d\"]\nv15 [label = \"%d\"]\nv16 [label = \"%d\"]\nv17 [label = \"%d\"]\nv1 -> v2;\nv1 -> v3;\nv3 -> v4;\nv3 -> v5;\nv5 -> v6;\nv5 -> v17;\nv6 -> v7;\nv6 -> v8;\nv8 -> v9;\nv9 -> v10;\nv9 -> v11;\nv11 -> v12;\nv11 -> v13;\nv8 -> v14;\nv14 -> v15;\nv14 -> v16;\n}\n", arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);
//     // fprintf(fp, buff);
// }

// void node_to_dot(Node *tree, void *param)
// {
//     FILE *f = param;

//     if (tree->left)
//     {
//         if (tree->left->is_num)
//             fprintf(f, "v%zu [label = \"%c\"]\nv%zu [label = \"%d\"]\nv%zu -> v%zu;\n", cur, tree->data, max + 1, tree->left->data, cur, max + 1);
//         else
//             fprintf(f, "v%zu [label = \"%c\"]\nv%zu [label = \"%c\"]\nv%zu -> v%zu;\n", cur, tree->data, max + 1, tree->left->data, cur, max + 1);
//         cur += 1;
//         max += 1;
//     }
//     if (tree->right)
//     {    // fprintf(f, "[]%d -> %d;\n", tree->data, tree->right->data);
//         if (tree->right->is_num)
//             fprintf(f, "v%zu [label = \"%c\"]\nv%zu [label = \"%d\"]\nv%zu -> v%zu;\n", cur, tree->data, max + 1, tree->right->data, cur, max + 1);
//         else
//             fprintf(f, "v%zu [label = \"%c\"]\nv%zu [label = \"%c\"]\nv%zu -> v%zu;\n", cur, tree->data, max + 1, tree->right->data, cur, max + 1);
//         cur += 1;
//         max += 1;
//     }
// }

// void node_to_dot_label(Node *tree, void *param)
// {
//     FILE *f = param;

//     if (tree && cur >= max)
//     {
//         if (tree->is_num)
//             fprintf(f, "v%zu [label = \"%d\"]\n", cur, tree->data);
//         else
//             fprintf(f, "v%zu [label = \"%c\"]\n", cur, tree->data);
//         cur += 1;
//         max += 1;
//     }
// }


// void btree_export_to_dot(FILE *f, const char *tree_name, Node *tree)
// {
//     fprintf(f, "digraph %s {\n", tree_name);

//     btree_apply_pre(tree, node_to_dot_label, f);

//     fprintf(f, "}\n");
// }

