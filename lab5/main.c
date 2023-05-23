#include <stdio.h>
#include "graph.h"
#include "dialog.h"
#include "consts.h"
int main() {
    Graph* graph = init();
    void (*fptr[])(Graph*) = {NULL,insert_node, insert_link, remove_link, remove_node, show_graph, find_shortest_path,
                              check_if_reachable, make_skeleton};
    int command;
    while(command = dialog(msgs,Nmsgs))
    {
        fptr[command](graph);
        printf("\n");
    }
    delete_graph(&graph);
    return 0;
}
