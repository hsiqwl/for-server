#ifndef DIALOG_H
#define DIALOG_H
#include "table.h"
#include "defines.h"
int dialog(const char* msgs[], int len);
int d_add(table* tbl);
int d_delete(table* tbl);
int d_find(table* tbl);
int d_show(table* tbl);
int d_range(table* tbl);
int d_reorganize(table* tbl);
int d_read(table* tbl);
#endif
