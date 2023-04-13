#ifndef TABLE_H
#define TABLE_H
#include <stdlib.h>
#include <stdio.h>
typedef struct Table
{
    int msize;
    struct keyspace* ks;
    FILE* ftbl;
    char* fname;
}table;

typedef struct keyspace
{
    int busy;
    unsigned int key;
    unsigned int release;
    unsigned int offset;
}keyspace;

#endif
