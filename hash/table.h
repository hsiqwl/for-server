#ifndef TABLE_H
#define TABLE_H
#include <stdbool.h>
typedef struct Table
{
    int msize;
    struct keyspace* ks;
}table;

typedef struct keyspace
{
    int busy;
    unsigned int key;
    unsigned int release;
    struct item* info;
}keyspace;

typedef struct item
{
    unsigned int value;
}item;

#endif
