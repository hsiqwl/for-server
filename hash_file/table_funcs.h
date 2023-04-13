#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H
#include "table.h"
table* create(int msize);
table* find(unsigned int key, int release, table* tbl);
int insert(unsigned int key, unsigned int value, table* tbl);
int delete(unsigned int key, int release, table* tbl);
void print(table* tbl);
void delete_table(table** tbl);
void load(table* tbl);
#endif