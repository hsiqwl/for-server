#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
Tree* search(Tree* root, char* key, int release)
{
    Tree* ptr = root;
    while(ptr!=NULL && (strcmp(key,ptr->key)!=0 || ptr->release != release))
    {
        if(strcmp(key,ptr->key)==0 && release!=ptr->release)
        {
            ptr = ptr->left;
        }
        if(strcmp(key,ptr->key)<0)
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

Tree* special_search(Tree* root, char* key, int release)
{
    Tree* ptr = root;
    if(root == NULL)
    {
        return NULL;
    }
    Tree* last_bigger = root;
    while(ptr!=NULL && ptr->release!=release)
    {
        int cmp = strcmp(ptr->key, key);
        if(cmp>0)
        {
            if(last_bigger==NULL || strcmp(last_bigger->key, ptr->key)>0)
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
            if(ptr->release!=release)
            {
                ptr = ptr->left;
            }
            else
            {
                last_bigger = ptr;
                break;
            }
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
    Tree* parent = NULL;
    while(ptr!=NULL)
    {
        if(strcmp(node->key,ptr->key)>0)
        {
            if(ptr->right!=NULL)
            {
                parent = ptr;
                ptr = ptr->right;
            }
            else
            {
                Tree* prev;
                if(ptr->left!=NULL)
                {
                    prev = get_max(ptr->left);
                    if(prev == ptr->left && ptr->left->left!=NULL)
                    {
                        prev = get_min(ptr->left);
                    }
                }
                else
                {
                    prev = ptr;
                }
                ptr->right = node;
                node->next = prev->next;
                if(prev->next!=NULL)
                {
                    prev->next->prev = node;
                }
                node->prev = prev;
                prev->next = node;
                node->release = 1;
                break;
            }
        }
        else if(strcmp(node->key, ptr->key)<0)
        {
            if(ptr->left!=NULL)
            {
                parent = ptr;
                ptr = ptr->left;
            }
            else
            {
                ptr->left = node;
                node->next = ptr->next;
                if(ptr->next!=NULL)
                {
                    ptr->next->prev = node;
                }
                node->prev = ptr;
                ptr->next = node;
                node->release = 1;
                break;
            }
        }
        else
        {
            if(parent == NULL)
            {
                node->left = ptr->left;
                node->release = ptr->release + 1;
                ptr->left = node;
                node->next = ptr->next;
                ptr->next->prev = node;
                node->prev = ptr;
                ptr->next = node;
            }
            else
            {
                if(parent->left == ptr)
                {
                    parent->left = node;
                    node->left = ptr;
                }
                else
                {
                    parent->right = node;
                    node->right = ptr;
                }
                node->release = ptr->release + 1;
                ptr->prev->next = node;
                node->prev = ptr->prev;
                node->next = ptr;
                ptr->prev = node;
            }
            break;
        }
    }
}

void direct_travers(Tree* root, void (*visit_root)(Tree**),const char* max_str)
{
    Tree* ptr = root;
    while(ptr!=NULL)
    {
        Tree* curr_root = ptr;
        ptr = ptr->next;
        if(*max_str==0)
        {
            visit_root(&curr_root);
        }
        else if(strcmp(curr_root->key, max_str)<=0)
        {
            visit_root(&curr_root);
        }
    }
}

void make_graph(Tree* root, FILE** fd)
{
    fprintf(*fd, "strict graph {\n");
    Tree* ptr = root;
    while(ptr!=NULL)
    {
        if(ptr->left!=NULL)
        {
            fprintf(*fd, "%s -- %s\n", ptr->key, ptr->left->key);
        }
        if(ptr->right!=NULL)
        {
            fprintf(*fd, "%s -- %s\n", ptr->key, ptr->right->key);
        }
        ptr = ptr->next;
    }
    fprintf(*fd, "}");
    fclose(*fd);
}

Tree* find_parent(Tree* root, char* key, Tree** node, int release)
{
    Tree* ptr = root;
    Tree* parent = NULL;
    while(ptr!=NULL && (strcmp(key,ptr->key)!=0 || ptr->release!=release))
    {
        parent = ptr;
        if(strcmp(key,ptr->key)==0 && release!=ptr->release)
        {
            ptr = ptr->left;
        }
        else if(strcmp(key,ptr->key)<0)
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

int delete(Tree** root, char* key, int release)
{
    Tree* node;
    Tree* parent = find_parent(*root, key, &node, release);
    if(node == NULL)
    {
        return 1;
    }
    if(node->left == NULL && node->right == NULL)
    {
        if(node==*root)
        {
            *root = NULL;
            goto clean;
        }
        node->prev->next = node->next;
        if(node->next!=NULL)
        {
            node->next->prev = node->prev;
        }
        if(parent->right == node)
        {
            parent->right = NULL;
        }
        else
        {
            parent->left = NULL;
        }
    }
    else if(node->right==NULL || node->left==NULL)
    {
        if(node==*root)
        {
            node->next->next = node->next->next->next;
            node->next->prev = NULL;
            *root = node->next;
            goto clean;
        }
        if(node->right!=NULL)
        {
            if(parent->right == node)
            {
                parent->right = node->right;
            }
            else
            {
                parent->left = node->right;
            }
        }
        else
        {
            if(parent->left == node)
            {
                parent->left = node->left;
            }
            else
            {
                parent->right = node->left;
            }
        }
        node->prev->next = node->next;
        if(node->next!=NULL)
        {
            node->next->prev = node->prev;
        }
    }
    else
    {
            Tree* substitute = get_min(node->right);
            if(substitute == node->right)
            {
                substitute->left = node->left;
            }
            else
            {
                substitute->prev->left = NULL;
                substitute->left = node->left;
                substitute->right = node->right;
            }
            if(parent!=NULL && parent->right == node)
            {
                parent->right = substitute;
            }
            else if(parent!=NULL)
            {
                parent->left = substitute;
            }
            else
            {
                *root = substitute;
            }
            substitute->prev->next = substitute->next;
            if(substitute->next!=NULL)
            {
                substitute->next->prev = substitute->prev;
            }
            substitute->prev = node->prev;
            substitute->next = node->next;
            if(node->prev!=NULL)
            {
                node->prev->next = substitute;
            }
            node->next->prev = substitute;
    }
    clean:
    free(node->key);
    free(node->data);
    free(node);
    return 0;
}