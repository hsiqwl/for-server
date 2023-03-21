#include <stdlib.h>
#include "table_funcs.h"
#include "input.h"
#include <string.h>
#include "error.h"

table* create(int msize)
{
	table* new = (table*)malloc(sizeof(table));
	new->msize = msize;
	new->ks = (keyspace*)calloc(msize,sizeof(keyspace));
	new->csize = 0;
	return new;
}

item* search_by_key(table* tbl,char* key)
{
	keyspace* ptr = tbl->ks;
	if(ptr!=NULL)
	{
		for(int i = 0;i<tbl->csize;++i,++ptr)
		{
			if(ptr->key!=NULL && strcmp(ptr->key,key)==0 && ptr->busy==1)
			{
				return ptr->info;
			}
		}
	}
	return NULL;
}

int table_full(table* tbl)
{
	if(tbl->csize == tbl->msize)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int insert_by_key(char* key,char* value,table* tbl)
{
	if(table_full(tbl))
	{
		return NO_SPACE;
	}
	else
	{
		if(search_by_key(tbl,key)!=NULL)
		{
			return KEY_USED;
		}
		else
		{
			(tbl->ks+tbl->csize)->busy = 1;
			(tbl->ks+tbl->csize)->key = strdup(key);
			(tbl->ks+tbl->csize)->info = (item*)malloc(sizeof(item));
			(tbl->ks+tbl->csize)->info->value = strdup(value);
			(tbl->ks + tbl->csize)->info->ks_ptr = tbl->ks + tbl->csize;
			(tbl->csize)++;
			return OK; 
		}
	}
}

int delete_by_key(char* key, table* tbl)
{
	item* current_for_key = search_by_key(tbl,key);
	if(current_for_key!=NULL)
	{
		current_for_key->ks_ptr->busy = 0;
		return OK;
	}
	else
	{
		return NO_KEY;
	}
}

void reorganize(table* tbl)
{
	keyspace* ptr = tbl->ks;
	int count = 0;
	for(int i = 0;i<tbl->msize;++i,++ptr)
	{
		if(ptr->busy==0 && ptr->key!=NULL)
		{
			free(ptr->key);
			free(ptr->info->value);
			free(ptr->info);
			for(int j = i;j<tbl->msize - 1;++j,++ptr)
			{
				*(ptr) = *(ptr + 1);
			}
			(tbl->ks + tbl->msize - 1)->key = NULL;
			(tbl->ks + tbl->msize - 1)->info = NULL;
			count++; 
			i--;
		}
		ptr = tbl->ks + i;
	}
	tbl->csize = tbl->csize - count;
}

void print_table(const table* tbl)
{
	if(tbl->csize == 0)
	{
		printf("table is empty\n");
	}
	keyspace* ptr = tbl->ks;
	for(int i = 0;i<tbl->csize;++i,++ptr)
	{
		printf("key:%s -> value:",ptr->key);
		if(ptr->busy)
		{
			printf("%s\n",ptr->info->value);
		}
		else
		{
			printf("no value\n");
		}
	}
}

int delete_by_range(char* start,char* end,table* tbl)
{
	keyspace* ptr = tbl->ks;
	for(int i = 0;i<tbl->csize;++i,++ptr)
	{
		if(strcmp(ptr->key,start)>=0 && strcmp(ptr->key,end)<=0)
		{
			delete_by_key(ptr->key,tbl);
		}
	}
	return OK;
}

void read_from_file(FILE* fd,table* tbl)
{
	int size;
    fseek(fd, SEEK_END, SEEK_SET);
    size = ftell(fd);
    fseek(fd,0,SEEK_SET);
    while(!feof(fd))
    {
        char* string = malloc(size+1);
        fgets(string,size,fd);
        char* key = strtok(string," ");
        char* value = strtok(NULL," ");
        insert_by_key(key,value,tbl);
        free(string);
        free(key);
        free(value);
    }
} 

void delete_table(table** tbl)
{
	keyspace* ptr = (*tbl)->ks;
	for(int i = 0;i<(*tbl)->msize;++i,++ptr)
	{
		if(ptr->key!=NULL)
		{
			free(ptr->info->value);
			free(ptr->info);
			free(ptr->key);
		}
	}
	free((*tbl)->ks);
	free((*tbl));
}
