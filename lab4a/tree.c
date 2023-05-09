#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
Tree* search(Tree* root, char* key)
{
    Tree* ptr = root;
    while(ptr!=NULL && strcmp(key,ptr->key)!=0)
    {
        int cmp = strcmp(key,ptr->key);
        if(cmp<0)
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
    }
    return ptr;
}

Tree* special_search(Tree* root, char* key)
{
    Tree* ptr = root;
    if(root == NULL)
    {
        return NULL;
    }
    Tree* last_bigger = NULL;
    while(ptr!=NULL)
    {
        int cmp = strcmp(ptr->key, key);
        if(cmp>0)
        {
            if(last_bigger==NULL || (strcmp(last_bigger->key, ptr->key)>0))
            {
                last_bigger = ptr;
            }
            ptr = ptr->left;
        }
        else if (cmp<0)
        {
            ptr = ptr->right;
        }
        else
        {
            last_bigger = ptr;
            break;
        }
    }
    return last_bigger;
}

Tree* get_min(Tree* root)
{
    Tree* ptr = root;
    while(ptr->left!=NULL)
    {
        ptr = ptr->left;
    }
    return ptr;
}

Tree* get_max(Tree* root)
{
    Tree* ptr = root;
    while(ptr->right!=NULL)
    {
        ptr = ptr->right;
    }
    return ptr;
}

void insert(Tree** root, Tree* node)
{
    if(*root == NULL)
    {
        node->release = 1;
        *root = node;
        return;
    }
    Tree* ptr = (*root);
    while(ptr!=NULL) {
        if (strcmp(node->key, ptr->key) > 0) {
            if (ptr->right != NULL){
                ptr = ptr->right;
            } else {
                ptr->right = node;
                node->next = ptr->next;
                if (ptr->next != NULL) {
                    ptr->next->prev = node;
                }
                ptr->next = node;
                node->prev = ptr;
                node->release = 1;
                break;
            }
        } else if (strcmp(node->key, ptr->key) < 0) {
            if (ptr->left != NULL) {
                ptr = ptr->left;
            } else {
                ptr->left = node;
                node->next = ptr;
                node->prev = ptr->prev;
                if (ptr->prev != NULL) {
                    ptr->prev->next = node;
                }
                ptr->prev = node;
                node->release = 1;
                break;
            }
        } else {
            ptr->release++;
            break;
        }
    }
}

void direct_travers(Tree* root, void (*visit_root)(Tree**),const char* max_str) {
    Tree *ptr = get_min(root);
    int count = 0;
    while (ptr != NULL) {
        Tree *curr_root = ptr;
        ptr = ptr->next;
        if (*max_str == 0) {
            visit_root(&curr_root);
            count++;
        } else if (strcmp(curr_root->key, max_str) <= 0) {
            visit_root(&curr_root);
        } else {
            break;
        }
    }
    printf("%d\n", count);
}

void show_tree(Tree* root, int lvl)
{
    int i = lvl;
    if(root)
    {
        show_tree(root->right, lvl+1);
        while(i-- > 0)
        {
            printf("  ");
        }
        printf("%s\n", root->key);
        show_tree(root->left, lvl+1);
    }
}

Tree* find_parent(Tree* root, char* key, Tree** node)
{
    Tree* ptr = root;
    Tree* parent = NULL;
    while(ptr!=NULL && strcmp(key,ptr->key)!=0)
    {
        parent = ptr;
        int cmp = strcmp(key, ptr->key);
        if(cmp<0)
        {
            ptr = ptr->left;
        }
        else
        {
            ptr = ptr->right;
        }
    }
    *node = ptr;
    return parent;
}

int delete(Tree** root, char* key, int release) {
    Tree *node;
    Tree *parent = find_parent(*root, key, &node);
    if (node == NULL) {
        return 1;
    }
    if (node->left == NULL && node->right == NULL) {
        if (node == *root) {
            *root = NULL;
        } else {
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            if (parent->right == node) {
                parent->right = NULL;
            } else {
                parent->left = NULL;
            }
        }
    } else if (node->right == NULL || node->left == NULL) {
        if (node == *root) {
            if (node->prev == NULL) {
                *root = node->next;
            } else {
                *root = node->prev;
            }
        } else if (node->right != NULL) {
            if (parent->right == node) {
                parent->right = node->right;
            } else {
                parent->left = node->right;
            }
        } else {
            if (parent->left == node) {
                parent->left = node->left;
            } else {
                parent->right = node->left;
            }
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
    } else {
        Tree *start_of_chain = node->next;
        Tree *end_of_chain = start_of_chain;
        while (end_of_chain->next != NULL && strcmp(end_of_chain->next->key, start_of_chain->key) == 0) {
            end_of_chain = end_of_chain->next;
        }
        start_of_chain->left = node->left;
        node->left = NULL;
        if (node->right != end_of_chain) {
            Tree *end_right_ptr = end_of_chain->right;
            Tree *end_parent = end_of_chain;
            while (end_parent != NULL && end_parent->left != end_of_chain) {
                end_parent = end_parent->next;
            }
            end_parent->left = end_right_ptr;
            end_of_chain->right = node->right;
            node->right = NULL;
        }
        start_of_chain->prev = node->prev;
        if (node->prev != NULL) {
            node->prev->next = start_of_chain;
        }
        if (*root == node) {
            *root = end_of_chain;
        }
        if (parent != NULL && parent->right == node) {
            parent->right = end_of_chain;
        } else if (parent != NULL) {
            parent->left = end_of_chain;
        }
    }
    free(node->key);
    free(node->data);
    free(node);
    return 0;
}
