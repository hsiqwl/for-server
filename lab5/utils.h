#ifndef UTILS_H
#define UTILS_H
#include "graph.h"

Point* new_point(int x, int y);
int get_node_number(Graph* graph, Point* node_point);
int get_index_of_min_unvisited(Graph* graph, Node* node, const int* dist, const int* visited);
void print_node(Node* node);
#endif