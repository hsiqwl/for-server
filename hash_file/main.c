#include "table.h"
#include "dialog.h"
#include "table_funcs.h"
#include <stdio.h>
int main()
{
    int (*fptr[])(table*) = {NULL,d_add,d_delete,d_find,d_show};
    table* tbl = d_load();
    if(tbl == NULL)
    {
        printf("end\n");
        return 0;
    }
    int command;
    while((command = dialog(msgs,Nmsgs)))
    {
        if(fptr[command](tbl))
        {
            break;
        }
    }
    printf("end\n");
    tbl->ftbl = fopen(tbl->fname,"r+b");
    d_save(tbl);
    fclose(tbl->ftbl);
    delete_table(&tbl);
    return 0;
}


