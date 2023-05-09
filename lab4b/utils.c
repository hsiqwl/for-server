#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
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
            fprintf(fd,"%d -- %d\n", (*root)->key, (*root)->right->key);
        }
        if((*root)->left != NIL)
        {
            fprintf(fd, "%d -- %d\n", (*root)->key, (*root)->left->key);
        }
    }
    fclose(fd);
}

void delete_root(tree** root)
{
    free((*root)->value);
    free(*root);
}