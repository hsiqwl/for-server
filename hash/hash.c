#include "hash.h"
#include "consts.h"
#include <math.h>
#include <stdlib.h>

int get_nod(int a, int b)
{
    while(a!=0 && b!=0)
    {
        if(a>b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return a+b;
}

int get_hash_easy(unsigned int key, int msize)
{
    unsigned int hash = key;
    hash += ~(hash << 16);
    hash ^=  (hash >>  5);
    hash +=  (hash <<  3);
    hash ^=  (hash >> 13);
    hash += ~(hash <<  9);
    hash ^=  (hash >> 17);
    return (hash % msize);
}

int get_hash_primary(unsigned int key, int msize)
{
    int ans;
    do
    {
        ans = primary[(rand() + key)%primary_size];
    }while(get_nod(ans,msize) != 1);
    return ans;
}


