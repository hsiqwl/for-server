#include <stdio.h>
#include "tree.h"
#include "dialog.h"
int main() {
    int (*fptr[])(tree**) = {NULL,tree_insert,tree_delete,tree_search, tree_special_search, traverse,make_image, show, timing,
                             tree_height};
    int command;
    tree* root = NULL;
    while((command = dialog(msgs,Nmsgs)))
    {
        if(fptr[command](&root))
        {
            break;
        }
    }
    printf("end\n");
    delete_tree(&root);
    return 0;
}
