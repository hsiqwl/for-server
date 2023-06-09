#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_int(int* value)
{
    int n;
    do
    {
        n = scanf("%d",value);
        if(n==EOF)
        {
            return 1;
        }
        if(n==0 || *value<0)
        {
            while(getchar()!='\n');
            printf("try again\n");
        }
    }
    while(n<=0);
    return 0;
}

char* get_str(FILE* fd)
{
    char* ptr = (char*)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do
    {
        n = fscanf(fd,"%80[^\n]", buf);
        if(n<0)
        {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if(n==0)
        {
            fscanf(fd,"%*c");
        }
        else
        {
            len += strlen(buf);
            ptr = (char*)realloc(ptr,len+1);
            strcat(ptr,buf);
        }
    }while(n>0);
    return ptr;
}

