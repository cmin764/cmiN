#ifndef STACK_H
#define STACK_H


#include <stdlib.h>


typedef int stack_key_t;


typedef struct {
    size_t size;
    size_t capacity;
    stack_key_t * vec;
} stack_t;


void stack_create(stack_t *);
void stack_destroy(stack_t *);
void stack_push(stack_t *, stack_key_t);
stack_key_t stack_pop(stack_t *);
int stack_empty(stack_t *);


#endif /* STACK_H */
