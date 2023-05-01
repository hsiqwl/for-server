#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_root(Tree** root)
{
    printf("%s -- %s -- %d\n",(*root)->key, (*root)->data, (*root)->release);
}

void clear_root(Tree** root)
{
    if((*root)->key!=NULL)
    {
        free((*root)->key);
    }
    if((*root)->data!=NULL)
    {
        free((*root)->data);
    }
    free(*root);
}
