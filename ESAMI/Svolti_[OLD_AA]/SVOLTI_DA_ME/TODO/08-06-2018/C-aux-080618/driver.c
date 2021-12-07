#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"
#include "graph_services.h"

void print_help() {
    printf("Manca argomento: {graph, list, edges, conn, 1-conn}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "graph") == 0) {
		graph * graph = graph_new();

		graph_add_node(graph, "a");
		graph_node * uno = graph_add_node(graph, "b");
		graph_node * due = graph_add_node(graph, "c");
		graph_node * tre = graph_add_node(graph, "d");
		graph_node * quattro = graph_add_node(graph, "e");
		graph_node * cinque = graph_add_node(graph, "f");
		graph_node * sei = graph_add_node(graph, "g");
		graph_node * sette = graph_add_node(graph, "h");
		graph_node * otto = graph_add_node(graph, "i");

		graph_print(graph);
		
		graph_add_edge(graph, uno, due);
		graph_add_edge(graph, uno, sei);
		graph_add_edge(graph, due, tre);
		graph_add_edge(graph, due, sei);
		graph_add_edge(graph, tre, quattro);
		graph_add_edge(graph, quattro, due);
		graph_add_edge(graph, cinque, sei);
		graph_add_edge(graph, sei, tre);
		graph_add_edge(graph, sette, otto);

		printf("Grafo iniziale\n\n");
		graph_print(graph);

		printf("\n");
		printf("Rimozione: %s,%s\n", graph_get_node_label(sei), graph_get_node_label(tre));
		graph_remove_edge(graph, sei, tre);
		graph_print(graph);

		printf("Rimozione: %s,%s\n", graph_get_node_label(tre), graph_get_node_label(due));
		graph_remove_edge(graph, tre, due);
		graph_print(graph);

		printf("Rimozione: %s,%s\n", graph_get_node_label(quattro), graph_get_node_label(tre));
		graph_remove_edge(graph, quattro, tre);
		graph_print(graph);

		printf("Aggiunta: %s,%s\n", graph_get_node_label(tre), graph_get_node_label(sei));
		graph_add_edge(graph, tre, sei);
		graph_print(graph);

		printf("Aggiunta: %s,%s\n", graph_get_node_label(quattro), graph_get_node_label(tre));
		graph_add_edge(graph, quattro, tre);
		graph_print(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", graph_get_node_label(quattro));
		graph_remove_node(graph, quattro);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(uno));
		graph_remove_node(graph, uno);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(otto));
		graph_remove_node(graph, otto);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(sei));
		graph_remove_node(graph, sei);
		graph_print(graph);

		printf("DONE\n");
		graph_delete(graph);
	}
	else if (strcmp(argv[1], "list") == 0) {
		linked_list* lista = linked_list_new();
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_head(lista, "1");
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_head(lista, "2");
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_tail(lista, "3");
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_tail(lista, "4");
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_head(lista, "5");
		linked_list_print(lista);
		printf("\n");

		linked_list_remove_head(lista);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove_head(lista);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove_head(lista);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove_head(lista);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove_head(lista);
		linked_list_print(lista);
		printf("\n");

		linked_list_insert_head(lista, "1");
		linked_list_insert_head(lista, "2");
		linked_list_insert_head(lista, "3");
		linked_list_insert_head(lista, "4");
		linked_list_insert_head(lista, "5");
		linked_list_print(lista);

		linked_list_iterator *it = linked_list_iterator_new(lista);
		void * cur = linked_list_iterator_getvalue(it);
		for (; linked_list_iterator_hasnext(it); cur = linked_list_iterator_next(it)) {
			if (cur) {
				if (((char*)cur)[0] == '1') {
					linked_list_iterator_remove(it);
				}
				if (((char*)cur)[0] == '4') {
					linked_list_iterator_remove(it);
				}
				if (((char*)cur)[0] == '5') {
					linked_list_iterator_remove(it);
				}
			}
			linked_list_print(lista);
		}
		linked_list_iterator_delete(it);

		printf("DONE\n");
		linked_list_delete(lista);
	}
	else if (strcmp(argv[1], "edges") == 0) {
		graph* graph = graph_new();
		graph_add_node(graph, "a");
		graph_node * uno = graph_add_node(graph, "b");
		graph_node * due = graph_add_node(graph, "c");
		graph_node * tre = graph_add_node(graph, "d");
		graph_node * quattro = graph_add_node(graph, "e");
		graph_node * cinque = graph_add_node(graph, "f");
		graph_node * sei = graph_add_node(graph, "g");
		graph_node * sette = graph_add_node(graph, "h");
		graph_node * otto = graph_add_node(graph, "i");
		graph_add_edge(graph, uno, due);
		graph_add_edge(graph, due, uno);
		graph_add_edge(graph, uno, sei);
		graph_add_edge(graph, due, tre);
		graph_add_edge(graph, due, sei);
		graph_add_edge(graph, due, uno);
		graph_add_edge(graph, tre, quattro);
		graph_add_edge(graph, quattro, due);
		graph_add_edge(graph, cinque, sei);
		graph_add_edge(graph, sei, tre);
		graph_add_edge(graph, tre, sei);
		graph_add_edge(graph, sette, otto);

		printf("Grafo:\n\n");
		graph_print(graph);

		linked_list* edges_of_g = graph_get_edges(graph);
		linked_list_iterator* it = linked_list_iterator_new(edges_of_g);
		graph_edge* edge = linked_list_iterator_getvalue(it);
		for (; linked_list_iterator_hasnext(it); edge = linked_list_iterator_next(it)) {
			printf("%s %s\n", edge->n1->label, edge->n2->label);
		}
		linked_list_iterator_delete(it);
		linked_list_delete(edges_of_g);
		graph_delete(graph);
	}
	else if (strcmp(argv[1], "conn") == 0) {
		// Primo Test
		printf("\n");
		printf("###############\n");
		printf("Primo test:\n");
		printf("###############\n\n");
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, d, c);
		graph_add_edge(g, d, b);
		printf("Grafo:\n\n");
		graph_print(g);
		int con = graph_is_connected(g);
		printf("Grafo connesso? -> %d\n", con);
		graph_delete(g);

		// Secondo Test
		printf("\n");
		printf("###############\n");
		printf("Secondo test:\n");
		printf("###############\n\n");
		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		graph_add_edge(g, a, d);
		graph_add_edge(g, a, c);
		graph_add_edge(g, d, c);
		printf("Grafo:\n\n");
		graph_print(g);
		con = graph_is_connected(g);
		printf("Grafo connesso? -> %d\n", con);
		graph_delete(g);
	}
	else if (strcmp(argv[1], "1-conn") == 0) {
		// Primo Test
		printf("\n");
		printf("###############\n");
		printf("Primo test:\n");
		printf("###############\n\n");
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_add_edge(g, a, b);
		graph_add_edge(g, d, c);
		graph_add_edge(g, d, b);
		printf("Grafo:\n\n");
		graph_print(g);
		int con = graph_is_1_connected(g);
		printf("Grafo 1-connesso? -> %d\n", con);
		graph_delete(g);

		// Secondo Test
		printf("\n");
		printf("###############\n");
		printf("Secondo test:\n");
		printf("###############\n\n");
		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		graph_add_edge(g, a, d);
		graph_add_edge(g, a, c);
		graph_add_edge(g, d, c);
		printf("Grafo:\n\n");
		graph_print(g);
		con = graph_is_1_connected(g);
		printf("Grafo 1-connesso? -> %d\n", con);
		graph_delete(g);

		// Terzo Test
		printf("\n");
		printf("###############\n");
		printf("Terzo test:\n");
		printf("###############\n\n");
		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, d);
		graph_add_edge(g, d, c);
		printf("Grafo:\n\n");
		graph_print(g);
		con = graph_is_1_connected(g);
		printf("Grafo 1-connesso? -> %d\n", con);
		graph_delete(g);
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}