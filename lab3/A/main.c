#include "table.h"
#include "input.h"
#include "dialog.h"
#include "table_funcs.h"
int main()
{
	int (*fptr[])(table*) = {NULL,d_add,d_delete,d_find,d_show,d_range,d_reorganize,d_read};
	printf("enter max size of table->");
	int msize;
	if(get_uint(&msize))
	{
		printf("end\n");
		return 0;
	}
	table* tbl = create(msize);
	int command;
	while((command = dialog(msgs,Nmsgs)))
	{
		if(fptr[command](tbl))
		{
			break;
		}
	}
	printf("end\n");
	delete_table(&tbl);
	return 0;
}
