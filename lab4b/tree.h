#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdbool.h>
/*typedef enum COLOR
{
    RED = 0,
    BLACK = 1
}COLOR;*/
#define BLACK true
#define RED false

typedef struct Tree
{
    int key;
    char* value;
    struct Tree* right;
    struct Tree* left;
    bool color;
}tree;

tree* search(tree* root, int key);
tree* get_min(tree* root);
tree* get_max(tree* root);
tree* new_node(int key, char* value);
int is_red(tree* node);
tree* left_rotate(tree* node);
tree* right_rotate(tree* node);
void change_colors(tree* node);
tree* insert(tree* root, int key, char* value);
tree* lean_red_left(tree* node);
tree* lean_red_right(tree* node);
tree* delete_min(tree* node);
tree* delete_node(tree* root, int key);
void invert_traverse(tree* root, void (*visit_root)(tree**));
void show_tree(tree* root, int lvl);
void delete_tree(tree** root);
tree* special_search(tree* root, int key);
#endif