#include "input.h"
#include "table_funcs.h"
#include "dialog.h"
#include <string.h>
#include "error.h"
#include <readline/readline.h>
int dialog(const char* msgs[], int len)
{
	char* err = "";
	int command;
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
	//printf("enter key->");
	char* key = readline("enter key->");
	if(key == NULL)
	{
		return 1;
	}
//	printf("enter value->");
	char* value = readline("enter value->");
	if(value == NULL)
	{
		return 1;
	}
	int msg = insert_by_key(key,value,tbl);
	printf("%s\n",errmsg[msg+1]);
	free(key);
	free(value);
	return 0;
}

int d_delete(table* tbl)
{
	//printf("enter key->");
	char* key = readline("enter key->");
	if(key==NULL)
	{
		return 1;
	}
	int msg = delete_by_key(key,tbl);
	free(key);
	printf("%s\n",errmsg[msg+1]);
	return 0;
}

int d_find(table* tbl)
{
//	printf("enter key->");
	char* key = readline("enter key->");
	if(key==NULL)
	{
		return 1;
	}
	item* current_for_key = search_by_key(tbl,key);
	free(key);
	if(current_for_key==NULL)
	{
		int msg = NO_KEY;
		printf("%s\n",errmsg[msg+1]);
	}
	else
	{
		int msg = OK;
		printf("%s\n",errmsg[msg+1]);
		printf("value is->%s\n", current_for_key->value);
	}
	return 0;
}

int d_show(table* tbl)
{
	print_table(tbl);
	return 0;
}

int d_range(table* tbl)
{
//	printf("enter start key->");
	char* start = readline("enter start key->");
	if(start == NULL)
	{
		return 1;
	}
	//printf("enter end key->");
	char* end = readline("enter end key->");
	if(end == NULL)
	{
		return 1;
	}
	if(strcmp(start,end)>0)
	{
		char* buf = start;
		start = end;
		end = buf;
	}
	int msg = delete_by_range(start,end,tbl);
	free(start);
	free(end);
	printf("%s\n",errmsg[msg+1]);
	return 0;
}

int d_reorganize(table* tbl)
{
	reorganize(tbl);
	int msg = OK;
	printf("%s\n",errmsg[msg+1]);
	return 0;
}

int d_read(table* tbl)
{
	//printf("enter file name->");
	char* file = readline("enter file name->");
	if(file==NULL)
	{
		return 1;
	}
	FILE* fd = fopen(file,"rb");
	if(fd==NULL)
	{
		int msg = NO_FILE;
		printf("%s\n",errmsg[msg+1]);
	}
	else
	{
		read_from_file(fd,tbl);
		fclose(fd);
	}
	free(file);
	return 0;
}

table* d_load()
{
    printf("enter name of the file you want to read from:");
    char* fname = readline("");
    FILE* fp = fopen(fname,"r+b");
    if(fp==NULL)
    {
        printf("ERROR\n");
        return NULL;
    }
    int msize;
    fread(&msize,sizeof(int),1,fp);
    printf("%d\n",msize);
    table* tbl = create(msize);
    printf("%d\n",tbl->msize);
    return tbl;
}