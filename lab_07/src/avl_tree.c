#include "../inc/avl_tree.h"
#include <stdlib.h>
#include <stdio.h>
// node(int k) { key = k; left = right = 0; height = 1; }

int avl_tries; 

avl_node_t *create_avl_node(int k)
{
    avl_node_t *node = malloc(sizeof(avl_node_t));
    
    if (!node)
        return node;
    
    *node = (avl_node_t) { .key = k, .left = 0, .right = 0, .height = 1 };

    return node;
}

unsigned char height(avl_node_t* p)
{
	return p?p->height:0;
}

int bfactor(avl_node_t* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(avl_node_t* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

avl_node_t* rotateright(avl_node_t* p) // правый поворот вокруг p
{
	avl_node_t* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

avl_node_t* rotateleft(avl_node_t* q) // левый поворот вокруг q
{
	avl_node_t* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

avl_node_t* balance(avl_node_t* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

avl_node_t* insert(avl_node_t* p, int k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return create_avl_node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else if (k>p->key)
		p->right = insert(p->right,k);
	return balance(p);
}

avl_node_t* findmin(avl_node_t* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

avl_node_t* removemin(avl_node_t* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

avl_node_t* avl_remove(avl_node_t* p, int k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->key )
		p->left = avl_remove(p->left,k);
	else if( k > p->key )
		p->right = avl_remove(p->right,k);	
	else //  k == p->key 
	{
		avl_node_t* q = p->left;
		avl_node_t* r = p->right;
		free(p);
		if( !r ) return q;
		avl_node_t* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

typedef void (*ptr_action_t)(avl_node_t*, void*);

void avl_node_to_dot(avl_node_t *tree, void *param)
{
    FILE *f = param;

    if (tree->left)
        fprintf(f, "%d -> %d;\n", tree->key, tree->left->key);

    if (tree->right)
        fprintf(f, "%d -> %d;\n", tree->key, tree->right->key);
}

void avl_tree_apply_pre(avl_node_t *tree, ptr_action_t f, void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    avl_tree_apply_pre(tree->left, f, arg);
    avl_tree_apply_pre(tree->right, f, arg);
}

void avl_tree_export_to_dot(FILE *f, const char *tree_name, avl_node_t *tree)
{
    fprintf(f, "digraph %s {\n", tree_name);

    avl_tree_apply_pre(tree, avl_node_to_dot, f);

    fprintf(f, "}\n");
}

avl_node_t *avl_tree_lookup_2(avl_node_t *tree, int num)
{
    int cmp;
    avl_tries = 1;
    while (tree != NULL)
    {
        // cmp = strcmp(name, tree->name);
        cmp = num - tree->key;
        if (cmp == 0)
            return tree;
        else if (cmp < 0)
            tree = tree->left;
        else
            tree = tree->right;
        ++avl_tries;
    }

    return NULL;
}
