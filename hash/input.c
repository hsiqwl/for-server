#include "input.h"
#include <stdio.h>
int get_uint(unsigned int* value)
{
    int n;
    do
    {
        n = scanf("%u",value);
        if(n==EOF)
        {
            return 1;
        }
        if(n==0)
        {
            while(getchar()!='\n');
            printf("ERROR OCCURED,TRY AGAIN\n");
        }
    }while(n < 0);
    return 0;
}
