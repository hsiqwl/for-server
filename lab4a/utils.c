#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_root(Tree** root)
{
    printf("%s -- %s -- %d\n",(*root)->key, (*root)->data, (*root)->release);
}

void clear_root(Tree** root)
{
    free(*root);
}