#ifndef TABLE_H
#define TABLE_H
#include <stdbool.h>
#include <stdio.h>
typedef struct keyspace
{
	bool busy;
    char* key;
    int klen;
	int koffset;
    int voffset;
    int vlen;
}keyspace;
 
typedef struct table
{
	keyspace* ks;
	int msize;
	int csize;
    FILE* ftbl;
}table;

#endif

