#include "stack.h"
#include <stdlib.h>
#include "queue.h"

stack* init_stack(){
    stack* new = (stack*)malloc(sizeof(stack));
    new->top = NULL;
    return new;
}

int stack_empty(stack* s){
    return (s->top == NULL);
}

void push_top(stack* s, int value){
    list* new = (list*)malloc(sizeof(list));
    new->node_index = value;
    new->prev = NULL;
    new->next = s->top;
    s->top = new;
}

void pop_top(stack* s){
    if(!stack_empty(s)){
        list* next_top = s->top->next;
        free(s->top);
        s->top = next_top;
    }
}

int get_top(stack* s){
    if(!stack_empty(s)){
        return s->top->node_index;
    }else{
        return -1;
    }
}

void delete_stack(stack** s){
    if(*s!=NULL){
        list* ptr = (*s)->top;
        while(ptr!=NULL){
            list* next_top = ptr->next;
            free(ptr);
            ptr = next_top;
        }
        free(*s);
    }
}