#include "graph_services.h"
#include "min_heap.h"

#include <stdio.h>
#include <stdlib.h>

void bfs(graph* g, graph_node* source) {
	
	//Reset nodi
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		n->status = UNEXPLORED;
		n->timestamp = 0;
		n = linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);

	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);

	//Scorro finché non mi posiziono sul nodo sorgente, quello da cui parto
	while (linked_list_iterator_hasnext(lli)) {
		if (n == source)
			break;
		n = linked_list_iterator_next(lli);
	}

	//Setto i valori dei livelli e stampo
	printf("Livello %s: %d\n", (char*)n->value, n->timestamp);
	int old;
	for (old = 1; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
		linked_list_iterator* edges = linked_list_iterator_new(n->out_edges);
		graph_edge* e = (graph_edge*)linked_list_iterator_getvalue(edges);
		for (; linked_list_iterator_hasnext(edges); e = linked_list_iterator_next(edges)) {
			e->target->timestamp = old;
			if (e->target->status == UNEXPLORED) {
				printf("Livello %s: %d\n", (char*)e->target->value, e->target->timestamp);
				e->target->status = EXPLORED;
			}
		}
		if (n->status == UNEXPLORED)
			old++;
		n->status = EXPLORED;
		linked_list_iterator_delete(edges);
	}
	linked_list_iterator_delete(lli);
}

void sssp(graph* g, graph_node* source) {
	//creazione di un min heap
	min_heap* pq = min_heap_new();

	//inserimento dei nodi nell'heap con distanza infinita se n != source, altrimenti 0
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	while (linked_list_iterator_hasnext(lli)) {
		if (n == source) {
			min_heap_insert(pq, 0, n);
			n->dist = 0;
		}
		else {
			min_heap_insert(pq, 100000, n);
			n->dist = 100000;
		}
		n = linked_list_iterator_next(lli);
	}
	linked_list_iterator_delete(lli);

	//rimuovo ogni volta l'entry più piccola e dichiaro un puntatore, poi passo il puntatore a un puntatore a nodo
	while (!min_heap_is_empty(pq)) {
		min_heap_struct_entry* e = min_heap_remove_min(pq);
		graph_node* u = (graph_node*)e->value;
		free(e);

		//scorro gli archi incidenti u
		lli = linked_list_iterator_new(u->out_edges);
		graph_edge* edge = (graph_edge*)linked_list_iterator_getvalue(lli);
		for (; linked_list_iterator_hasnext(lli); edge = linked_list_iterator_next(lli)) {
			graph_node* v = (graph_node*)edge->target;
			if (u->dist + edge->weight < v->dist) { //passo per verificare che il percorso sia minimo, else replace
				int replaced = u->dist + edge->weight;
				min_heap_insert(pq, replaced, v);
				v->dist = replaced;
			}
		}
		linked_list_iterator_delete(lli);
	}
	min_heap_free(pq);

	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);

	printf("Distanze dal nodo %s [", (char*)source->value);
	for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
			printf("%s:%d, ", (char*)n->value, n->dist);
	}
	puts("]\n");
}

void apsp(graph* g) {
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
		sssp(g, n);
	}
	linked_list_iterator_delete(lli);
}
