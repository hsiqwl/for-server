#ifndef UTILS_H
#define UTILS_H
#include "graph.h"

Point* new_point(int x, int y);
int check_if_near(Point* src, Point* dest);
int check_if_same_points(Point* first, Point* second);
int get_node_number(Graph* graph, Point* node_point);
int get_index_of_min_unvisited(const int* dist, const int* visited, int len);
void print_node(Node* node);
void init_for_dijkstra(int** dist, int** visited, int** prev_shortest,int** heap, int len);
void clear_adj_list(adj_list** head);
void heap_swap(int a, int b, int* heap);
void shift_up(int* heap, int pos,int* dist);
void shift_down(int* heap, int pos, int curr_size, int* dist);
void heap_insert(int* heap, int curr_size, int value, int* dist);
int pop_min(int* heap, int curr_size, int* dist);
int check_entries(const Graph* graph);
int check_exits(const Graph* graph);
#endif