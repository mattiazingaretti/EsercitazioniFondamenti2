#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int node_key = 0;
static int edge_key = 0;

graph * graph_new() {
	graph * g = (graph *) malloc(sizeof(graph));
    g->nodes = linked_list_new();
	g->n_nodes = 0;
	g->n_edges = 0;
    return g;
}

linked_list * graph_get_nodes(graph * g) {
	if (g)
		return g->nodes;
	else {
		printf("ERROR - invocation with NULL in graph_get_nodes\n");
		return NULL;
	}
}

int graph_get_next_node_key() {
	return node_key;
}

int graph_get_next_edge_key() {
	return edge_key;
}

linked_list* graph_get_outgoing_edges(graph* g, graph_node* n){
	if (g && n)
		return n->outgoing_edges;
	else {
		printf("ERROR - invocation with NULL in graph_get_outgoing_edges\n");
		return NULL;
	}
}

linked_list * graph_get_incoming_edges(graph * g, graph_node * n) {
	if (g && n)
		return n->incoming_edges;
	else {
		printf("ERROR - invocation with NULL in graph_get_incoming_edges\n");
		return NULL;
	}
}

graph_node * graph_add_node(graph * g, char* label) {
	if (g && label) {
		graph_node * to_ret = (graph_node *)malloc(sizeof(graph_node));
		to_ret->key = node_key++;
		to_ret->label = label;
		to_ret->incoming_edges = linked_list_new();
		to_ret->outgoing_edges = linked_list_new();
		linked_list_insert_tail(g->nodes, to_ret);
		(g->n_nodes)++;
		return to_ret;
	}
	else {
		printf("ERROR - invocation with NULL in graph_add_node\n");
		return NULL;
	}
}

void graph_add_edge(graph * g, graph_node * n1, graph_node * n2) {
	if (g && n1 && n2) {
		linked_list_iterator* it = linked_list_iterator_new(g->nodes);
		graph_node* outer = linked_list_iterator_getvalue(it);
		for (; linked_list_iterator_hasnext(it); outer = linked_list_iterator_next(it)) {
			if (outer == n1) {
				linked_list_iterator* inner_it = linked_list_iterator_new(outer->outgoing_edges);
				graph_edge* edge = linked_list_iterator_getvalue(inner_it);
				for (; linked_list_iterator_hasnext(inner_it); edge = linked_list_iterator_next(inner_it)) {
					if (edge->n2 == n2) {
						linked_list_iterator_delete(inner_it);
						linked_list_iterator_delete(it);
						return; // The edge is already in the graph
					}
				}
				linked_list_iterator_delete(inner_it);
			}
		}
		linked_list_iterator_delete(it);

		graph_edge* to_ret = (graph_edge*)malloc(sizeof(graph_edge));
		to_ret->key = edge_key++;
		to_ret->n1 = n1;
		to_ret->n2 = n2;
		linked_list_insert_head(n1->outgoing_edges, to_ret);
		linked_list_insert_head(n2->incoming_edges, to_ret);
		(g->n_edges)++;
	}
	else {
		printf("ERROR - invocation with NULL in graph_add_edge\n");
		return;
	}
}

int graph_get_node_key(graph_node * n) {
	if (n)
		return n->key;
	else {
		printf("ERROR - invocation with NULL in graph_get_node_key, returning -1 as default value\n");
		return -1;
	}
}

int graph_get_edge_key(graph_edge * e){
	if (e)
		return e->key;
	else {
		printf("ERROR - invocation with NULL in graph_get_edge_key, returning 0 as default value\n");
		return 0;
	}
}

char* graph_get_node_label(graph_node* n) {
	if (n)
		return n->label;
	else {
		printf("ERROR - invocation with NULL in graph_get_node_label, returning NULL as default value\n");
		return NULL;
	}
}

graph_node * graph_get_edge_opposite(graph_edge * e, graph_node * cur){
	if (e && cur) {
		if (e->n1 == cur)
			return e->n2;
		if(e->n2 == cur)
			return e->n1;
		printf("ERROR - wrong invocation in graph_get_edge_opposite\n");
		return NULL; // ERRORE, l'arco e non contiene il nodo cur
	}
	else {
		printf("ERROR - invocation with NULL in graph_get_edge_opposite\n");
		return NULL;
	}
}

