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

int get_index_of_min_unvisited(const int* dist,const int* visited, int len)
{
    int min = RAND_MAX;
    int index_of_min_unvisited = 0;
    for(int i = 0; i < len; i++) {
        if (!visited[i]) {
            min = dist[i];
            index_of_min_unvisited = i;
            break;
        }
    }
    for(int i = 0;i <len;i++)
    {
        if(visited[i]==0 && dist[i]<min){
            min = dist[i];
            index_of_min_unvisited = i;
        }
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

void init_for_dijkstra(int** dist, int** visited, int** prev_shortest, int len)
{
    *dist = (int*)malloc(len*sizeof(int));
    *visited = (int*)calloc(len,sizeof(int));
    *prev_shortest = (int*)malloc(len*sizeof(int));
    for(int i=0;i<len;i++)
    {
        *(*dist + i) = RAND_MAX;
        *(*prev_shortest + i) = i;
    }
}

int compare_dist(int first, int second){
    if(second == RAND_MAX) {
        return 0;
    } else if(first > second + 1) {
        return 1;
    }else{
        return 0;
    }
}

void clear_node(Node** node){
    free((*node)->point);
    free(*node);
}

void clear_adj_list(Node** node){
    Node* ptr = *node;
    while(ptr!=NULL) {
        Node *prev_node = ptr;
        ptr = ptr->next;
        clear_node(&prev_node);
        prev_node = NULL;
    }
}
