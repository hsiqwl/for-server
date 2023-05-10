#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
void print_root(tree** root)
{
    if(*root != NULL)
    {
        printf("key - %d, value - %s\n", (*root)->key, (*root)->value);
    }
}

void graph(tree** root)
{
    FILE* fd = fopen("tree.dot", "a");
    if(*root != NULL)
    {

        if((*root)->right != NULL)
        {
            fprintf(fd,"%d -- %d\n", (*root)->key, (*root)->right->key);
        }
        if((*root)->left != NULL)
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