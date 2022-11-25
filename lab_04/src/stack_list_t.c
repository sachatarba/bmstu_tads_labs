#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../inc/stack_list_t.h"

#define MAX_SIZE 10000

struct free_addresses
{
    void *arr[MAX_SIZE];
    size_t size;
} free_addrs;

struct node
{
    DATA_TYPE item;
    struct node *next;
};


struct stack_list
{
    struct node *top;
    size_t elms;
};


stack_list_t create_stack_list(void)
{
    stack_list_t s = malloc(sizeof(struct stack_list));

    if (s)
        s->top = NULL;

    return s;
}


void destroy_stack_list(stack_list_t s)
{
	assert(s);
	
    DATA_TYPE item;

    while (!is_empty_stack_list(s))
        (void) pop_stack_list(s, &item);

    free(s);
}


bool is_empty_stack_list(const stack_list_t s)
{
	assert(s);
	
    return s->top == NULL;
}


bool is_full_stack_list(const stack_list_t s)
{
	assert(s);
	
    return s->elms + 1 <= MAX_SIZE;
}


int push_stack_list(stack_list_t s)
{
	assert(s);
	
    struct node *node = malloc(sizeof(struct node));

    if (!node)
        return 1;

    node->next = s->top;
    node->item = (void *) node;

    s->top = node;
    ++s->elms;

    return 0;
}


int pop_stack_list(stack_list_t s, DATA_TYPE *i)
{
	assert(s);
	
    struct node *node;

    if (is_empty_stack_list(s))
        return 1;

    node = s->top;

    *i = node->item;
    free_addrs.arr[free_addrs.size++] = node->item;
    s->top = node->next;

    free(node);

    return 0;
}


void look_up_stack_list(stack_list_t s)
{
    // printf("Вывод стэка, начиная с последнего элемента:\n")
    size_t i = 1;
    for (struct node *temp = s->top; temp; temp = temp->next)
    {
        printf("Номер элемента с конца стэка: %zu, значение элемента стэка: %p\n", i++, temp->item);
    }
}

void look_up_freed_addresses()
{
    for (size_t i = 0; i < free_addrs.size; i++)
    {
        printf("Номер освобожденного элемента стэка: %zu, значение: %p\n", i + 1, free_addrs.arr[i]);
    }   
}
