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
    table* new = create(tbl->msize);
    int found_elems = 0;
    while((tbl->ks + index)->busy != 0 && visited < tbl->msize)
    {
       if(release!=0)
       {
           if((tbl->ks + index)->key == key && (tbl->ks + index)->release == release)
           {
               insert(key,(tbl->ks + index)->info->value,new);
               found_elems = 1;
               break;
           }
       }
       else
       {
           if ((tbl->ks + index)->key == key && (tbl->ks+index)->busy==1)
           {
               found_elems = 1;
               insert(key,(tbl->ks + index)->info->value,new);
           }
       }
       index = (index + step) % tbl->msize;
       visited++;
    }
    if(found_elems)
    {
        return new;
    }
    else
    {
        delete_table(&new);
        return NULL;
    }
}

int insert(unsigned int key, unsigned int value, table* tbl)
{
    int visited = 0;
    int release = 0;
    int index = get_hash_easy(key,tbl->msize);
    int step = get_hash_primary(key,tbl->msize);
    int empty_pos =  -1;
    while(visited < tbl->msize)
    {
        if((tbl->ks+index)->busy!=1 && empty_pos == -1)
        {
            empty_pos = index;
            if((tbl->ks+index)->busy == 0)
            {
                break;
            }
        }
        if ((tbl->ks+index)->busy!=0 && (tbl->ks + index)->key == key)
        {
            release = (tbl->ks + index)->release;
        }
        index = (index + step) % tbl->msize;
        visited++;
    }
    if(empty_pos!=-1)
    {
        (tbl->ks + empty_pos)->busy = 1;
        (tbl->ks + empty_pos)->key = key;
        (tbl->ks + empty_pos)->release = release + 1;
        if((tbl->ks + empty_pos)->info == NULL)
        {
            (tbl->ks + empty_pos)->info = (item*)malloc(sizeof(item));
        }
        (tbl->ks + empty_pos)->info->value = value;
        return OK;
    }
    return NO_SPACE;
}

int delete(unsigned int key, int release, table* tbl)
{
    int flag = 0;
    int visited = 0;
    int index = get_hash_easy(key,tbl->msize);
    int step = get_hash_primary(key,tbl->msize);
    while((tbl->ks + index)->busy != 0 && visited < tbl->msize)
    {
        if(release!=0)
        {
            if((tbl->ks + index)->key == key && (tbl->ks + index)->release == release && (tbl->ks+index)->busy==1)
            {
                (tbl->ks + index)->busy = -1;
                flag = 1;
                break;
            }
        }
        else
        {
            if((tbl->ks + index)->key == key && (tbl->ks+index)->busy==1)
            {
                (tbl->ks + index)->busy = -1;
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
        if(ptr->busy == 1)
        {
            empty = 0;
            printf("key:%u -> value:%u release:%d\n",ptr->key,ptr->info->value, ptr->release);
        }
        else
        {
            printf("empty\n");
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