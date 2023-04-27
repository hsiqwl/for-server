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
    int release;
}Tree;

Tree* search(Tree* root, char* key, int release);
Tree* get_min(Tree* root);
Tree* get_max(Tree* root);
Tree* special_search(Tree* root, char* key, int release);
void insert(Tree** root, Tree* node);
void direct_travers(Tree* root, void (*visit_root)(Tree**), const char* max_str);
int delete(Tree** root, char* key, int release);
Tree* find_parent(Tree* root, char* key, Tree** node, int release);
void make_graph(Tree* root, FILE** fd);
#endif
