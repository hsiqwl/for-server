#include <stdio.h>
#include "tree.h"
#include "dialog.h"
int main()
{
    int (*fptr[])(Tree**) = {NULL,tree_insert,tree_delete,tree_search, tree_special_search, traverse,make_image, show};
    int command;
    Tree* root = NULL;
    while((command = dialog(msgs,Nmsgs)))
    {
        if(fptr[command](&root))
        {
            break;
        }
    }
    printf("end\n");
    free_tree(&root);
    return 0;

}
