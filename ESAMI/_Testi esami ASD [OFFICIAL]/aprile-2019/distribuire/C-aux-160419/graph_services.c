#include <stdlib.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"

int DFS(graph_node* n) {
	n->tag = DISCOVERY;

	int ret = 1;
	linked_list_iterator* lli = linked_list_iterator_new(n->incident_edges);
	graph_edge* e = (graph_edge*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); e = linked_list_iterator_next(lli)) {
		if (e->tag == UNEXPLORED) {
			e->tag = DISCOVERY;
			graph_node* opposite = graph_get_edge_opposite(e, n);
			if (opposite->tag == UNEXPLORED)
				ret = DFS(opposite);
		}
	}
	linked_list_iterator_delete(lli);
	return ret;
}

int conn_comp(graph* g){
	if (!g)
		return 0;
	
	//inizializzo i nodi e gli archi	
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
		n->tag = UNEXPLORED;
	}
	linked_list_iterator_delete(lli);

	int ret = 0;
	lli = linked_list_iterator_new(g->nodes);
	n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
		if (n->tag == UNEXPLORED)
			ret += DFS(n);
	}
	linked_list_iterator_delete(lli);
	return ret;
}

void contract(graph* g){
	linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
	graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
	for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
		if (n->incident_edges->size == 2) {
			graph_edge* e1 = (graph_edge*)n->incident_edges->head->value;
			graph_edge* e2 = (graph_edge*)n->incident_edges->head->next->value;
			graph_node* u = graph_get_edge_opposite(e1, n);
			graph_node* w = graph_get_edge_opposite(e2, n);
			
			linked_list_iterator* inner = linked_list_iterator_new(u->incident_edges);
			graph_edge* e = (graph_edge*)linked_list_iterator_getvalue(inner);
			int to_delete = 1;
			for (; linked_list_iterator_hasnext(inner); e = linked_list_iterator_next(inner)) {
				graph_node* opposite = graph_get_edge_opposite(e, u);
				if (opposite == w) //mi assicuro che non sia presente un arco (u,w)
					to_delete = 0;
			}
			linked_list_iterator_delete(inner);
			if (to_delete) {
				graph_add_edge(g, u, w);
				graph_remove_edge(g, n, u);
				graph_remove_edge(g, n, w);
				graph_remove_node(g, n);
				break;
			}
		}
	}
	linked_list_iterator_delete(lli);
}

int count_k3(graph* g){
	/*DA IMPLEMENTARE*/
	return 0;
}