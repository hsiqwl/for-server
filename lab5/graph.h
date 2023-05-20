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

typedef struct Node
{
    Point* point;
    node_type type;
    int node_index;
    struct Node* next;
}Node;

typedef struct Graph
{
    Node** nodes;
    int nodes_count;
}Graph;

Graph* init();
Node* new_node(Point* point, node_type type, int node_index);
int add_link(Node* src, Node* dest);
int check_if_same_points(Point* first, Point* second);
int add_node(Graph* graph, Node* node);
int delete_link(Node* src, int node_index);
int delete_node(Graph* graph, Node* node);
int change_node(Graph* graph, Point* point, node_type new_type);
int* shortest_path_from_this_node(Graph* graph, Node* start);
int breadth_first_search(Graph* graph, Node* start,Node* dest);
void clear_graph(Graph** graph);
int* ford_bellman(Graph* graph, Node* node);
#endif