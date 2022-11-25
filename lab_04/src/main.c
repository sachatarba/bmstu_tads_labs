#include <stdio.h>
#include <assert.h>

#include "../inc/stack_array_t.h"
#include "../inc/stack_list_t.h"

int main(void)
{
    // void *p = NULL;
    // assert(p);

    // stack_array_t arr = create_stack_arr();
    stack_list_t lst = create_stack_list();
    // scanf("%p", &p);

    for (size_t i = 0; i < 3; ++i)
    {
        // scanf("%p", &p);
        // push_stack_arr(arr, p);
        push_stack_list(lst);
    }
    // push_stack_arr(arr, p);
    // push_stack_list(lst, p);
    // pop_stack_arr(arr, &p);
    // printf("%p\n", p);
    // pop_stack_list(lst, &p);
    look_up_stack_list(lst);
    destroy_stack_list(lst);
    look_up_freed_addresses();
    // look_up_stack_arr(arr);
    // destroy_stack_arr(arr);
    // printf("%p\n", p);

    return 0;   
}