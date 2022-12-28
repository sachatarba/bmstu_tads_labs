#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <string.h>

#include "../inc/stack_array_t.h"

#define MAX_SIZE 10000

struct stack_array
{
    DATA_TYPE *content;
    size_t top;
    size_t size;
};

DATA_TYPE top_array(stack_array_t s)
{
    return s->content[s->top - 1];
}

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

void reverse_stack(stack_array_t s1, stack_array_t s2)
{
    while (!is_empty_stack_arr(s1))
    {
        Node *temp = NULL;
        pop_stack_arr(s1, &temp);
        push_stack_arr(s2, temp);
    }
}

double calc_poland_notation(char *buff)
{
    stack_array_t s1 = create_stack_arr();

    Node *temp = malloc(sizeof(Node));
    char *beg = strtok(buff, " ");
    temp->data = atoi(beg);
    temp->is_num = 1;
    push_stack_arr(s1, temp);
    Node node[100];
    temp = malloc(sizeof(Node));
    size_t i = 0;
    while ((beg = strtok(NULL, " ")) != NULL)
    {

        // printf("chars: %c", *beg);
        if ((*beg != '+' && *beg != '-' && *beg != '*') || *(beg + 1) != '\0')
        {
            // char *beg = strtok(buff, " ");
            (node + i)->data = atoi(beg);
            // printf("data: %d\n", temp->data);
            (node + i)->is_num = 1;
            push_stack_arr(s1, node + i);
            // push_stack_arr(s1, temp);
        }
        else if (*beg == '+')
        {
            int a, b;
            pop_stack_arr(s1, &temp);
            a = temp->data;
            pop_stack_arr(s1, &temp);
            b = temp->data;
            // temp = malloc(sizeof(Node));
            (node + i)->data = a + b;
            push_stack_arr(s1, node + i);
            // printf("")
            // printf("%d+%d\n", a, b);
        }
        else if (*beg == '-')
        {
            int a, b;
            pop_stack_arr(s1, &temp);
            a = temp->data;
            pop_stack_arr(s1, &temp);
            b = temp->data;
            // temp = malloc(sizeof(Node));
            (node + i)->data = b - a;
            // printf("%d-%d\n", b, a);
            push_stack_arr(s1, node + i);
        }
        else if (*beg == '*')
        {
            int a, b;
            pop_stack_arr(s1, &temp);
            a = temp->data;
            pop_stack_arr(s1, &temp);
            b = temp->data;
            temp = malloc(sizeof(Node));
            (node + i)->data = a * b;
            // printf("%d*%d\n", a, b);
            push_stack_arr(s1, node + i);
        }
        ++i;
    }

    int a;
    pop_stack_arr(s1, &temp);
    a = temp->data;
    // assert(pop_stack_arr(s1, &temp) == 1);
    return a;
}

double calc_in_stack(stack_array_t s_nums, stack_array_t s_ops)
{
    Node *temp = NULL;

    while (!is_empty_stack_arr(s_ops))
    {
        pop_stack_arr(s_ops, &temp);
        char data = (char) temp->data;
        switch(data)
        {
            case '+':
            {
                // stack.Push(stack.Pop() + stack.Pop());
                int a, b;
                pop_stack_arr(s_nums, &temp);
                a = temp->data;
                pop_stack_arr(s_nums, &temp);
                b = temp->data;
                temp = malloc(sizeof(Node));
                temp->data = a + b;
                push_stack_arr(s_nums, temp);
                break;
            }
            case '-':
            {
                int a, b;
                pop_stack_arr(s_nums, &temp);
                a = temp->data;
                pop_stack_arr(s_nums, &temp);
                b = temp->data;
                temp = malloc(sizeof(Node));
                temp->data = a - b;
                push_stack_arr(s_nums, temp);
                break;
            }
        }
    }

    int a;
    pop_stack_arr(s_nums, &temp);
    a = temp->data;

    // assert(pop_stack_arr())
    
    return a;
}
void to_stack(Node *node, stack_array_t s_nums, stack_array_t s_ops)
{
    if (node == NULL)
        return;

    to_stack(node->left, s_nums, s_ops);
    to_stack(node->right, s_nums, s_ops);

    if (node->is_num)
        push_stack_arr(s_nums, node);
    else
        push_stack_arr(s_ops, node);
}

void look_up_stack_arr(stack_array_t s)
{
    printf("STACK SIZE: %zu", sizeof(*s));
    // assert(s);

    // for (size_t i = s->top - 1; i != (size_t) -1; --i)
    // {
    //     printf("Номер элемента с конца стэка: %zu, значение элемента стэка: %c\n", s->top - i, (char)s->content[i]->data);
    // }
}
