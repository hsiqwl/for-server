#ifndef GRAPH_H
#define GRAPH_H
#define INF 1000000
typedef enum node_type{
    BASIC = 0,
    ENTRY = 1,
    EXIT = 2,
}node_type;

typedef struct Point
{
    int x;
    int y;
}Point;

typedef struct adj_list
{
    int node_index;
    struct adj_list* next;
}adj_list;

typedef struct Node
{
    Point* point;
    node_type type;
    int node_index;
    adj_list* head;
}Node;

typedef struct Graph
{
    Node** nodes;
    int nodes_count;
}Graph;

Graph* init();
Node* new_node(Point* point, node_type type, int node_index);
int add_link(Graph* graph ,int from, int to);
int check_if_same_points(Point* first, Point* second);
int add_node(Graph* graph, Node* node);
int delete_link(Graph* graph, int from, int to);
int delete_node(Graph* graph, int node_index);
int change_nod_type(Graph* graph, int node_index, node_type new_type);
int* shortest_path_from_this_node(Graph* graph, int start_index);
int breadth_first_search(Graph* graph, int start,int dest);
Graph* skeleton(Graph* graph);
void delete_graph(Graph** graph);
#endif
