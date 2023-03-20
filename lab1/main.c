#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#define END_MSG "end of prog\n"
int main()
{
	line* matrix;
	int lines_count, max_lenght, index;
	if(get_len(&lines_count) || input_matrix(lines_count,&matrix))
	{
		printf(END_MSG);
		return 1;
	}
	print_matrix(matrix,lines_count);
	max_lenght = find_max_lenght(matrix, lines_count);
	add_zeros(&matrix, lines_count, max_lenght);
	printf("Enter index of the column:");
	if(!get_int(&index))
	{
		swap_first_column(&matrix, lines_count, index);
		qsort(matrix,lines_count,sizeof(line),cmp);
		swap_first_column(&matrix, lines_count, index);
		printf("Matrix has been edited\n");
		print_matrix(matrix,lines_count);
		clean_memory(&matrix,lines_count);
		return 0;
	}
	else
	{
		printf(END_MSG);
		return 1;
	}
}
