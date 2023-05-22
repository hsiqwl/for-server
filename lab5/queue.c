#include "queue.h"
#include <stdlib.h>

queue* init_q() {
    queue *new = (queue *) malloc(sizeof(queue));
    new->head = NULL;
    new->tail = NULL;
    return new;
}

void push(queue* q, int node_index) {
    list *new = (list *) malloc(sizeof(list));
    new->node_index = node_index;
    new->next = NULL;
    new->prev = NULL;
    if (q->head == NULL) {
        q->head = new;
        q->tail = new;
    } else {
        new->prev = q->tail;
        q->tail->next = new;
        q->tail = new;
    }
}

int pop(queue* q) {
    if (q->head == NULL) {
        return -1;
    } else {
        int value = q->tail->node_index;
        if(q->head == q->tail){
            list* old_tail = q->tail;
            free(old_tail);
            q->head = NULL;
            q->tail = NULL;
        }else{
            list* old_tail = q->tail;
            q->tail = q->tail->prev;
            free(old_tail);
        }
        return value;
    }
}

int is_empty(queue* q) {
    if (q->head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void clear_q(queue** q){
    if(*q == NULL){
        return;
    }
    list* ptr = (*q)->head;
    while(ptr!=NULL){
        list* next_ptr = ptr->next;
        free(ptr);
        ptr = next_ptr;
    }
    free(*q);
}