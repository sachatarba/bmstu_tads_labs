#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../inc/stack_array_t.h"

#define MAX_SIZE 10000

struct stack_array
{
    DATA_TYPE *content;
    size_t top;
    size_t size;
};


stack_array_t create_ex(size_t size)
{
    stack_array_t s = malloc(sizeof(struct stack_array));

    if (s)
    {
        s->content = malloc(size * sizeof(DATA_TYPE));

        if (s->content)
        {
            s->size = size;

            make_empty_stack_arr(s);
        }
        else
        {
            free(s);

            s = NULL;
        }
    }

    return s;
}


stack_array_t create_stack_arr(void)
{
    return create_ex(MAX_SIZE);
}


void destroy_stack_arr(stack_array_t s)
{
	assert(s);
	
    free(s->content);
    free(s);
}


void make_empty_stack_arr(stack_array_t s)
{
	assert(s);
	
    s->top = 0;
}


bool is_empty_stack_arr(const stack_array_t s)
{
	assert(s);
	
    return s->top == 0;
}


bool is_full_stack_arr(const stack_array_t s)
{
	assert(s);
	
    return s->top == s->size;
}


int push_stack_arr(stack_array_t s, DATA_TYPE elm)
{
	assert(s);
	
    if (is_full_stack_arr(s))
        return 1;

    s->content[(s->top)++] = elm;

    return 0;
}


int pop_stack_arr(stack_array_t s, DATA_TYPE *elm)
{
	assert(s);
	
    if (is_empty_stack_arr(s))
        return 1;

    *elm = s->content[--(s->top)];

    return 0;
}


void look_up_stack_arr(stack_array_t s)
{
    assert(s);

    for (size_t i = s->top - 1; i != (size_t) -1; --i)
    {
        printf("Номер элемента с конца стэка: %zu, значение элемента стэка: %p\n", s->top - i, s->content[i]);
    }
}
