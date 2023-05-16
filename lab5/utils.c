#include <stdlib.h>
#include "utils.h"
#include "graph.h"
#include <stdio.h>
Point* new_point(int x, int y)
{
    Point* new = (Point*)malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}

int get_node_number(Graph* graph, Point* node_point)
{
    Node** ptr = graph->nodes;
    int i = -1;
    for(i = 0;i<graph->nodes_count;i++,++ptr)
    {
        if(check_if_same_points((*ptr)->point, node_point))
        {
            return i;
        }
    }
    return -1;
}

int get_index_of_min_unvisited(Graph* graph, Node* node,const int* dist,const int* visited)
{
    int min = RAND_MAX;
    int index_of_min_unvisited = 0;
    Node* ptr = node->next;
    while(ptr!=NULL)
    {
        int index = get_node_number(graph,ptr->point);
        if(visited[index]==0 && dist[index]<min)
        {
            min = dist[index];
            index_of_min_unvisited = index;
        }
        ptr = ptr->next;
    }
    return index_of_min_unvisited;
}

void print_node(Node* node){
    printf("(%d,%d)", node->point->x, node->point->y);
    if(node->type == BASIC)
    {
        printf("BASIC");
    }else if (node->type == ENTRY)
    {
        printf("ENTRY");
    }else{
        printf("EXIT");
    }
}
