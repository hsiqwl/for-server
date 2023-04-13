#include "input.h"
#include "table_funcs.h"
#include "dialog.h"
#include "errors.h"
#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

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

table* d_load()
{
    int msize = 0;
    table* tbl = NULL;
    printf("enter name of the file you want to read from:");
    char* fname = readline("");
    FILE* ftbl = fopen(fname,"r+b");
    if(ftbl==NULL)
    {
        printf("looks like there is no such file, let's make one!\n");
        printf("enter the size of table:");
        if(get_uint(&msize))
        {
            return NULL;
        }
        ftbl = fopen(fname,"w+b");
        tbl = create(msize);
        tbl->ftbl = ftbl;
        d_save(tbl);
    }
    else
    {
        fread(&msize, sizeof(int), 1, ftbl);
        tbl = create(msize);
        tbl->ftbl = ftbl;
        load(tbl);
    }
    fclose(tbl->ftbl);
    tbl->fname = strdup(fname);
    free(fname);
    return tbl;
}

void d_save(table* tbl)
{
    keyspace* ptr = tbl->ks;
    fseek(tbl->ftbl,0,SEEK_SET);
    fwrite(&tbl->msize,sizeof(int),1,tbl->ftbl);
    for(int i = 0;i<tbl->msize;++i,++ptr)
    {
        fwrite(&ptr->busy, sizeof(int), 1, tbl->ftbl);
        fwrite(&ptr->key, sizeof(int), 1, tbl->ftbl);
        fwrite(&ptr->release, sizeof(int), 1, tbl->ftbl);
        fwrite(&ptr->offset,sizeof(int), 1, tbl->ftbl);
    }
}
