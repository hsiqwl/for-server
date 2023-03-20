#ifndef TABLE_H
#define TABLE_H
#include <stdbool.h>

typedef struct item
{
	char* value;
	struct keyspace* ks_ptr;
}item;

typedef struct keyspace
{
	bool busy;
	char* key;
	item* info;
}keyspace;
 
typedef struct table
{
	keyspace* ks;
	int msize;
	int csize;
}table;

#endif
