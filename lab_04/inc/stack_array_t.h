#ifndef __STACK_ARRAY_T_H__

#define __STACK_ARRAY_T_H__

#include <stdbool.h>

#define DATA_TYPE void*

typedef struct stack_array* stack_array_t;

stack_array_t create_stack_arr(void);

void destroy_stack_arr(stack_array_t s);

void make_empty_stack_arr(stack_array_t s);

bool is_empty_stack_arr(const stack_array_t s);

bool is_full_stack_arr(const stack_array_t s);

int push_stack_arr(stack_array_t s, DATA_TYPE i);

int pop_stack_arr(stack_array_t s, DATA_TYPE *i);

void look_up_stack_arr(stack_array_t s);

#endif //  __STACK_ARRAY_T_H__
