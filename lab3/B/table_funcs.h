#ifndef TABLE_FUNCS_H
#define TABLE_FUNCS_H
#include "table.h"
#include <stdio.h>
table* create(int msize);
item* search_by_key(table* tbl,char* key);
int table_full(table* tbl);
int insert_by_key(char* key,char* value,table* tbl);
int delete_by_key(char* key,table* tbl);
int delete_by_range(char* start,char* end,table* tbl);
void print_table(const table* tbl);
void reorganize(table* tbl);
void read_from_file(FILE* fd,table* tbl);
void delete_table(table** tbl);
#endif
