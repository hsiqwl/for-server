#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
tree* search(tree* root, int key) {
    tree *ptr = root;
    while (ptr != NULL && ptr->key != key) {
        if (ptr->key > key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return ptr;
}

tree* get_min(tree* root) {
    tree *ptr = root;
    while (ptr->left != NULL) {
        ptr = ptr->left;
    }
    return ptr;
}

tree* get_max(tree* root) {
    tree *ptr = root;
    while (ptr->right != NULL) {
        ptr = ptr->right;
    }
    return ptr;
}

tree* new_node(int key, char* value) {
    tree *new_node = (tree *) malloc(sizeof(tree));
    new_node->key = key;
    new_node->value = strdup(value);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->color = RED;
    return new_node;
}

int is_red(tree* node) {
    if (node == NULL || node->color == BLACK) {
        return 0;
    } else {
        return 1;
    }
}

tree* left_rotate(tree* node) {
    tree *switched = node->right;
    node->right = switched->left;
    switched->left = node;
    switched->color = node->color;
    node->color = RED;
    return switched;
}

tree* right_rotate(tree* node) {
    tree *switched = node->left;
    node->left = switched->right;
    switched->right = node;
    switched->color = node->color;
    node->color = RED;
    return switched;
}

void change_colors(tree* node) {
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

tree* rotations(tree* root)
{
    if (is_red(root->right)) {
        root = left_rotate(root);
    }
    if (is_red(root->left) && is_red(root->left->left)) {
        root = right_rotate(root);
    }
    if (is_red(root->left) && is_red(root->right)) {
        change_colors(root);
    }
    return root;
}

tree* insert(tree* root, int key, char* value) {
    if (root == NULL) {
        return new_node(key, value);
    }
    if (key > root->key) {
        root->right = insert(root->right, key, value);
    } else if (key < root->key) {
        root->left = insert(root->left, key, value);
    } else {
        char *buf = root->value;
        root->value = strdup(value);
        free(buf);
    }
    return rotations(root);
}

tree* lean_red_left(tree* node) {
    change_colors(node);
    if (is_red(node->right->left)) {
        node->right = right_rotate(node->right);
        node = left_rotate(node);
        change_colors(node);
    }
    return node;
}

tree* lean_red_right(tree* node) {
    change_colors(node);
    if (is_red(node->right->right)) {
        node = right_rotate(node);
        change_colors(node);
    }
    return node;
}

tree* delete_min(tree* node) {
    if (node->left == NULL){
        free(node->value);
        free(node);
        return NULL;
    }
    if (!is_red(node->left) && !is_red(node->left->left)) {
        node = lean_red_left(node);
    }
    node->left = delete_min(node->left);
    return rotations(node);
}

tree* delete(tree* root, int key) {
    if (key < root->key) {
        if (!is_red(root->left) && !is_red(root->left->left)) {
            root = lean_red_left(root);
        }
        root->left = delete(root->left, key);
    } else {
        if (is_red(root->left)) {
            root = right_rotate(root);
        }
        if (key == root->key && root->right == NULL) {
            free(root->value);
            free(root);
            return NULL;
        }
        if (!is_red(root->right) && !is_red(root->right->left)) {
            root = lean_red_right(root);
        }
        if (key == root->key) {
            tree *substitute = get_min(root->right);
            root->value = substitute->value;
            root->key = substitute->key;
            root->right = delete_min(root->right);
        } else {
            root->right = delete(root->right, key);
        }
    }
    return rotations(root);
}

void show_tree(tree* root, int lvl) {
    int i = lvl;
    if (root!=NULL) {
        show_tree(root->right, lvl + 1);
        while (i-- > 0) {
            printf(" ");
        }
        if (root != NULL) {
            printf("%d\n", root->key);
        }
        show_tree(root->left, lvl + 1);
    }
}

void invert_traverse(tree* root, void (*visit_root)(tree**)) {
    if (root != NULL) {
        tree* right = root->right;
        tree* left = root->left;
        invert_traverse(right, visit_root);
        visit_root(&root);
        invert_traverse(left, visit_root);
    }
}

tree* special_search(tree* root, int key) {
    tree *max = get_max(root);
    tree *min = get_min(root);
    if (abs(max->key - key) > abs(min->key - key)) {
        return max;
    } else {
        return min;
    }
}

void delete_tree(tree** root)
{
    invert_traverse(*root, delete_root);
}
