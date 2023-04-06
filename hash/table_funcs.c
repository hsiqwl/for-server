#include "table.h"
#include "table_funcs.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

table* create(int msize)
{
    table* new = (table*)malloc(sizeof(table));
    new->ks = (keyspace*)calloc(msize,sizeof(keyspace));
    new->msize = msize;
    return new;
}

table* find(unsigned int key, int release, table* tbl)
{
    int visited = 0;
    int index = get_hash_easy(key,tbl->msize);
    int step = get_hash_primary(key,tbl->msize);
    table* new = create(1);
    int new_size = 0;
    while((tbl->ks + index)->busy == 1 && visited < tbl->msize)
    {
       if(release!=0)
       {
           if((tbl->ks + index)->key == key && (tbl->ks + index)->release == release)
           {
               insert(key,(tbl->ks + index)->info->value,new);
               new_size++;
               break;
           }
       }
       else
       {
           if ((tbl->ks + index)->key == key)
           {
               new_size++;
               new->ks = (keyspace*)realloc(new->ks,new_size * sizeof(keyspace));
               (new->ks + new_size - 1)->busy = 0;
               (new->ks + new_size - 1)->info = NULL;
               insert(key,(tbl->ks + index)->info->value,new);
               new->msize++;
           }
       }
       index = (index + step) % tbl->msize;
       visited++;
    }
    if(new_size)
    {
        new->msize = new_size;
        return new;
    }
    else
    {
        return NULL;
    }
}

int insert(unsigned int key, unsigned int value, table* tbl)
{
    int visited = 0;
    int release = 0;
    int index = get_hash_easy(key,tbl->msize);
    int step = get_hash_primary(key,tbl->msize);
    while(visited < tbl->msize)
    {
        if((tbl->ks+index)->busy==0)
        {
            if((tbl->ks + index)->info == NULL)
            {
                (tbl->ks + index)->info = (item*)malloc(sizeof(item));
            }
            (tbl->ks + index)->info->value = value;
            (tbl->ks + index)->key = key;
            (tbl->ks + index)->release = release + 1;
            (tbl->ks + index)->busy = 1;
            return OK;
        }
        else if ((tbl->ks + index)->key == key)
        {
            release = (tbl->ks + index)->release;
        }
        index = (index + step) % tbl->msize;
        visited++;
    }
    return NO_SPACE;
}

int delete(unsigned int key, int release, table* tbl)
{
    int flag = 0;
    int visited = 0;
    int index = get_hash_easy(key,tbl->msize);
    int step = get_hash_primary(key,tbl->msize);
    while((tbl->ks + index)->busy == 1 && visited < tbl->msize)
    {
        if(release!=0)
        {
            if((tbl->ks + index)->key == key && (tbl->ks + index)->release == release)
            {
                (tbl->ks + index)->busy = 0;
                return OK;
            }
        }
        else
        {
            if((tbl->ks + index)->key == key)
            {
                (tbl->ks + index)->busy = 0;
                flag = 1;
            }
        }
        index = (index + step) % tbl->msize;
        visited++;
    }
    if(flag)
    {
        return OK;
    }
    return NO_KEY;
}

void print(const table* tbl)
{
    int empty = 1;
    keyspace* ptr = tbl->ks;
    for(int i = 0;i < tbl->msize;++i,++ptr)
    {
        if(ptr->busy)
        {
            empty = 0;
            printf("key:%u -> value:%u release:%d\n",ptr->key,ptr->info->value, ptr->release);
        }
    }
    if(empty)
    {
        printf("table is empty\n");
    }
}

void delete_table(table** tbl)
{
    keyspace* ptr = (*tbl)->ks;
    int i = 0;
    while(i<(*tbl)->msize)
    {
        if(ptr->info != NULL)
        {
            free(ptr->info);
        }
        ++i;
        ++ptr;
    }
    free((*tbl)->ks);
    free(*tbl);
}