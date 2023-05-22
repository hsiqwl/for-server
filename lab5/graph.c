#include "graph.h"
#include <stdlib.h>
#include "utils.h"
#include "queue.h"
#include <stdio.h>
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
    new->head = NULL;
    new->node_index = node_index;
    return new;
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

int add_link(Graph* graph ,int from, int to) {
    if(from==-1 || to==-1 || !check_if_near((*(graph->nodes + from))->point, (*(graph->nodes + to))->point)){
        return 1;
    }
    adj_list* head = (*(graph->nodes + from))->head;
    while(head!=NULL){
        if(head->node_index == to){
            return 1;
        }
        head = head->next;
    }
    head = (*(graph->nodes + from))->head;
    adj_list* new = malloc(sizeof(adj_list));
    new->node_index = to;
    new->next = NULL;
    new->next = head;
    (*(graph->nodes + from))->head = new;
    return 0;
}

int delete_link(Graph* graph, int from, int to) {
    if (from == -1 || to == -1) {
        return 1;
    }
    adj_list *ptr = (*(graph->nodes + from))->head;
    if (ptr != NULL && ptr->node_index == to) {
        adj_list *next_after_to = ptr->next;
        free(ptr);
        (*(graph->nodes + from))->head = next_after_to;
        return 0;
    }
    while (ptr != NULL) {
        if (ptr->next != NULL && ptr->next->node_index == to) {
            break;
        }
        ptr = ptr->next;
    }
    if (ptr != NULL) {
        adj_list *next_after_to = ptr->next->next;
        free(ptr->next);
        ptr->next = next_after_to;
        return 0;
    } else {
        return 1;
    }
}

int delete_node(Graph* graph, int node_index) {
    if(node_index == -1){
        return 1;
    }
    Node **ptr = graph->nodes;
    for (int i = 0; i < graph->nodes_count; ++i, ++ptr) {
        delete_link(graph, (*ptr)->node_index, node_index);
    }
    ptr = graph->nodes + node_index;
    for(int i = node_index; i < graph->nodes_count - 1;++i,++ptr){
        *ptr = *(ptr + 1);
        (*ptr)->node_index -=1;
    }
    graph->nodes_count -=1;
    graph->nodes = (Node**)realloc(graph->nodes, graph->nodes_count*sizeof(Node*));
    ptr = graph->nodes;
    for(int i = 0; i < graph->nodes_count;++i,++ptr){
        adj_list* head = (*ptr)->head;
        while(head!=NULL){
            if(head->node_index > node_index){
                head->node_index -=1;
            }
            head = head->next;
        }
    }
    return 0;
}

int change_node_type(Graph* graph, int node_index, int new_type) {
    if (node_index == -1) {
        return 1;
    }
    (*(graph->nodes + node_index))->type = new_type;
    return 0;
}


int* shortest_path_from_this_node(Graph* graph, int start_index) {
    if(start_index == -1) {
        return NULL;
    }
    int *dist, *visited, *prev_shortest;
    init_for_dijkstra(&dist, &visited, &prev_shortest, graph->nodes_count);
    int curr_node = start_index;
    dist[curr_node] = 0;
    int number_of_visited = 0;
    while (number_of_visited < graph->nodes_count) {
        adj_list* ptr = (*(graph->nodes + curr_node))->head;
        while (ptr != NULL) {
            int next_node = ptr->node_index;
            if (visited[next_node] == 0 && dist[next_node] > dist[curr_node] + 1) {
                dist[next_node] = dist[curr_node] + 1;
                prev_shortest[next_node] = curr_node;
            }
            ptr = ptr->next;
        }
        visited[curr_node] = 1;
        number_of_visited++;
        curr_node = get_index_of_min_unvisited(dist, visited, graph->nodes_count);
    }
    free(visited);
    free(dist);
    return prev_shortest;
}

int breadth_first_search(Graph* graph, int start, int dest) {
    if(start==-1 || dest==-1){
        return 0;
    }
    if(start==dest){
        return 1;
    }
    int *visited = (int *)calloc(graph->nodes_count, sizeof(int));
    queue *q = init_q();
    push(q, start);
    visited[start] = 1;
    while (!is_empty(q)) {
        int node_index = pop(q);
        adj_list *ptr = (*(graph->nodes + node_index))->head;
        while (ptr != NULL) {
            if (!visited[ptr->node_index]) {
                push(q, ptr->node_index);
                visited[ptr->node_index] = 1;
                if (ptr->node_index == dest) {
                    return 1;
                }
            }
            ptr = ptr->next;
        }
    }
    return 0;
}

/*Graph* skeleton(const Graph* graph) {
    if(!check_exits(graph) || !check_entries(graph)){
        return NULL;
    }
}

void clear_graph(Graph** graph) {
}*/
