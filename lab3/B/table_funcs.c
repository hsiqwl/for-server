#include <stdlib.h>
#include "table_funcs.h"
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

keyspace* search_by_key(table* tbl,char* key)
{
	keyspace* ptr = tbl->ks;
	if(ptr!=NULL)
	{
		for(int i = 0;i<tbl->csize;++i,++ptr)
		{
			if(ptr->key!=NULL && strcmp(ptr->key,key)==0 && ptr->busy==1)
			{
                return ptr;
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
            tbl->ftbl = fopen(tbl->fname,"r+b");
            fseek(tbl->ftbl,0,SEEK_END);
            keyspace* ptr = tbl->ks + tbl->csize;
            ptr->key = strdup(key);
            ptr->busy = 1;
            ptr->voffset = ftell(tbl->ftbl);
            ptr->vlen = strlen(value);
            fwrite(value,sizeof(char),ptr->vlen + 1 ,tbl->ftbl);
            fseek(tbl->ftbl,0,SEEK_END);
            ptr->koffset = ftell(tbl->ftbl);
            ptr->klen = strlen(key);
            fwrite(ptr->key,sizeof(char),ptr->klen + 1 ,tbl->ftbl);
            tbl->csize++;
            fclose(tbl->ftbl);
			return OK; 
		}
	}
}

int delete_by_key(char* key, table* tbl)
{
	keyspace* current_for_key = search_by_key(tbl,key);
	if(current_for_key!=NULL)
	{
		current_for_key->klen = 0;
        current_for_key->busy = 0;
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
	for(int i = 0;i<tbl->msize;++i,++ptr)
	{
		if(ptr->busy==0 && ptr->key!=NULL)
		{
			free(ptr->key);
            ptr->key = NULL;
			keyspace buf = *ptr;
            *ptr = *(tbl->ks + tbl->csize - 1);
            *(tbl->ks + tbl->csize - 1) = buf;
            tbl->csize--;
            --i;
            --ptr;
		}
	}
}

void print_table(table* tbl)
{
	if(tbl->csize == 0)
	{
		printf("table is empty\n");
	}
    else
    {
        keyspace *ptr = tbl->ks;
        tbl->ftbl = fopen(tbl->fname,"r+b");
        for (int i = 0; i < tbl->csize; ++i, ++ptr) {
            printf("key:%s -> value:", ptr->key);
            if (ptr->busy)
            {
                fseek(tbl->ftbl, ptr->voffset, SEEK_SET);
                char *value = (char *) malloc(ptr->vlen + 1);
                fread(value, sizeof(char), ptr->vlen + 1, tbl->ftbl);
                printf("%s\n", value);
                perror("ERROR MSG:");
                free(value);
            }
            else
            {
                printf("no value\n");
            }
        }
        fclose(tbl->ftbl);
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

void read_from_file(FILE* fd,table* tbl,int position)
{
    int size;
    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    fseek(fd,position,SEEK_SET);
    while(!feof(fd))
    {
        char* string = malloc(size+1);
        fgets(string,size,fd);
        if(strlen(string)!=0)
        {
            string[strlen(string) - 1] = 0;
        }
        char* key = strtok(string," ");
        char* value = strtok(NULL," ");
        if(key!=NULL && value!=NULL)
        {
            insert_by_key(key,value,tbl);
        }
        free(string);
    }
}
void load(table* tbl)
{
    fseek(tbl->ftbl,sizeof(int),SEEK_SET);
    int i = 0;
    keyspace* ptr = tbl->ks;
    while(i<tbl->msize)
    {
        fread(&(ptr->klen),sizeof(int),1,tbl->ftbl);
        fread(&(ptr->koffset),sizeof(int),1,tbl->ftbl);
        if(ptr->klen!=0)
        {
            int prev_pos = ftell(tbl->ftbl);
            fseek(tbl->ftbl,ptr->koffset,SEEK_SET);
            ptr->key = (char*)malloc(ptr->klen+1);
            fread(ptr->key,sizeof(char), ptr->klen+1,tbl->ftbl);
            fseek(tbl->ftbl,prev_pos,SEEK_SET);
            fread(&ptr->voffset,sizeof(int),1,tbl->ftbl);
            fread(&ptr->vlen,sizeof(int),1,tbl->ftbl);
            ptr->busy = 1;
            tbl->csize++;
        }
        else
        {
            fseek(tbl->ftbl,2*sizeof(int),SEEK_CUR);
        }
        i++;
        ++ptr;
    }
}
void delete_table(table** tbl)
{
	keyspace* ptr = (*tbl)->ks;
	for(int i = 0;i<(*tbl)->msize;++i,++ptr)
	{
		if(ptr->key!=NULL)
		{
			free(ptr->key);
		}
	}
	free((*tbl)->ks);
    free((*tbl)->fname);
	free((*tbl));
}

