#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#define ERR_MSG "error occured, try again\n" 
int get_int(int* value)
{
	int n;
	do
	{
		n = scanf("%d", value);
		if(n==EOF)
		{
			printf("END OF FILE\n");
			return 1;
		}
		if(n==0)
		{
			while(getchar()!='\n');
			printf(ERR_MSG);
		}
	}
	while(n<=0);
	return 0;
}

int get_len(int* len)
{
	do
	{
		printf("input number of elements:");
		int input = get_int(len);
		if(input)
		{
			return 1;
		}
	}while(*len<=0);
	return 0;
}

int input_line(int** arr, int line_lenght)
{
	*arr = (int*)malloc(line_lenght*sizeof(int));
	if(*arr==NULL)
	{
		return 1;
	}
	int* ptr_arr = *arr;
	for(int i = 0;i<line_lenght;++i,++ptr_arr)
	{
		int value;
		printf("input value:");
		if(!get_int(&value))
		{
			*ptr_arr = value;
		}
		else
		{
			return 1;
		}
	}
	return 0;
}

int input_matrix(int lines_count,line** matrix)
{
	*matrix = (line*)malloc(lines_count*sizeof(line));
	if(*matrix == NULL)
	{
		return 1;
	}
	line* ptr_line = *matrix;
	for(int i=0;i<lines_count;++i,++ptr_line)
	{
		int line_lenght;
		if(get_len(&line_lenght) || input_line(&(ptr_line->arr), line_lenght))
		{
			return 1;
		}
		ptr_line->line_lenght = line_lenght;				
	}
	return 0;
}

void print_matrix(line* matrix, int lines_count)
{
	printf("Your matrix:\n");
	line* ptr = matrix;
	for(int i = 0; i < lines_count;++i,++ptr)
	{
		int line_lenght = ptr->line_lenght;
		int* ptr_arr = ptr->arr;
		for(int j=0;j<line_lenght;++j,++ptr_arr)
		{
			printf("%d ",*ptr_arr);
		}
		printf("\n");
	}
}

int cmp(const void* a, const void* b)
{
	int* x = ((line*)a)->arr;
	int* y = ((line*)b)->arr;
	if(*x > *y)
	{
		return 1;
	}
	if(*x == *y)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

void clean_memory(line** matrix, int lines_count)
{
	for(int i=0;i<lines_count;i++)
	{
		free((*matrix + i)->arr);
	}
	free(*matrix);
}

int find_max_lenght(line* matrix, int lines_count)
{
	line* ptr = matrix;
	int max_line = ptr->line_lenght;
	for(int i = 0;i<lines_count;++i,++ptr)
	{
		if(ptr->line_lenght > max_line)
		{
			max_line = ptr->line_lenght;
		}
	}
	return max_line;
}

void add_zeros(line** matrix, int lines_count, int max_lenght)
{
	line* ptr_line = *matrix;
	for(int i = 0;i<lines_count;++i,++ptr_line)
	{
		ptr_line->arr = (int*)realloc(ptr_line->arr,max_lenght*sizeof(int));
		int* ptr_arr = ptr_line->arr;
		ptr_arr = ptr_arr+ptr_line->line_lenght;
		for(int j = ptr_line->line_lenght; j < max_lenght; ++j, ++ptr_arr)
		{
			*ptr_arr = 0;
		}
	}
}

void swap(void* a, void* b, int size)
{
	unsigned char *A = a, *B = b, tmp;
	for(int i  = 0;i<size;i++)
	{
		tmp = A[i];
		A[i] = B[i];
		B[i] = tmp;
	}
}

void swap_first_column(line** matrix, int lines_count, int index)
{
	line* ptr = *matrix;
	for(int i = 0;i<lines_count;++i,++ptr)
	{
		int* first = ptr->arr;
		swap(first,first+index-1,sizeof(int));
	}
}

