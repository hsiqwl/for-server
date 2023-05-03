#ifndef DIALOG_H
#define DIALOG_H
#include "consts.h"
#include "tree.h"
int tree_insert(Tree** root);
int tree_delete(Tree** root);
int tree_search(Tree** root);
int tree_special_search(Tree** root);
int traverse(Tree** root);
int make_image(Tree** root);
int show(Tree** root);
int load(Tree** root);
int free_tree(Tree** root);
int dialog(const char* msgs[], int len);
#endif