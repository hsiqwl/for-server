#ifndef UTILS_H
#define UTILS_H
#include "tree.h"
void print_root(Tree** root);
void clear_root(Tree** root);
int check_if_multiple(Tree* root);
Tree* find_needed_release(Tree* root, int release);
char* random_string_key();
char* random_string_data();
void to_lower_case(char* str);
#endif