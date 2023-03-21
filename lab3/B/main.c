#include "table.h"
#include "input.h"
#include "dialog.h"
#include "table_funcs.h"
int main()
{
	int (*fptr[])(table*) = {NULL,d_add,d_delete,d_find,d_show,d_range,d_reorganize,d_read};
	table* tbl = d_load();
    if(tbl == NULL)
    {
        printf("end\n");
        return 0;
    }
	int command;
	while((command = dialog(msgs,Nmsgs)))
	{
		if(fptr[command](tbl))
		{
			break;
		}
	}
	printf("end\n");
    d_save(tbl);
	delete_table(&tbl);
	return 0;
}
