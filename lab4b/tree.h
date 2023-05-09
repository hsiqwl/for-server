#ifndef TREE_H
#define TREE_H
#include <stdio.h>
typedef enum COLOR
{
    RED = 0,
    BLACK = 1
}COLOR;

typedef struct Tree
{
    int key;
    char* value;
    struct Tree* parent;
    struct Tree* right;
    struct Tree* left;
    COLOR color;
}tree;

extern tree NULLED;
extern tree* NIL;

tree* search(tree* root, int key);
tree* get_min(tree* root);
tree* get_max(tree* root);
tree* new_node(int key, char* value, tree* parent);
int is_red(tree* node);
tree* left_rotate(tree* node);
tree* right_rotate(tree* node);
void change_colors(tree* node);
tree* insert(tree* root, int key, char* value, tree* parent);
tree* lean_red_left(tree* node);
tree* lean_red_right(tree* node);
tree* delete_min(tree* node);
tree* delete(tree* root, int key);
void invert_traverse(tree* root, void (*visit_root)(tree**));
void show_tree(tree* root, int lvl);
void make_image(tree* root);
void delete_tree(tree** root);
#endif