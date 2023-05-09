#ifndef DIALOG_H
#define DIALOG_H
#include "consts.h"
#include "tree.h"
int tree_insert(tree** root);
int tree_delete(tree** root);
int tree_search(tree** root);
int tree_special_search(tree** root);
int traverse(tree** root);
int make_image(tree** root);
int show(tree** root);
int free_tree(tree** root);
int dialog(const char* msgs[], int len);
#endif