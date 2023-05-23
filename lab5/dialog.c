#include "dialog.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "consts.h"

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
        scanf("%d", &command);
        printf("\n");
    }while(command<0 || command>=len);
    return command;
}


void insert_node(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y):");
    scanf("%d %d", &x,&y);
    Point* point = (Point*)malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    printf("Enter 0, 1 or 2 to define node type: BASIC, ENTRY, EXIT:");
    int node_type;
    scanf("%d",&node_type);
    Node* new = new_node(point, node_type, graph->nodes_count);
    if(add_node(graph, new)){
        printf("there is such node already\n");
        free(new->point);
        free(new);
    }else{
        printf("ok\n");
    }
}

void insert_link(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of first node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    int src_index = get_node_number(graph, point);
    printf("enter coordinates(x,y) of second node:");
    scanf("%d %d", &x, &y);
    point->x = x;
    point->y = y;
    int dest_index = get_node_number(graph, point);
    free(point);
    if(add_link(graph, src_index, dest_index)){
        printf("cannot add a link\n");
    }else{
        printf("ok\n");
    }
}

void remove_link(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of first node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    int src_index = get_node_number(graph, point);
    printf("enter coordinates(x,y) of second node:");
    scanf("%d %d", &x, &y);
    point->x = x;
    point->y = y;
    int dest_index = get_node_number(graph, point);
    if(delete_link(graph, src_index, dest_index)){
        printf("no such node or no link between nodes");
    }else{
        printf("ok\n");
    }
}

void remove_node(Graph* graph) {
    int x, y;
    printf("enter coordinates(x,y) of node:");
    scanf("%d %d", &x, &y);
    Point *point = new_point(x, y);
    int node_index = get_node_number(graph, point);
    free(point);
    if(delete_node(graph, node_index)){
       printf("no such node\n");
    }else{
        printf("ok\n");
    }
}

void show_graph(Graph* graph) {
    Node **ptr = graph->nodes;
    for (int i = 0; i < graph->nodes_count; i++, ++ptr) {
        adj_list *node = (*ptr)->head;
        if ((*ptr)->type == BASIC) {
            printf("BASIC");
        } else if ((*ptr)->type == ENTRY) {
            printf("ENTRY");
        } else {
            printf("EXIT");
        }
        printf(" %d ", (*ptr)->node_index);
        printf("(%d,%d)-", (*ptr)->point->x, (*ptr)->point->y);
        while (node != NULL) {
            printf("(%d,%d)-", (*(graph->nodes + node->node_index))->point->x, (*(graph->nodes + node->node_index))->point->y);
            node = node->next;
        }
        printf("\n");
    }
}

void find_shortest_path(Graph* graph) {
    int x, y;
    printf("enter coordinates(x,y) of starting node:");
    scanf("%d %d", &x, &y);
    Point *point = new_point(x, y);
    int start_index = get_node_number(graph, point);
    printf("enter coordinates(x,y) of destination node:");
    scanf("%d %d", &x, &y);
    point->x = x;
    point->y = y;
    int dest_index = get_node_number(graph, point);
    free(point);
    if(start_index == dest_index){
        print_node(*(graph->nodes + start_index));
    }else{
        int *pred = shortest_path_from_this_node(graph, start_index);
        if(pred[dest_index] == dest_index)
        {
            printf("there is no path between these two nodes\n");
        }else{
            while(dest_index!=start_index){
                print_node(*(graph->nodes + dest_index));
                printf(" ");
                dest_index = pred[dest_index];
            }
            print_node(*(graph->nodes+start_index));
            printf("\n");
        }
        free(pred);
    }
}

void check_if_reachable(Graph* graph) {
    int x, y;
    printf("enter coordinates(x,y) of starting node:");
    scanf("%d %d", &x, &y);
    Point *point = new_point(x, y);
    int start_index = get_node_number(graph, point);
    printf("enter coordinates(x,y) of destination node:");
    scanf("%d %d", &x, &y);
    point->x = x;
    point->y = y;
    int dest_index = get_node_number(graph, point);
    free(point);
    if(start_index == dest_index){
        printf("destination node is reachable from starting node\n");
    }else{
        int result = breadth_first_search(graph, start_index, dest_index);
        if(result){
            printf("destination node is reachable from starting node\n");
        }else{
            printf("destination node is not reachable from starting node\n");
        }
    }
}

void make_skeleton(Graph* graph){
    Graph* new = skeleton(graph);
    show_graph(new);
    delete_graph(&new);
}

