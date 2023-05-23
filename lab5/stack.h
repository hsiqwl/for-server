#ifndef STACK_H
#define STACK_H
#include "queue.h"
typedef struct stack{
    list* top;
}stack;

stack* init_stack();
int stack_empty(stack* s);
void push_top(stack* s, int value);
void pop_top(stack* s);
int get_top(stack* s);
void delete_stack(stack** s);

#endif