#include <stdlib.h>
#include "../deque.h"
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
int check_note(char* note)
{
	char* copy = (char*)malloc(strlen(note)+1);
	copy = strcpy(copy,note);
	char* buf = NULL;
	int buf_len = 0;
	int no_slash = 1;
	for(int i = strcspn(copy,"/") + 1;i<strlen(copy);++i)
	{
		if(copy[i]=='/' && buf==NULL)
		{
			free(copy);
			return 1;
		}
		else if(copy[i]=='/')
		{
			no_slash = 0;
		}
		else
		{
			buf = (char*)realloc(buf,buf_len+1);
			buf[buf_len] = copy[i];
			buf_len++;
		}
	}
	if(no_slash)
	{
		free(copy);
		free(buf);
		return 1;
	}
	buf = (char*)realloc(buf,buf_len+1);
	buf[buf_len]=0;
	buf_len++;
	for(int i = 0;i<strlen(buf);++i)
	{
		if(buf[i]>'9' || buf[i]<'0')
		{
			free(copy);
			free(buf);
			return 1;
		}
	}
	free(copy);
	free(buf);
	return 0;
}

char** parse_str(char* str, int* notes_count)
{
	char** notes = NULL;
	*notes_count = 0;
	char* ptr = strtok(str," ");
	while(ptr!=NULL)
	{
		if(!check_note(ptr))
		{
			notes = (char**)realloc(notes,(*notes_count+1)*sizeof(char*));
			notes[*notes_count] = ptr;
			(*notes_count)++;
		}
		ptr = strtok(NULL," ");
	}
	return notes;
}

patient make_client(char* str)
{
	patient client;
	char* id = NULL;
	int id_len = 0;
	if(*str == '*')
	{
		client.flag = 1;
	}
	else
	{
		client.flag = 0;
	}
	int time = 0;
	for(int i = client.flag;i<strcspn(str,"/");i++)
	{
		id = (char*)realloc(id, id_len+1);
		id_len++;
		id[id_len-1] = str[i];
	}
	id = (char*)realloc(id, id_len+1);
	id[id_len] = 0;
	int i = strcspn(str,"/");
	client.id = id;
	for(i = i + 1; i<strlen(str);i++)
	{
		if(str[i]=='/')
		{
			client.time_in = time;
			time = 0;
			continue;
		}
		else
		{
			time = time*10 + ((int)str[i] - 48);
		}
	}
	client.time_out = time;
	return client;
}

void delete_note(char** notes, int* notes_count, int index)
{
	for(int i = index; i < (*notes_count) - 1;i++)
	{
		notes[i] = notes[i+1];
	}
	(*notes_count)--;
}

patient find_curr(char** notes, int* notes_count, int curr_time)
{
	char** ptr = notes;
	for(int i = 0; i < *notes_count; ++i,++ptr)
	{
		patient client = make_client(*ptr);
		if(client.time_in == curr_time)
		{
			delete_note(notes, notes_count, i);
			return client;
		}
		free(client.id);
	}
	patient null = {0,0,0,NULL};
	return null;
}

int get_int(int* value)
{
	int n;
	do
	{
		printf("Enter max number of elements that will be used in vector mode: "); 
		n = scanf("%d",value);
		if(n==EOF)
		{
			return 1;
		}
		if(n==0 || *value<=0)
		{
			while(getchar()!='\n');
			printf("try again\n");
		}
	}
	while(n<=0);
	return 0;
}
