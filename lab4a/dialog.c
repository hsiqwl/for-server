#include "dialog.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "input.h"
#include "tree.h"
#include "consts.h"
#include "utils.h"
#include <readline/readline.h>
int dialog(const char* msgs[], int len)
{
    char* err = "";
    int command;
    int n;
    do
    {
        printf("%s\n",err);
        err = "ERROR OCCURED,TRY AGAIN";
        for(int i = 0;i<len;++i)
        {
            printf("%s\n",msgs[i]);
        }
        printf("Please make your choice->");
        n = get_int(&command);
        printf("\n");
        if(n)
        {
            command = 0;
        }
    }while(command<0 || command>=len);
    return command;
}

int tree_insert(Tree** root)
{
    char* key;
    char* data;
    key = readline("enter key:");
    data = readline("enter data:");
    if(key==NULL || data==NULL)
    {
        free(key);
        free(data);
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    Tree* node = (Tree*)malloc(sizeof(Tree));
    node->key = strdup(key);
    node->data = strdup(data);
    node->left = NULL;
    node->right = NULL;
    node->next = NULL;
    node->prev = NULL;
    insert(root, node);
    free(key);
    free(data);
    printf("%s\n", errmsg[OK]);
    return 0;
}

int show(Tree** root)
{
    show_tree(*root, 0);
    return 0;
}

int tree_search(Tree** root)
{
    char* key;
    key = readline("enter key:");
    if(key==NULL)
    {
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    int release;
    printf("enter release number:");
    if(get_int(&release))
    {
        free(key);
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    else
    {
        Tree* result = search(*root, key);
        if(result == NULL)
        {
            free(key);
            printf("%s\n" , errmsg[NO_KEY]);
            return 0;
        }
        else
        {
            printf("%s -- %s -- %d\n", result->key,result->data,result->release);
            free(key);
            printf("%s\n" , errmsg[OK]);
            return 0;
        }
    }
}

int tree_special_search(Tree** root)
{
    char* key = readline("enter key:");
    if(key == NULL)
    {
        printf("%s\n", errmsg[BAD_INPUT]);
    }
    else
    {
        Tree* result = special_search(*root, key);
        free(key);
        if(result == NULL)
        {
            printf("%s\n", errmsg[NO_KEY]);
            return 0;
        }
        else
        {
            if(!check_if_multiple(result))
            {
                int release;
                printf("Looks like there are multiple choices. Please, enter release number:");
                if(get_int(&release))
                {
                    printf("%s\n" , errmsg[BAD_INPUT]);
                    return 0;
                }
                Tree* answer = find_needed_release(result, release);
                if(answer!=NULL)
                {
                    printf("%s -- %s -- %d\n", answer->key, answer->data, answer->release);
                    printf("%s\n", errmsg[OK]);
                }
                else
                {
                    printf("%s\n", errmsg[NO_KEY]);
                }
            }
            else
            {
                printf("%s -- %s -- %d\n", result->key, result->data, result->release);
                printf("%s\n", errmsg[OK]);
            }
            return 0;
        }
    }
}


int tree_delete(Tree** root)
{
    char* key;
    key = readline("enter key:");
    if(key==NULL)
    {
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    int release;
    printf("enter release number:");
    if(get_int(&release))
    {
        free(key);
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    else
    {
        int result = delete(root, key, release);
        free(key);
        if(result)
        {
            printf("%s\n" , errmsg[NO_KEY]);
        }
        printf("%s\n" , errmsg[OK]);
        return 0;
    }
}

int traverse(Tree** root)
{
    char* max_str;
    max_str = readline("enter max string to show or press ENTER to show all:");
    if(max_str==NULL)
    {
        printf("%s\n" , errmsg[BAD_INPUT]);
        return 0;
    }
    direct_travers(*root, print_root, max_str);
    free(max_str);
    printf("%s\n" , errmsg[OK]);
    return 0;
}

int free_tree(Tree** root)
{
    direct_travers(*root, clear_root,"");
    return 0;
}

int make_image(Tree** root)
{
    if(root==NULL)
    {
        printf("%s\n" , errmsg[EMPTY]);
        return 0;
    }
    else
    {
        FILE* fd = fopen("tree.dot", "w");
        fprintf(fd, "strict graph {\n");
        Tree* ptr = get_min(*root);
        while(ptr!=NULL)
        {
            if(ptr->left!=NULL)
            {
                fprintf(fd, "%s -- %s\n", ptr->key, ptr->left->key);
            }
            if(ptr->right!=NULL)
            {
                fprintf(fd, "%s -- %s\n", ptr->key, ptr->right->key);
            }
            ptr = ptr->next;
        }
        fprintf(fd, "}");
        fclose(fd);
        system("dot -Tpng -O tree.dot");
        printf("Open 'tree.dot.png' to see your tree\n");
    }
    return 0;
}

int load(Tree** root)
{
    char* fname = readline("enter file name:");
    FILE* fd = fopen(fname, "r");
    while(!feof(fd))
    {
        char* word = get_str(fd);
        const char* DELIM = " ,.!?\t()'";
        if(*word == 0)
        {
            free(word);
            free(fname);
            fclose(fd);
            return 0;
        }
        char* ptr = strtok(word, DELIM);
        while(ptr!=NULL)
        {
            Tree* node = (Tree*)calloc(1,sizeof(Tree));
            to_lower_case(ptr);
            node->key = strdup(ptr);
            insert(root, node);
            ptr = strtok(NULL,DELIM);
        }
        free(word);
    }
    free(fname);
    fclose(fd);
    return 0;
}
