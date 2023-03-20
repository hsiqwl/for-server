#include <stdio.h>
#include <stdlib.h>
#include "user_view.h"
#include <string.h>

void display_functions()
{
	printf("0.Quit\n");
	printf("1.Read from file\n");
	printf("2.Add by key\n");
	printf("3.Delete by key\n");
	printf("4.Delete by range of keys\n");
	printf("5.Display info\n");
	printf("6.Search by key\n");
	printf("7.Reorganize\n");
}

char* get_string(char* msg)
{
	printf("%s", msg);
	char* ptr = (char*)calloc(1,sizeof(char));
	char buf[81];
	int n, len = 0;
	do
	{
		n = scanf("%80[^\n]", buf);
		if(n<0)
		{
			free(ptr);
			ptr = NULL;
		}
		if(n==0)
		{
			scanf("%*c");
		}
		else
		{
			len+=strlen(buf);
			ptr = (char*)realloc(ptr,len+1);
			ptr = strcat(ptr,buf);
		}
	}while(n>0);
	return ptr;
}
