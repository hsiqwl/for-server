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
    int i ;
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

void init_for_dijkstra(int** dist, int** visited, int** prev_shortest,int** heap, int len)
{
    *heap = (int*)malloc(len*sizeof(int));
    *dist = (int*)malloc(len*sizeof(int));
    *visited = (int*)calloc(len,sizeof(int));
    *prev_shortest = (int*)malloc(len*sizeof(int));
    for(int i=0;i<len;i++)
    {
        *(*heap+i) = i;
        *(*dist + i) = INF;
        *(*prev_shortest + i) = i;
    }
}

void clear_adj_list(adj_list** head){
    adj_list *ptr = *head;
    while(ptr!=NULL){
        adj_list* next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

/*int check_entries(const Graph* graph){
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

void heap_swap(int a, int b, int* heap){
    int tmp = heap[a];
    heap[a] = heap[b];
    heap[b] = tmp;
}

void shift_up(int* heap, int pos, int* dist){
    while(pos>0 && dist[heap[pos]] < dist[heap[(pos-1)/2]]){
        heap_swap(pos, (pos - 1)/2, heap);
        pos = (pos - 1)/2;
    }
}

void shift_down(int* heap, int pos, int curr_size, int* dist){
    while(2*pos + 1 < curr_size){
        int left = 2*pos + 1;
        int right = 2*pos + 2;
        int min_child = left;
        if(right<curr_size && dist[heap[right]] < dist[heap[left]]){
            min_child = right;
        }
        if(dist[heap[pos]]<=dist[heap[min_child]]){
            return;
        }
        heap_swap(pos, min_child, heap);
        pos = min_child;
    }
}

void heap_insert(int* heap, int curr_size, int value,int* dist){
    heap[curr_size++] = value;
    shift_up(heap, curr_size - 1,dist);
}

int pop_min(int* heap, int curr_size, int* dist){
    if(curr_size<=0){
        return -1;
    }
    int min = heap[0];
    heap_swap(0,curr_size - 1, heap);
    curr_size--;
    shift_down(heap, 0, curr_size, dist);
    return min;
}