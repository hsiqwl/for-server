#ifndef DIALOG_H
#define DIALOG_H
#include "graph.h"

void insert_node(Graph* graph);
void insert_link(Graph* graph);
void remove_link(Graph* graph);
void remove_node(Graph* graph);
void show_graph(Graph* graph);
void find_shortest_path(Graph* graph);
void check_if_reachable(Graph* graph);
void create_skeleton(Graph* graph);
#endif