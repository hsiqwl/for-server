#ifndef QUEUE_H
#define QUEUE_H

typedef struct list{
    int node_index;
    struct list* next;
    struct list* prev;
}list;

typedef struct queue
{
    list* head;
    list* tail;
}queue;

queue* init_q();
void push(queue* q, int node_index);
int pop(queue* q);
int is_empty(queue* q);

#endif