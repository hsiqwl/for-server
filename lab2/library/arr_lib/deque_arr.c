#include <stdlib.h>
#include <stdio.h>
#include "../deque.h"
#include "../funcs.h"

typedef struct deque
{
	int head;
	int tail;
	patient* ptr_to_elems;
	int len;
	int capacity;
}deque;


deque* create_dq(int capacity)
{
	deque* dq = (deque*)malloc(sizeof(deque));
	dq->head = 0;
	dq->tail = 0;
	dq->ptr_to_elems  = (patient*)calloc(capacity,sizeof(patient));
	dq->len = 0;
	dq->capacity = capacity;
	return dq;
}

int insert_front(deque* dq, patient client)
{
	if(!is_full(dq))
	{
		patient* ptr = dq->ptr_to_elems;
		ptr[(dq->head+dq->capacity-1)%dq->capacity] = client;
		dq->head = (dq->head + dq->capacity - 1)%dq->capacity;
		dq->len++;
		return 0;
	}
	else
	{
		return 1;
	}
}

int insert_back(deque* dq,patient client)
{
	if(!is_full(dq))
	{
		patient* ptr = dq->ptr_to_elems;
		ptr[dq->tail] = client;
		dq->tail = (dq->tail+1)%dq->capacity;
		dq->len++;
		return 0;
	}
	else
	{
		return 1;
	}
}

int is_full(deque* dq)
{
	if(dq->len==dq->capacity)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int is_empty(deque* dq)
{
	if(dq==NULL || dq->len==0)
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
		dq->head = (dq->head+1)%dq->capacity;
		dq->len--;
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
		dq->tail = (dq->tail + dq->capacity - 1)%dq->capacity;
		dq->len--;
		return 0;
	}
	else
	{
		return 1;
	}
}

int peek_front(deque* dq,patient* client)
{
	if(!is_empty(dq))
	{
		patient* ptr = dq->ptr_to_elems;
		*client = ptr[dq->head];
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
		printf("'%s'  ", current.id);
	}
	else
	{
		printf("''");
	}
	if(!is_empty(dq))
	{
		patient* ptr = dq->ptr_to_elems;
		int i = 0;
		while(i<dq->len)
		{
			int index = (dq->head + i)%dq->capacity;
			if(ptr[index].id!=NULL)
			{
				printf("'%s' ", ptr[index].id);
			}
			i++;
		}
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
			current->id=NULL;
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
	free(dq->ptr_to_elems);
	free(dq);
}
