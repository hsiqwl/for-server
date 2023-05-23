#include "graph.h"
#include <stdlib.h>
#include "utils.h"
#include "queue.h"
#include <stdio.h>
#include "stack.h"
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
    clear_adj_list(&((*ptr)->head));
    free((*ptr)->point);
    free(*ptr);
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
    int *dist, *visited, *prev_shortest, *heap;
    init_for_dijkstra(&dist, &visited, &prev_shortest,&heap, graph->nodes_count);
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
    free(heap);
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
                    clear_q(&q);
                    free(visited);
                    return 1;
                }
            }
            ptr = ptr->next;
        }
    }
    clear_q(&q);
    free(visited);
    return 0;
}

void delete_graph(Graph** graph){
    Node** ptr = (*graph)->nodes;
    for(int i=0;i<(*graph)->nodes_count;i++,++ptr){
        clear_adj_list(&((*ptr)->head));
        free((*ptr)->point);
        free((*ptr));
    }
    free((*graph)->nodes);
    free(*graph);
}

/*Graph* skeleton(Graph* graph){
    Graph* new = init();
    Node** ptr = graph->nodes;
    int* color = (int*)malloc(sizeof(int)*graph->nodes_count);
    stack* s = init_stack();
    for(int i = 0; i < graph->nodes_count;++i,++ptr){
        Point* point = new_point((*ptr)->point->x, (*ptr)->point->y);
        Node* node = new_node(point, (*ptr)->type, i);
        add_node(new, node);
        color[i] = i;
        if((*ptr)->type == ENTRY){
            push_top(s,(*ptr)->node_index);
        }
    }
    while(!stack_empty(s)){
        int curr_node = get_top(s);
        adj_list* p = (*(graph->nodes + curr_node))->head;
        while(p!=NULL){
            if(!is_connected(curr_node, p->node_index, color)){
                connect(curr_node, p->node_index, color, graph->nodes_count);
                push_top(s,p->node_index);
                add_link(new, curr_node, p->node_index);
                break;
            }else{
                p = p->next;
            }
        }
        if(p==NULL){
            pop_top(s);
        }
    }
    delete_stack(&s);
    free(color);
    return new;
}*/

int* bfs(Graph* graph, int start){
    if(start==-1){
        return 0;
    }
    int *visited = (int *)calloc(graph->nodes_count, sizeof(int));
    int* pred = (int*)calloc(graph->nodes_count, sizeof(int));
    for(int i = 0; i < graph->nodes_count;++i){
        pred[i] = start;
    }
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
                pred[ptr->node_index] = node_index;
            }
            ptr = ptr->next;
        }
    }
    clear_q(&q);
    free(visited);
    return pred;
}

Graph* skeleton(Graph* graph){
    Graph* new = init();
    Node** ptr = graph->nodes;
    int* color = (int*)malloc(sizeof(int)*graph->nodes_count);
    int* exits = (int*)malloc(sizeof(int)*graph->nodes_count);
    int len = 0;
    for(int i = 0; i < graph->nodes_count;++i,++ptr) {
        Point *point = new_point((*ptr)->point->x, (*ptr)->point->y);
        Node *node = new_node(point, (*ptr)->type, i);
        add_node(new, node);
        color[i] = i;
        if((*ptr)->type == EXIT){
            exits[len] = (*ptr)->node_index;
            len++;
        }
    }
    ptr = graph->nodes;
    for(int i = 0; i < graph->nodes_count;++i,++ptr) {
        if((*ptr)->type == ENTRY){
            int* pred = bfs(graph, (*ptr)->node_index);
            for(int j = 0; j<len;j++){
                int end = exits[j];
                while(end!=(*ptr)->node_index){
                    if(!is_connected(end,pred[end], color)){
                        add_link(new, pred[end], end);
                        connect(pred[end], end, color, graph->nodes_count);
                    }
                }
            }
            free(pred);
        }
    }
    ptr = new->nodes;
    for(int i = 0; i < graph->nodes_count;++i,++ptr) {
        adj_list* head = (*ptr)->head;
        if(head==NULL){
            adj_list* head_in_old = (*(graph->nodes + ((*ptr)->node_index)))->head;
            while(head_in_old!=NULL){
                if(!is_connected(head_in_old->node_index, (*ptr)->node_index, color)){
                    connect(head_in_old->node_index, (*ptr)->node_index, color, graph->nodes_count);
                    add_link(new,(*ptr)->node_index, head_in_old->node_index);
                    break;
                }
                head_in_old = head_in_old->next;
            }
        }
    }
    free(exits);
    free(color);
    return new;
}
