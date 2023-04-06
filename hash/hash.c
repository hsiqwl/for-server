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
    return (key * 43 - 1) % msize;
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


