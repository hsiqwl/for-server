#include "dialog.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "input.h"
#include "tree.h"
#include "consts.h"
#include "utils.h"
#include <readline/readline.h>
int dialog(const char* msgs[], int len) {
    char *err = "";
    int command;
    int n;
    do {
        printf("%s\n", err);
        err = "ERROR OCCURED,TRY AGAIN";
        for (int i = 0; i < len; ++i) {
            printf("%s\n", msgs[i]);
        }
        printf("Please make your choice->");
        n = get_int(&command);
        printf("\n");
        if (n) {
            command = 0;
        }
    } while (command < 0 || command >= len);
    return command;
}

int tree_insert(tree** root) {
    int key;
    printf("enter key:");
    int n = get_int(&key);
    char *value = readline("enter value:");
    if (value == NULL || n == 1) {
        printf("%s\n", errmsg[BAD_INPUT]);
    } else {
        *root = insert(*root, key, value);
        (*root)->color = BLACK;
        free(value);
    }
    return 0;
}

int show(tree** root) {
    if (*root == NULL) {
        printf("%s\n", errmsg[EMPTY]);
    } else {
        show_tree(*root, 0);
    }
    return 0;
}

int tree_search(tree** root) {
    int key;
    printf("enter key:");
    int n = get_int(&key);
    if (n) {
        printf("%s\n", errmsg[BAD_INPUT]);
    } else {
        tree *result = search(*root, key);
        if (result == NULL) {
            printf("%s\n", errmsg[NO_KEY]);
        } else {
            printf("%d -- %s\n", result->key, result->value);
            printf("%s\n", errmsg[OK]);
        }
    }
    return 0;
}

int tree_special_search(tree** root) {
    int key;
    printf("enter key:");
    int n = get_int(&key);
    if (n) {
        printf("%s\n", errmsg[BAD_INPUT]);
    } else {
        tree *result = special_search(*root, key);
        if (result == NULL) {
            printf("%s\n", errmsg[NO_KEY]);
        } else {
            printf("%d -- %s\n", result->key, result->value);
            printf("%s\n", errmsg[OK]);
        }
    }
    return 0;
}

int tree_delete(tree** root) {
    int key;
    printf("enter key:");
    int n = get_int(&key);
    if (n) {
        printf("%s\n", errmsg[BAD_INPUT]);
    } else {
        if(*root == NULL) {
            printf("%s\n", errmsg[NO_KEY]);
            return 0;
        }
        *root = delete(*root, key);
        (*root)->color = BLACK;
        printf("%s\n", errmsg[OK]);
    }
    return 0;
}

int traverse(tree** root) {
    if (*root == NULL) {
        printf("%s\n", errmsg[EMPTY]);
    } else {
        invert_traverse(*root, print_root);
    }
    return 0;
}

int free_tree(tree** root) {
    delete_tree(root);
    return 0;
}

int make_image(tree** root){
    FILE* fd = fopen("tree.dot", "w");
    fprintf(fd, "strict graph {\n");
    fclose(fd);
    invert_traverse(*root, graph);
    fd = fopen("tree.dot", "a");
    fprintf(fd, "}");
    fclose(fd);
    system("dot -Tpng -O tree.dot");
    return 0;
}
