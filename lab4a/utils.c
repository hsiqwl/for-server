#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
void print_root(Tree** root)
{
    printf("%s -- %d\n",(*root)->key, (*root)->release);
}

void clear_root(Tree** root)
{
    if((*root)->key!=NULL)
    {
        free((*root)->key);
    }
    if((*root)->data!=NULL)
    {
        free((*root)->data);
    }
    free(*root);
}

int check_if_multiple(Tree* root)
{
    Tree* ptr = root;
    while(ptr!=NULL)
    {
        if(ptr->left!=NULL && strcmp(ptr->left->key,ptr->key)==0)
        {
            return 0;
        }
        ptr = ptr->left;
    }
    return 1;
}

Tree* find_needed_release(Tree* root, int release)
{
    Tree* ptr = root;
    char* key = ptr->key;
    while(ptr!=NULL && ptr->release != release && strcmp(ptr->key,key)==0)
    {
        if(ptr->release == release && strcmp(ptr->key,key)==0)
        {
            break;
        }
        ptr = ptr->left;
    }
    if(ptr->release == release)
    {
        return ptr;
    }
    return NULL;
}

char* random_string_key()
{
    char* string;
    srand(time(NULL));
    int len = rand()%6 + 1;
    string = (char*)calloc(len+1, sizeof(char));
    for(int i = 0; i<len;i++)
    {
        string[i] = (char)(65 + rand()%62);
    }
    return string;
}

char* random_string_data()
{
    char* string;
    srand(time(NULL));
    int len = rand()%5 + 1;
    string = (char*)calloc(len+1, sizeof(char));
    for(int i = 0; i<len;i++)
    {
        string[i] = (char)(65 + rand()%62);
    }
    return string;
}

void to_lower_case(char* str)
{
    for(int i = 0;i <strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
}