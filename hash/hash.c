#include "hash.h"
#include "consts.h"
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
    return key % msize;
}

int get_hash_primary(unsigned int key, int msize)
{
    int ans;
    ans = primary[key%primary_size];
    if(get_nod(ans,msize)!=1)
    {
        ans-=1;
    }
    return ans;
}