static graph_edge* graph_remove_edge_aux(graph* g, graph_node* v1, graph_node* v2) {
	linked_list_iterator *it = linked_list_iterator_new(g->nodes);
	graph_node* current = (graph_node*)linked_list_iterator_getvalue(it);
	while (linked_list_iterator_hasnext(it)) {
		if (current == v1) {
			linked_list_iterator *it2 = linked_list_iterator_new(v1->outgoing_edges);
			graph_edge* search = linked_list_iterator_getvalue(it2);
			while (linked_list_iterator_hasnext(it2)) {
				if (search->n2 == v2) {
					linked_list_iterator_remove(it2);
					break;
				}
				search = linked_list_iterator_next(it2);
			}
			linked_list_iterator_delete(it2);
		}
		else if(current == v2) {
			linked_list_iterator *it2 = linked_list_iterator_new(v2->incoming_edges);
			graph_edge* search = linked_list_iterator_getvalue(it2);
			while (linked_list_iterator_hasnext(it2)) {
				if (search->n1 == v1) {
					free(search);
					linked_list_iterator_remove(it2);
					break;
				}
				search = linked_list_iterator_next(it2);
			}
			linked_list_iterator_delete(it2);
		}
		current = linked_list_iterator_next(it);
	}
	linked_list_iterator_delete(it);
	return NULL;
}

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
	if (g && v1 && v2) {
		graph_remove_edge_aux(g, v1, v2);
		(g->n_edges)--;
	}
	else {
		printf("ERROR - invocation with NULL in graph_remove_edge\n");
		return;
	}
}

void graph_remove_node(graph* g, graph_node* v) {
	if (g && v) {
		linked_list_iterator *it = linked_list_iterator_new(g->nodes);
		graph_node *cur = (graph_node*)linked_list_iterator_getvalue(it);
		for (; linked_list_iterator_hasnext(it); cur = linked_list_iterator_next(it)) {
			//case I found v in g->nodes
			if (cur == v) {
				linked_list_iterator *it2 = linked_list_iterator_new(cur->outgoing_edges);
				for (; linked_list_iterator_hasnext(it2); linked_list_iterator_next(it2)) {
					linked_list_iterator_remove(it2);
					(g->n_edges)--;
				}
				linked_list_iterator_delete(it2);
				it2 = linked_list_iterator_new(cur->incoming_edges);
				for (; linked_list_iterator_hasnext(it2); linked_list_iterator_next(it2)) {
					linked_list_iterator_remove(it2);
					(g->n_edges)--;
				}
				linked_list_iterator_delete(it2);
				linked_list_iterator_remove(it);
			}
			//case I am on a generic node
			else {
				linked_list_iterator *it2 = linked_list_iterator_new(cur->outgoing_edges);
				graph_edge *edge = (graph_edge*)linked_list_iterator_getvalue(it2);
				for (; linked_list_iterator_hasnext(it2); edge = linked_list_iterator_next(it2)) {
					if (edge->n2 == v) {
						free(edge);
						linked_list_iterator_remove(it2);
					}
				}
				linked_list_iterator_delete(it2);
				it2 = linked_list_iterator_new(cur->incoming_edges);
				edge = (graph_edge*)linked_list_iterator_getvalue(it2);
				for (; linked_list_iterator_hasnext(it2); edge = linked_list_iterator_next(it2)) {
					if (edge->n1 == v) {
						free(edge);
						linked_list_iterator_remove(it2);
					}
				}
				linked_list_iterator_delete(it2);
			}
		}
		(g->n_nodes)--;
		linked_list_iterator_delete(it);
		linked_list_delete(v->incoming_edges);
		linked_list_delete(v->outgoing_edges);
		free(v);
	}
	else {
		printf("ERROR - invocation with NULL in graph_remove_node\n");
		return;
	}
}

void graph_delete(graph * g) {
	if (g) {
		for (int i = 0; i < g->n_nodes; ++i) {
			linked_list_node* lln = g->nodes->head;
			while(lln != NULL){
				graph_node* n = (graph_node*)(lln->value);
				lln = lln->next;
				graph_remove_node(g, n);
			}
		}
		linked_list_delete(g->nodes);
		free(g);
	}
	else {
		printf("ERROR - invocation with NULL in graph_delete\n");
		return;
	}
}

void graph_print(graph* g) {
	if (g) {
		linked_list_iterator *it = linked_list_iterator_new(g->nodes);
		graph_node* cur = (graph_node*)linked_list_iterator_getvalue(it);
		while (linked_list_iterator_hasnext(it)) {
			printf("%s <-- : ", cur->label);
			linked_list_iterator *it2 = linked_list_iterator_new(cur->incoming_edges);
			graph_edge* edge = linked_list_iterator_getvalue(it2);
			while (linked_list_iterator_hasnext(it2)) {
				printf("%s ", edge->n1->label);
				edge = linked_list_iterator_next(it2);
			}
			printf("\n");
			linked_list_iterator_delete(it2);
			printf( "  --> : ");
			it2 = linked_list_iterator_new(cur->outgoing_edges);
			edge = linked_list_iterator_getvalue(it2);
			while (linked_list_iterator_hasnext(it2)) {
				printf("%s ", edge->n2->label);
				edge = linked_list_iterator_next(it2);
			}
			cur = linked_list_iterator_next(it);
			printf("\n");
			linked_list_iterator_delete(it2);
		}
		linked_list_iterator_delete(it);
		printf("n_nodes:%d,  n_edges:%d\n", g->n_nodes, g->n_edges);
	}
	else {
		printf("ERROR - invocation with NULL in graph_print\n");
		return;
	}
}