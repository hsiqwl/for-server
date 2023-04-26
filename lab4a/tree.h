#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef struct Tree
{
    struct Tree* right;
    struct Tree* left;
    char* data;
    char* key;
    struct Tree* next;
    struct Tree* prev;
}Tree;

Tree* search(Tree* root, char* value);
void insert(Tree** root, Tree* node);
void direct_travers(Tree* root, void (*visit_root)(Tree**));
int delete(Tree** root, char* key);
Tree* find_parent(Tree* root, char* key, Tree** node);
void make_graph(Tree* root, FILE** fd);
#endif
