#include <stdlib.h>
#include "utils.h"
#include "graph.h"
#include <stdio.h>
#include <math.h>
Point* new_point(int x, int y)
{
    Point* new = (Point*)malloc(sizeof(Point));
    new->x = x;
    new->y = y;
    return new;
}

int get_node_number(Graph* graph, Point* node_point) {
    Node **ptr = graph->nodes;
    int i = -1;
    for (i = 0; i < graph->nodes_count; i++, ++ptr) {
        if (check_if_same_points((*ptr)->point, node_point)) {
            return i;
        }
    }
    return -1;
}

int check_if_near(Point* src, Point* dest) {
    double dist = sqrt(abs(src->x - dest->x) * abs(src->x - dest->x) + abs(src->y - dest->y) * abs(src->y - dest->y));
    if (dist != 1) {
        return 0;
    } else {
        return 1;
    }
}

int check_if_same_points(Point* first, Point* second) {
    return (first->x == second->x && first->y == second->y);
}

int get_index_of_min_unvisited(const int* dist,const int* visited, int len) {
    int flag = 1;
    int index_of_min_unvisited = 0;
    int min = INF;
    for (int i = 0; i < len; i++) {
        if (visited[i] == 0 && (flag == 1 || dist[i] < min)) {
            min = dist[i];
            index_of_min_unvisited = i;
            flag = 0;
        }
    }
    return index_of_min_unvisited;
}

void print_node(Node* node) {
    printf("(%d,%d)", node->point->x, node->point->y);
    if (node->type == BASIC) {
        printf("BASIC");
    } else if (node->type == ENTRY) {
        printf("ENTRY");
    } else {
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
        *(*dist + i) = INF;
        *(*prev_shortest + i) = i;
    }
}

/*void clear_node(Node** node){
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

int check_entries(const Graph* graph){
    Node** ptr = graph->nodes;
    for(int i=0;i<graph->nodes_count;++i,++ptr){
        if((*ptr)->type == ENTRY && (*ptr)->next==NULL){
            return 0;
        }
    }
    return 1;
}

int check_exits(const Graph* graph){
    Node** ptr = graph->nodes;
    for(int i=0;i<graph->nodes_count;++i,++ptr) {
        if((*ptr)->type != EXIT){
            continue;
        }else {
            Node** new_ptr = graph->nodes;
            int flag = 1;
            for(int j = 0; j <graph->nodes_count;++j,++new_ptr){
                Node* next_node = (*new_ptr)->next;
                while(next_node!=NULL){
                    if(next_node->node_index == i){
                        flag = 0;
                    }
                    next_node = next_node->next;
                }
            }
            if(flag){
                return 1;
            }else{
                return 0;
            }
        }
    }
}*/