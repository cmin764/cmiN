#include <stdlib.h>

#include "stack.h"


void stack_create(stack_t * stack)
{
    stack->size = 0;
    stack->capacity = 1;
    stack->vec = (stack_key_t *)malloc(\
        sizeof(stack_key_t));
}


void stack_destroy(stack_t * stack)
{
    free(stack->vec);
    stack->size = 0;
    stack->capacity = 0;
}


void stack_push(stack_t * stack, stack_key_t key)
{
    if (stack->size + 1 > stack->capacity) {
        stack->vec = (stack_key_t *)realloc(stack->vec,
            sizeof(stack_key_t) * (stack->capacity *= 2));
        if (!stack->vec)
            exit(EXIT_FAILURE);
    }
    stack->vec[stack->size++] = key;
}


stack_key_t stack_pop(stack_t * stack)
{
    return stack->vec[--stack->size];
}


int stack_empty(stack_t * stack)
{
    return !stack->size;
}
