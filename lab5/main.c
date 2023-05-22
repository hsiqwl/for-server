#include <stdio.h>
#include "graph.h"
#include "dialog.h"
int main() {
    Graph* graph = init();
    void (*fptr[])(Graph*) = {NULL,insert_node, insert_link, remove_link, remove_node, show_graph, find_shortest_path,
                              check_if_reachable};
    int command;
    printf("enter command:");
    scanf("%d", &command);
    while(command)
    {
        fptr[command](graph);
        printf("\n");
        printf("enter command:");
        scanf("%d", &command);
    }
    //clear_graph(&graph);
    return 0;
}
