#ifndef DIALOG_H
#define DIALOG_H
#include "table.h"
#include "consts.h"
int dialog(const char* msgs[], int len);
int d_add(table* tbl);
int d_delete(table* tbl);
int d_find(table* tbl);
int d_show(table* tbl);
table* d_load();
void d_save(table* tbl);
#endif
