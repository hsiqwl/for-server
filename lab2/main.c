#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "library/deque.h"
#include "library/funcs.h"

int main()
{
	char* str;
	int len;
	do
	{
		int n = get_int(&len);
		if(n)
		{
			str = NULL;
			continue;
		}
		str = readline("input notes:");
		if(str==NULL || *str==0)
		{
			continue;
		}
		int notes_count;
		char** notes = parse_str(str,&notes_count);
		if(notes==NULL)
		{
			return 0;
		}
		int abs_time = 0;
		deque* dq = create_dq(len);
		patient current = {0,1,0,NULL};
		do
		{
			current.time_out--;
			abs_time++;
			patient next = find_curr(notes,&notes_count,abs_time);
			int flag = 0;
			while(next.id!=NULL)
			{
				if(!add_newcomer(dq,&next,&flag))
				{
					printf("cannot add patient '%s'\n", next.id);
					free(next.id);
				}
				next = find_curr(notes,&notes_count,abs_time);
			}
			change_current(dq,&current,&flag);
			if(flag)
			{
				status(dq, current, abs_time);
			}
		}while(notes_count>0 || current.time_out>0);
		free_dq(dq);
		free(str);
		free(notes);
	}while(str!=NULL);
	return 0;
}
