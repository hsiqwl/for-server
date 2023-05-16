#ifndef GRAPH_H
#define GRAPH_H
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
    struct Node* next;
}Node;

typedef struct Graph
{
    Node** nodes;
    int nodes_count;
}Graph;

Graph* init();
Node* new_node(Point* point, node_type type);
Node* find_node_by_points(Graph* graph, Point* point);
int add_link(Node* src, Node* dest);
int check_if_same_points(Point* first, Point* second);
int add_node(Graph* graph, Node* node);
int delete_link(Node* src, Point* dest_point);
int delete_node(Graph* graph, Node* node);
int change_node(Graph* graph, Point* point, node_type new_type);
#endif