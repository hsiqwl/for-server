#include "table.h"
#include "table_funcs.h"
#include "errors.h"
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include <string.h>
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
    new->ftbl = tbl->ftbl;
    new->fname = strdup(tbl->fname);
    int found_elems = 0;
    while((tbl->ks + index)->busy != 0 && visited < tbl->msize)
    {
       if(release!=0)
       {
           if((tbl->ks + index)->key == key && (tbl->ks + index)->release == release)
           {
               found_elems = 1;
               int value;
               tbl->ftbl = fopen(tbl->fname,"r+b");
               fseek(tbl->ftbl, (tbl->ks+index)->offset, SEEK_SET);
               fread(&value,sizeof(int),1, tbl->ftbl);
               fclose(tbl->ftbl);
               insert(key,value,new);
               break;
           }
       }
       else
       {
           if ((tbl->ks + index)->key == key && (tbl->ks+index)->busy==1)
           {
               found_elems = 1;
               int value;
               tbl->ftbl = fopen(tbl->fname,"r+b");
               fseek(tbl->ftbl, (tbl->ks+index)->offset, SEEK_SET);
               fread(&value,sizeof  (int),1, tbl->ftbl);
               fclose(tbl->ftbl);
               insert(key,value,new);
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
        tbl->ftbl = fopen(tbl->fname,"r+b");
        fseek(tbl->ftbl, 0,SEEK_END);
        (tbl->ks + empty_pos)->busy = 1;
        (tbl->ks + empty_pos)->key = key;
        (tbl->ks + empty_pos)->release = release + 1;
        (tbl->ks + empty_pos)->offset = ftell(tbl->ftbl);
        fwrite(&value,sizeof(int),1, tbl->ftbl);
        fclose(tbl->ftbl);
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

void print(table* tbl)
{
    int empty = 1;
    keyspace* ptr = tbl->ks;
    tbl->ftbl = fopen(tbl->fname, "r+b");
    for(int i = 0;i < tbl->msize;++i,++ptr)
    {
        if(ptr->busy == 1)
        {
            empty = 0;
            printf("key:%u -> ",ptr->key);
            int value;
            fseek(tbl->ftbl, ptr->offset,SEEK_SET);
            fread(&value,sizeof(int),1,tbl->ftbl);
            printf("value:%u release:%d\n",value,ptr->release);
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
    fclose(tbl->ftbl);
}

void delete_table(table** tbl)
{
    free((*tbl)->fname);
    free((*tbl)->ks);
    free((*tbl));
}

void load(table* tbl)
{
    fseek(tbl->ftbl,sizeof(int),SEEK_SET);
    int i = 0;
    keyspace* ptr = tbl->ks;
    while(i<tbl->msize)
    {
        fread(&ptr->busy, sizeof(int), 1, tbl->ftbl);
        fread(&ptr->key, sizeof(int), 1, tbl->ftbl);
        fread(&ptr->release, sizeof(int), 1, tbl->ftbl);
        fread(&ptr->offset, sizeof(int), 1, tbl->ftbl);
        ++i;
        ++ptr;
    }
}
