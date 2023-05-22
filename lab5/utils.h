#ifndef UTILS_H
#define UTILS_H
#include "graph.h"

Point* new_point(int x, int y);
int check_if_near(Point* src, Point* dest);
int check_if_same_points(Point* first, Point* second);
int get_node_number(Graph* graph, Point* node_point);
int get_index_of_min_unvisited(const int* dist, const int* visited, int len);
void print_node(Node* node);
void init_for_dijkstra(int** dist, int** visited, int** prev_shortest, int len);
void clear_node(Node** node);
void clear_adj_list(Node** node);
int check_entries(const Graph* graph);
int check_exits(const Graph* graph);
#endif