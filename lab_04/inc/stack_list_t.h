#ifndef __STACK_LIST_T_H__

#define __STACK_LIST_T_H__

#include <stdbool.h>

#define DATA_TYPE void*

typedef struct stack_list* stack_list_t;

unsigned long long get_node_size(void);

stack_list_t create_stack_list(void);

void destroy_stack_list(stack_list_t s);

void make_empty_stack_list(stack_list_t s);

bool is_empty_stack_list(const stack_list_t s);

bool is_full_stack_list(const stack_list_t s);

int push_stack_list(stack_list_t s);

int pop_stack_list(stack_list_t s, DATA_TYPE*i);

void look_up_stack_list(stack_list_t s);

void look_up_freed_addresses();

#endif //  __STACK_LIST_T_H__
