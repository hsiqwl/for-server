#include "utils.h"
#include <stdio.h>
void print_root(Tree** root)
{
    printf("%s -- %s\n",(*root)->key, (*root)->data);
}
