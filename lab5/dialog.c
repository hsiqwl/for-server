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
    Node* src = find_node_by_points(graph, point);
    if(src==NULL) {
        printf("no such node in graph\n");
    } else {
        printf("enter coordinates(x,y) of first node:");
        scanf("%d %d", &x, &y);
        point->x = x;
        point->y = y;
        Node *dest_in_arr = find_node_by_points(graph, point);
        if (dest_in_arr == NULL) {
            printf("no such node in graph\n");
        } else {
            Node* dest = new_node(point, dest_in_arr->type);
            add_link(src,dest);
        }
    }
}

void remove_link(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of fisrt node:");
    scanf("%d %d", &x,&y);
    Point* point = new_point(x,y);
    Node* src = find_node_by_points(graph, point);
    if(src==NULL) {
        printf("no such node in graph\n");
    }else {
        printf("enter coordinates(x,y) of second node:");
        scanf("%d %d", &x, &y);
        point->x = x;
        point->y = y;
        Node *dest = find_node_by_points(graph, point);
        if(dest == NULL) {
            printf("no such node in graph\n");
        }else {
            delete_link(src, dest->point);
        }
    }
}

void remove_node(Graph* graph)
{
    int x, y;
    printf("enter coordinates(x,y) of fisrt node:");
    scanf("%d %d", &x,&y);
    Point* point = (Point*)malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    Node* node = find_node_by_points(graph, point);
    delete_node(graph, node);
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