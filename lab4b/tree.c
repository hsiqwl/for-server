#include "tree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"
tree NULLED = {0,NULL,NULL,NULL,NULL,BLACK};
tree* NIL = &NULLED;

tree* search(tree* root, int key) {
    tree *ptr = root;
    while (ptr != NIL && ptr->key != key) {
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
    while (ptr->left != NIL) {
        ptr = ptr->left;
    }
    return ptr;
}

tree* get_max(tree* root) {
    tree *ptr = root;
    while (ptr->right != NIL) {
        ptr = ptr->right;
    }
    return ptr;
}

tree* new_node(int key, char* value, tree* parent) {
    tree *new_node = (tree *) malloc(sizeof(tree));
    new_node->key = key;
    new_node->value = strdup(value);
    new_node->left = NIL;
    new_node->right = NIL;
    new_node->color = RED;
    new_node->parent = parent;
    return new_node;
}

int is_red(tree* node) {
    if (node->color == RED) {
        return 1;
    } else {
        return 0;
    }
}

tree* left_rotate(tree* node) {
    tree *parent = node->parent;
    tree *switched = node->right;
    node->right = switched->left;
    switched->left = node;
    switched->color = node->color;
    node->color = RED;
    node->parent = switched;
    switched->parent = parent;
    if (node->right != NIL) {
        node->right->parent = node;
    }
    return switched;
}

tree* right_rotate(tree* node) {
    tree *parent = node->parent;
    tree *switched = node->left;
    node->left = switched->right;
    switched->right = node;
    switched->color = node->color;
    node->color = RED;
    node->parent = switched;
    switched->parent = parent;
    if (node->left != NIL) {
        node->left->parent = node;
    }
    return switched;
}

void change_colors(tree* node) {
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

tree* rotations(tree* root)
{
    if (is_red(root->right) && !is_red(root->left)) {
        root = left_rotate(root);
    }
    if (is_red(root->left) && is_red(root->left->left)) {
        root = right_rotate(root);
    }
    return root;
}

tree* insert(tree* root, int key, char* value, tree* parent) {
    if (root == NIL) {
        return new_node(key, value, parent);
    }
    if (is_red(root->left) && is_red(root->right)) {
        change_colors(root);
    }
    if (key > root->key) {
        parent = root->right;
        root->right = insert(root->right, key, value, parent);
    } else if (key < root->key) {
        parent = root->left;
        root->left = insert(root->left, key, value, parent);
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
    if(node==NIL)
    {
        return NIL;
    }
    if (node->left == NIL) {
        free(node->value);
        free(node);
        return NIL;
    }
    if (!is_red(node->left) && !is_red(node->left->left)) {
        node = lean_red_left(node);
    }
    node->left = delete_min(node->left);
    return rotations(node);
}

tree* delete(tree* root, int key) {
    if(root == NIL)
    {
        return NIL;
    }
    if (key < root->key) {
        if (!is_red(root->left) && !is_red(root->left->left)) {
            root = lean_red_left(root);
        }
        root->left = delete(root->left, key);
    } else {
        if (is_red(root->left)) {
            root = right_rotate(root);
        }
        if (key == root->key && root->right == NIL) {
            free(root->value);
            free(root);
            return NIL;
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
    if (root) {
        show_tree(root->right, lvl + 1);
        while (i-- > 0) {
            printf("  ");
        }
        if (root != NIL) {
            printf("%d\n", root->key);
        }
        show_tree(root->left, lvl + 1);
    }
}

void invert_traverse(tree* root, void (*visit_root)(tree**)) {
    if (root != NIL) {
        invert_traverse(root->right, visit_root);
        visit_root(&root);
        invert_traverse(root->left, visit_root);
    }
}

void make_image(tree* root){
    FILE* fd = fopen("tree.dot", "w");
    fprintf(fd, "strict graph {\n");
    fclose(fd);
    invert_traverse(root, graph);
    fd = fopen("tree.dot", "a");
    fprintf(fd, "}");
    fclose(fd);
    system("dot -Tpng -O tree.dot");
}
