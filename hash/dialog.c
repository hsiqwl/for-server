#include "input.h"
#include "table_funcs.h"
#include "dialog.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
int dialog(const char* msgs[], int len)
{
    char* err = "";
    unsigned int command;
    int n;
    do
    {
        printf("%s\n",err);
        err = "ERROR OCCURED,TRY AGAIN";
        for(int i = 0;i<len;++i)
        {
            printf("%s\n",msgs[i]);
        }
        printf("Please make your choice->");
        n = get_uint(&command);
        printf("\n");
        if(n)
        {
            command = 0;
        }
    }while(command<0 || command>=len);
    return command;
}

int d_add(table* tbl)
{
    printf("enter key->");
    unsigned int key;
    if(get_uint(&key))
    {
        return 1;
    }
    printf("enter value->");
    unsigned int value;
    if(get_uint(&value))
    {
        return 1;
    }
    int msg = insert(key,value,tbl);
    printf("%s\n",errmsg[msg]);
    return 0;
}

int d_delete(table* tbl)
{
    printf("enter key->");
    unsigned int key;
    if(get_uint(&key))
    {
        return 1;
    }
    printf("input the release or enter 0 to delete all->");
    unsigned int release;
    if(get_uint(&release))
    {
        return 1;
    }
    int msg = delete(key,release,tbl);
    printf("%s\n",errmsg[msg]);
    return 0;
}

int d_find(table* tbl)
{
    printf("enter key->");
    unsigned int key;
    if(get_uint(&key))
    {
        return 1;
    }
    printf("input the release or enter 0 to find all->");
    unsigned int release;
    if(get_uint(&release))
    {
        return 1;
    }
    table* new = find(key,release,tbl);
    if(new == NULL)
    {
        printf("%s\n",errmsg[NO_KEY]);
    }
    else
    {
        printf("%s\n",errmsg[OK]);
        print(new);
        delete_table(&new);
    }
    return 0;
}

int d_show(table* tbl)
{
    print(tbl);
    return 0;
}
