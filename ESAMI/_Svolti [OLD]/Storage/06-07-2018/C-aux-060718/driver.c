#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"
#include "graph_services.h"
#include "bintree.h"
#include "bintree_services.h"

void print_help() {
    printf("Manca argomento: {graph, list, bintree, istree, path, maxsubtree}\n");
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

		// graph_print(graph);
		
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
		// graph_print(graph);

		printf("\n");
		printf("Rimozione: %s,%s\n", graph_get_node_label(sei), graph_get_node_label(tre));
		graph_remove_edge(graph, sei, tre);
		// graph_print(graph);

		printf("Rimozione: %s,%s\n", graph_get_node_label(tre), graph_get_node_label(due));
		graph_remove_edge(graph, tre, due);
		// graph_print(graph);

		printf("Rimozione: %s,%s\n", graph_get_node_label(quattro), graph_get_node_label(tre));
		graph_remove_edge(graph, quattro, tre);
		// graph_print(graph);

		printf("Aggiunta: %s,%s\n", graph_get_node_label(tre), graph_get_node_label(sei));
		graph_add_edge(graph, tre, sei);
		// graph_print(graph);

		printf("Aggiunta: %s,%s\n", graph_get_node_label(quattro), graph_get_node_label(tre));
		graph_add_edge(graph, quattro, tre);
		// graph_print(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", graph_get_node_label(quattro));
		graph_remove_node(graph, quattro);
		// graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(uno));
		graph_remove_node(graph, uno);
		// graph_print(graph);

		printf("Aggiunta nodo: %s\n", "test");
		graph_add_node(graph, "test");
		// graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(otto));
		graph_remove_node(graph, otto);
		// graph_print(graph);

		printf("Rimozione nodo: %s\n", graph_get_node_label(sei));
		graph_remove_node(graph, sei);
		// graph_print(graph);

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
	else if (strcmp(argv[1], "bintree") == 0){
		binTree* bt0 = bintree_new(0);

		binTree* bt1 = bintree_set_left_child(bt0, 1);
		binTree* bt11 = bintree_set_left_child(bt1, 3);
		bintree_set_left_child(bt11, 5);
		bintree_set_right_child(bt11, 6);

		bintree_set_left_child(bt1, 4);

		binTree* bt2 = bintree_set_right_child(bt0, 2);
		bintree_set_left_child(bt2, 7);
		bintree_set_right_child(bt2, 8);

		bintree_print(bt0);
		printf("\n");
		bintree_print(bt2);
		bintree_delete(bt0);
	}
	else if (strcmp(argv[1], "istree") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_node* e = graph_add_node(g, "e");
		graph_node* f = graph_add_node(g, "f");
		graph_node* gi = graph_add_node(g, "g");
		graph_node* h = graph_add_node(g, "h");
		graph_node* i = graph_add_node(g, "i");
		graph_node* l = graph_add_node(g, "l");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, d);
		graph_add_edge(g, d, h);
		graph_add_edge(g, h, i);
		graph_add_edge(g, h, l);
		graph_add_edge(g, c, e);
		graph_add_edge(g, c, f);
		graph_add_edge(g, c, gi);

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		graph_print(g);
		printf("istree --> %d\n", is_tree(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		e = graph_add_node(g, "e");
		f = graph_add_node(g, "f");
		gi = graph_add_node(g, "g");
		h = graph_add_node(g, "h");
		i = graph_add_node(g, "i");
		l = graph_add_node(g, "l");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, d);
		graph_add_edge(g, d, h);
		graph_add_edge(g, h, i);
		graph_add_edge(g, h, l);
		graph_add_edge(g, c, e);
		graph_add_edge(g, c, f);
		graph_add_edge(g, c, gi);
		graph_add_edge(g, a, e);

		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		graph_print(g);
		printf("istree --> %d\n", is_tree(g));
		graph_delete(g);
		printf("\n");

		g = graph_new();
		a = graph_add_node(g, "a");
		b = graph_add_node(g, "b");
		c = graph_add_node(g, "c");
		d = graph_add_node(g, "d");
		e = graph_add_node(g, "e");
		f = graph_add_node(g, "f");
		gi = graph_add_node(g, "g");
		h = graph_add_node(g, "h");
		i = graph_add_node(g, "i");
		l = graph_add_node(g, "l");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, d);
		graph_add_edge(g, h, i);
		graph_add_edge(g, h, l);
		graph_add_edge(g, c, e);
		graph_add_edge(g, c, f);
		graph_add_edge(g, c, gi);
		graph_add_edge(g, a, e);

		printf("################################\n");
		printf("Terzo test\n");
		printf("################################\n");
		graph_print(g);
		printf("istree --> %d\n", is_tree(g));
		graph_delete(g);
		printf("\n");
	}
	else if (strcmp(argv[1], "path") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "a");
		graph_node* b = graph_add_node(g, "b");
		graph_node* c = graph_add_node(g, "c");
		graph_node* d = graph_add_node(g, "d");
		graph_node* e = graph_add_node(g, "e");
		graph_node* f = graph_add_node(g, "f");
		graph_node* gi = graph_add_node(g, "g");
		graph_node* h = graph_add_node(g, "h");
		graph_node* i = graph_add_node(g, "i");
		graph_node* l = graph_add_node(g, "l");

		graph_add_edge(g, a, b);
		graph_add_edge(g, a, c);
		graph_add_edge(g, b, d);
		graph_add_edge(g, d, h);
		graph_add_edge(g, d, e);
		graph_add_edge(g, h, i);
		graph_add_edge(g, h, l);
		graph_add_edge(g, c, e);
		graph_add_edge(g, c, f);
		graph_add_edge(g, gi, f);
		graph_add_edge(g, c, gi);

		graph_print(g);
		printf("\n");

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		printf("minpath b,e per g --> %d\n", get_size_constrained_path(g, b, gi, e));
		printf("\n");

		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		printf("minpath b,a per g --> %d\n", get_size_constrained_path(g, b, gi, a));
		printf("\n");

		printf("################################\n");
		printf("Terzo test\n");
		printf("################################\n");
		printf("minpath b,f per g --> %d\n", get_size_constrained_path(g, b, gi, f));
		printf("\n");

		printf("################################\n");
		printf("Quarto test\n");
		printf("################################\n");
		printf("minpath b,d per h --> %d\n", get_size_constrained_path(g, b, h, d));
		printf("\n");

		graph_delete(g);
	}
	else if (strcmp(argv[1], "maxsubtree") == 0){
		binTree* bt0 = bintree_new(1);

		binTree* bt1 = bintree_set_left_child(bt0, 2);
		binTree* bt11 = bintree_set_left_child(bt1, 4);
		bintree_set_left_child(bt11, 8);
		bintree_set_right_child(bt11, 9);
		binTree* bt12 = bintree_set_right_child(bt1, 5);
		bintree_set_left_child(bt12, 10);
		bintree_set_right_child(bt12, 11);

		binTree* bt2 = bintree_set_right_child(bt0, 3);
		bintree_set_left_child(bt2, 6);
		bintree_set_right_child(bt2, 7);

		printf("################################\n");
		printf("Primo test\n");
		printf("################################\n");
		bintree_print(bt0);
		printf("maxsubtree --> %d\n", get_size_max_complete_subtree(bt0));
		printf("\n");
		bintree_delete(bt0);

		bt0 = bintree_new(1);

		bt1 = bintree_set_left_child(bt0, 2);
		bt11 = bintree_set_left_child(bt1, 4);
		bintree_set_left_child(bt11, 8);
		bintree_set_right_child(bt11, 9);
		bt12 = bintree_set_right_child(bt1, 5);
		bintree_set_left_child(bt12, 10);

		bt2 = bintree_set_right_child(bt0, 3);
		bintree_set_left_child(bt2, 6);
		bintree_set_right_child(bt2, 7);

		printf("################################\n");
		printf("Secondo test\n");
		printf("################################\n");
		bintree_print(bt0);
		printf("maxsubtree --> %d\n", get_size_max_complete_subtree(bt0));
		printf("\n");
		bintree_delete(bt0);

		bt0 = bintree_new(1);

		bt1 = bintree_set_left_child(bt0, 2);
		bt11 = bintree_set_left_child(bt1, 4);
		bintree_set_left_child(bt11, 8);
		bintree_set_right_child(bt11, 9);
		bt12 = bintree_set_right_child(bt1, 5);
		bintree_set_left_child(bt12, 10);

		bt2 = bintree_set_right_child(bt0, 3);
		bintree_set_left_child(bt2, 6);

		printf("################################\n");
		printf("Terzo test\n");
		printf("################################\n");
		bintree_print(bt0);
		printf("maxsubtree --> %d\n", get_size_max_complete_subtree(bt0));
		printf("\n");
		bintree_delete(bt0);
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}