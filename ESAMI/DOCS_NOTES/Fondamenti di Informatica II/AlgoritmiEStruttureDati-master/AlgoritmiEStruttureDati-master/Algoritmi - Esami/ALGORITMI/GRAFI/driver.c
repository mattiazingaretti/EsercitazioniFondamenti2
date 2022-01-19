#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"

void print_help() {
    printf("Richiesto argomento: {graph}\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        print_help();
        return EXIT_FAILURE;
    }
    if (strcmp(argv[1], "graph") == 0) {
        graph * graph = graph_new();

        graph_node * a = graph_add_node(graph, "a");
        graph_node * b = graph_add_node(graph, "b");
        graph_node * c = graph_add_node(graph, "c");
        graph_node * d = graph_add_node(graph, "d");
        graph_node * e = graph_add_node(graph, "e");
        graph_node * f = graph_add_node(graph, "f");
        graph_node * g = graph_add_node(graph, "g");
        graph_node * h = graph_add_node(graph, "h");
		graph_node * i = graph_add_node(graph, "i");

        graph_add_edge(graph, a, b);
        graph_add_edge(graph, a, f);
        graph_add_edge(graph, b, c);
        graph_add_edge(graph, b, f);
        graph_add_edge(graph, c, d);
        graph_add_edge(graph, d, b);
        graph_add_edge(graph, e, f);
        graph_add_edge(graph, f, c);
        graph_add_edge(graph, g, h);

        printf("Grafo iniziale\n\n");
        graph_print(graph);
        graph_print2(graph);
        printf("\n");

        int x = graph_n_con_comp(graph);
        printf("le componenti connesse sono %d\n", x);

		printf("Rimozione: %s,%s\n",(char*) graph_get_node_value(f), (char*)graph_get_node_value(c));
		graph_remove_edge(graph, f, c);
		graph_print(graph);
        graph_print2(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(b));
		graph_remove_edge(graph, c, b);
		graph_print(graph);
        graph_print2(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_remove_edge(graph, d, c);
		graph_print(graph);
        graph_print2(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(f));
		graph_add_edge(graph, c, f);
		graph_print(graph);
        graph_print2(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_add_edge(graph, d, c);
		graph_print(graph);
        graph_print2(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(d));
		graph_remove_node(graph, d);
		graph_print(graph);
        graph_print2(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(f));
		graph_remove_node(graph, f);
		graph_print(graph);
        graph_print2(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(c));
		graph_remove_node(graph, c);
		graph_print(graph);
        graph_print2(graph);

		printf("DONE\n");
        x = graph_n_con_comp(graph);
        printf("le componenti connesse sono %d\n", x);
        linked_list* l = graph_get_con_comp(graph);
        printf("size %d\n", linked_list_size(l));
		//graph_delete(graph);
    }
	else {
        print_help();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
