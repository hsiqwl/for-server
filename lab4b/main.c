#include <stdio.h>
#include "tree.h"
#include <readline/readline.h>
#include "utils.h"
int main() {
    int command;
    int n;
    tree* root = NIL;
    do {
        n = scanf("%d", &command);
        if(n==EOF)
        {
            continue;
        }
        if(command==1) {
            int key;
            printf("enter key:");
            scanf("%d", &key);
            char *value = readline("enter key");
            root = insert(root, key, value,NIL);
            root->color = BLACK;
        }
        if(command==2)
        {
            int key;
            printf("enter key:");
            scanf("%d", &key);
            root = delete(root, key);
            root->color = BLACK;
        }
        if(command == 3)
        {
            invert_traverse(root, print_root);
        }
        if(command==4)
        {
            show_tree(root, 0);
        }
        if(command==5)
        {
            make_image(root);
        }
    }while(n!=EOF);
    delete_tree(&root);
}
