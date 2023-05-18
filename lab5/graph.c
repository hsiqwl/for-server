#include "graph.h"
#include <stdlib.h>
#include <math.h>
#include "utils.h"
#include "queue.h"

Graph* init() {
    Graph *new = (Graph*)malloc(sizeof(Graph));
    new->nodes = NULL;
    new->nodes_count = 0;
    return new;
}

Node* new_node(Point* point, node_type type, int node_index) {
    Node *new = (Node *) malloc(sizeof(Node));
    new->point = point;
    new->type = type;
    new->next = NULL;
    new->node_index = node_index;
    return new;
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
    if (first->x == second->x && first->y == second->y) {
        return 1;
    } else {
        return 0;
    }
}

int add_node(Graph* graph, Node* node) {
    if (get_node_number(graph, node->point) != -1) {
        return 1;
    }
    graph->nodes_count += 1;
    graph->nodes = (Node**)realloc(graph->nodes, graph->nodes_count * sizeof(Node*));
    *(graph->nodes + graph->nodes_count - 1) = node;
    return 0;
}

int add_link(Node* src, Node* dest) {
    if(!check_if_near(src->point, dest->point)){
        return 1;
    }
    Node *ptr = src->next;
    while (ptr != NULL) {
        if (check_if_same_points(ptr->point, dest->point)) {
            return 1;
        }
        ptr = ptr->next;
    }
    dest->next = src->next;
    src->next = dest;
    return 0;
}

int delete_link(Node* src, Point* dest_point) {
    Node *ptr = src;
    while (ptr != NULL) {
        if (ptr->next!=NULL && check_if_same_points(ptr->next->point,dest_point)) {
            break;
        }
        ptr = ptr->next;
    }
    if (ptr != NULL) {
        Node *next = ptr->next->next;
        clear_node(&(ptr->next));
        ptr->next = next;
        return 0;
    } else {
        return 1;
    }
}

int delete_node(Graph* graph, Node* node){
    Node** ptr = graph->nodes;
    int pos = -1;
    for(int i = 0;i<graph->nodes_count;++i,++ptr) {
        if(*ptr == node) {
            pos = i;
            continue;
        }
        delete_link(*ptr, node->point);
    }
    if(pos == -1) {
        return 1;
    }else {
        ptr = graph->nodes + pos;
        clear_adj_list(&((*ptr)->next));
        clear_node(ptr);
        *ptr = NULL;
        for (int i = pos; i < graph->nodes_count - 1; i++, ++ptr) {
            *ptr = *(ptr + 1);
            (*ptr)->node_index -=1;
        }
        graph->nodes_count -= 1;
        graph->nodes = (Node **)realloc(graph->nodes, graph->nodes_count * sizeof(Node *));
        return 0;
    }
}

int change_node(Graph* graph, Point* point, node_type new_type) {
    int node_index = get_node_number(graph, point);
    if (node_index == -1) {
        return 1;
    }
    (*(graph->nodes + node_index))->type = new_type;
    return 0;
}


int* shortest_path_from_this_node(Graph* graph, Node* start)
{
    int *dist, *visited, *prev_shortest;
    init_for_dijkstra(&dist, &visited, &prev_shortest, graph->nodes_count);
    int curr_node = start->node_index;
    dist[curr_node] = 0;
    int number_of_visited = 0;
    while(number_of_visited<graph->nodes_count)
    {
        Node* ptr = *(graph->nodes + curr_node);
        ptr = ptr->next;
        while(ptr!=NULL)
        {
            int next_node = ptr->node_index;
            if(visited[next_node]==0 && (compare_dist(dist[next_node], dist[curr_node]))) {
                dist[next_node] = dist[curr_node] + 1;
                prev_shortest[next_node] = curr_node;
            }
            ptr = ptr->next;
        }
        visited[curr_node] = 1;
        number_of_visited++;
        curr_node = get_index_of_min_unvisited(dist, visited, graph->nodes_count);
    }
    return dist;
}

int breadth_first_search(Graph* graph, Node* start, Node* dest) {
    int *visited = (int *) calloc(graph->nodes_count, sizeof(int));
    queue *q = init_q();
    push(q, start->node_index);
    visited[start->node_index] = 1;
    while (!is_empty(q)) {
        int node_index = pop(q);
        Node *ptr = *(graph->nodes + node_index);
        ptr = ptr->next;
        while (ptr != NULL) {
            if (!visited[ptr->node_index]) {
                push(q, ptr->node_index);
                visited[ptr->node_index] = 1;
                if (*(graph->nodes + ptr->node_index) == dest) {
                    return 1;
                }
            }
            ptr = ptr->next;
        }
    }
    return 0;
}
