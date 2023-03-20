#ifndef DEQUE_H
#define DEQUE_H
#include "patient.h"
typedef struct deque deque;

deque* create_dq(int len);
int insert_front(deque* dq, patient client);
int insert_back(deque* dq, patient client);
int is_empty(deque* dq);
int is_full(deque* dq);
int remove_back(deque* dq);
int remove_front(deque* dq);
int peek_front(deque* dq,patient* client);
void status(deque* dq, patient current, int time);
int add_newcomer(deque* dq,patient* next, int* change);
void change_current(deque* dq, patient* current, int* change);
void free_dq(deque* dq);
#endif
