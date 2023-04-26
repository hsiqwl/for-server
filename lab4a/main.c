#include <stdio.h>
#include <readline/readline.h>
#include "tree.h"
#include "utils.h"
#include <stdlib.h>
int main()
{
    int command, n;
    Tree* root = NULL;
    do
    {
        n = scanf("%d",&command);
        if(command == 1)
        {
            char* key = readline("enter key:");
            char* data = readline("enter value:");
            Tree* node = (Tree*)malloc(sizeof(Tree));
            node->key = strdup(key);
            node->data = strdup(data);
            node->left = NULL;
            node->right = NULL;
            node->next = NULL;
            node->prev = NULL;
            insert(&root, node);
            free(key);
            free(data);
        }
        if(command == 2)
        {
            direct_travers(root, print_root);
        }
        if(command == 4)
        {
            FILE* fd = fopen("tree.dot" , "w");
            make_graph(root, &fd);
            system("dot -Tpng -O tree.dot");
        }
        if(command == 3)
        {
            char* key = readline("enter key:");
            delete(&root, key);
            free(key);
        }
    }while(n!=EOF);
}
