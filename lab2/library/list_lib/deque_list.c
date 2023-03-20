#include <stdlib.h>
#include <stdio.h>
#include "../deque.h"
#include "../funcs.h"

typedef struct List
{
	patient client;
	struct List* next;
	struct List* prev;
}List;

typedef struct deque
{
	List* head;
	List* tail;
}deque;

deque* create_dq(int len)
{
	deque* dq = (deque*)malloc(sizeof(deque));
	dq->head = NULL;
	dq->tail = dq->head;
	return dq;
}

int insert_front(deque* dq, patient client)
{
	List* new_head = (List*)malloc(sizeof(List));
	new_head->client = client;
	new_head->prev = NULL;
	new_head->next = dq->head;
	if(is_empty(dq))
	{
		dq->tail = new_head;	
	}
	dq->head = new_head;
	return 0;
}

int insert_back(deque* dq, patient client)
{
	List* new_tail = (List*)malloc(sizeof(List));
	new_tail->client = client;
	new_tail->next = NULL;
	new_tail->prev = dq->head;
	if(is_empty(dq))
	{
		dq->head = new_tail;
	}
	dq->tail = new_tail;
	return 0;
}

int is_empty(deque* dq)
{
	if(dq->head==NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int remove_front(deque* dq)
{
	if(!is_empty(dq))
	{
		List* old_head = dq->head;
		dq->head = dq->head->next;
		dq->head->prev = NULL;
		free(old_head);
		return 0;
	}
	else
	{
		return 1;
	}
}

int remove_back(deque* dq)
{
	if(!is_empty(dq))
	{
		List* old_tail = dq->tail;
		dq->tail = dq->tail->prev;
		dq->tail->next = NULL;
		free(old_tail);
	}
	else
	{
		return 1;
	}
}

int peek_front(deque* dq, patient* client)
{
	if(!is_empty(dq))
	{
		*client = dq->head->client;
		return 0;
	}
	else
	{
		return 1;
	}
}
void status(deque* dq, patient current, int time)
{
	printf("%d\n", time);
	if(current.id!=NULL)
	{
		printf("'%s'  ",current.id);
	}
	else
	{
		printf("''");
	}
	if(!is_empty(dq))
	{
		List* ptr = dq->head;
		do
		{
			printf("'%s' ",ptr->client.id);
			ptr = ptr->next;
		}while(ptr!=dq->head);
	}
	printf("\n");
}


int add_newcomer(deque* dq, patient* next, int* change)
{
	if(next->flag || is_empty(dq))
	{
		if(insert_front(dq,*next))
		{
			*change = 0;
		}
		else
		{
			*change = 1;
		}
	}
	else
	{
		if(insert_back(dq,*next))
		{
			*change = 0;
		}
		else
		{
			*change = 1;
		}
	}
	return (*change);
}

void change_current(deque* dq, patient* current, int* change)
{
	if(current->time_out<=0)
	{
		if(current->id!=NULL && *(current->id)!=0)
		{
			free(current->id);
			current->id = NULL;
			*change = 1;
		}
		peek_front(dq,current);
		if(!remove_front(dq))
		{
			*change = 1;
		}
	}
}
void free_dq(deque* dq)
{
	if(dq->head!=NULL)
	{
		free(dq->head);
	}
	if(dq->tail!=NULL)
	{
		free(dq->tail);
	}
	free(dq);
}
