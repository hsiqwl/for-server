#include "dialog.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
void insert_node(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y):");
    scanf("%d-%d", &x,&y);
    Point* point = (Point*)malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    printf("Enter 0, 1 or 2 to define node type: BASIC, ENTRY, EXIT:");
    int node_type;
    scanf("%d",&node_type);
    Node* new = new_node(point, node_type);
    add_node(graph, new);
}

void insert_link(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of first node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    int src_index = get_node_number(graph, point);
    if(src_index == -1) {
        printf("no such node in graph\n");
    } else {
        printf("enter coordinates(x,y) of first node:");
        scanf("%d %d", &x, &y);
        point->x = x;
        point->y = y;
        int dest_index = get_node_number(graph, point);
        if (dest_index == -1) {
            printf("no such node in graph\n");
        } else {
            Node* dest = new_node(point, (*(graph->nodes + dest_index))->type);
            add_link(*(graph->nodes + src_index),dest);
        }
    }
}

void remove_link(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of fisrt node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    int src_index = get_node_number(graph, point);
    if(src_index == -1) {
        printf("no such node in graph\n");
    }else {
        printf("enter coordinates(x,y) of second node:");
        scanf("%d %d", &x, &y);
        point->x = x;
        point->y = y;
        int dest_index = get_node_number(graph, point);
        if(dest_index == -1) {
            printf("no such node in graph\n");
        }else {
            delete_link(*(graph->nodes + src_index), (*(graph->nodes + src_index))->point);
        }
    }
}

void remove_node(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of fisrt node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    int node_index = get_node_number(graph, point);
    delete_node(graph,*(graph->nodes + node_index));
}

void show_graph(Graph* graph) {
    Node **ptr = graph->nodes;
    for (int i = 0; i < graph->nodes_count; i++, ++ptr) {
        Node *node = *ptr;
        if (node->type == BASIC) {
            printf("BASIC");
        } else if (node->type == ENTRY) {
            printf("ENTRY");
        } else {
            printf("EXIT");
        }
        while (node != NULL) {
            printf("(%d,%d)-", node->point->x, node->point->y);
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
    if (start_index == -1) {
        printf("no such node in graph\n");
    } else {
        printf("enter coordinates(x,y) of destination node:");
        scanf("%d %d", &x, &y);
        point->x = x;
        point->y = y;
        int dest_index = get_node_number(graph, point);
        if (dest_index == -1) {
            printf("no such node in graph\n");
        } else {
            int *prev_shortest = shortest_path_from_this_node(graph, *(graph->nodes + start_index));
            int curr_index = dest_index;
            while (curr_index != start_index) {
                print_node(*(graph->nodes + curr_index));
                curr_index = prev_shortest[curr_index];
            }
            print_node(*(graph->nodes + curr_index));
        }
    }
}