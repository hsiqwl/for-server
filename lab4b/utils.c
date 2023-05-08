#include "utils.h"
#include <stdio.h>

void print_root(tree** root)
{
    if(*root != NIL)
    {
        printf("key - %d\n", (*root)->key);
    }
}

void graph(tree** root)
{
    FILE* fd = fopen("tree.dot", "a");
    if(*root != NIL)
    {

        if((*root)->right != NIL)
        {
            fprintf(fd,"%d -- %d", (*root)->key, (*root)->right->key);
        }
        if((*root)->left != NIL)
        {
            fprintf(fd, "%d -- %d", (*root)->key, (*root)->left->key);
        }
    }
    fclose(fd);
}