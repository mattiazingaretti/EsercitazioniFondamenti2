#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;

struct graph_node{
    void * value;
    linked_list * out_edges;

    // keep track status
    STATUS state;
    int timestamp;
};

struct graph{
    linked_list * nodes;
};
void remove_edge_aux(graph* g, graph_node* v1, graph_node* v2);
void setUnexplored(graph* g);

graph * graph_new() {
    linked_list * nodes = linked_list_new();
    graph* grafo = malloc(sizeof(graph));
    grafo->nodes = nodes;
	return grafo;
}

linked_list * graph_get_nodes(graph * g) {
    return g->nodes;
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
	return n-> out_edges;
}

graph_node * graph_add_node(graph * g, void * value) {
    //controlla se nodo è già presente
    graph_node* nodo = malloc(sizeof(graph_node));
    nodo->value = value;
    nodo->state = UNEXPLORED;
    nodo->timestamp=0;
    nodo->out_edges= linked_list_new();
    if(g == NULL){
        graph_new();
    }
    linked_list_add(g->nodes, (void*)nodo);
    return nodo;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
    linked_list_add(v1->out_edges, (void*)v2);
    linked_list_add(v2->out_edges, (void*)v1);
}

void * graph_get_node_value(graph_node * n) {
	return n->value;
}

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {
    remove_edge_aux(g,v1,v2);
    remove_edge_aux(g,v2,v1);
}

/*void graph_remove_node(graph* g, graph_node* v) { //devo utilizzare iteratore per scandire lista nodi del grafo
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    linked_list_node* nodo_head = (linked_list_node*) it;
    graph_node* nodo =(graph_node*) linked_list_iterator_getvalue(it);
    if(nodo == v){  //se è la testa
        linked_list_iterator* it2 = linked_list_iterator_new(nodo->out_edges);
        while(it2 != NULL){
            linked_list_iterator* itera = linked_list_iterator_next(it2);
            graph_node* v2 = (graph_node*) linked_list_iterator_getvalue(it2);
            graph_remove_edge(g, v2, nodo);
            it2 = itera;
        }
        if(g->nodes->head == g->nodes->tail){ //coda == testa (un solo elemento nel grafo
            linked_list_delete(nodo->out_edges);
			free(nodo);
            free(nodo_head);
			linked_list_delete(g->nodes);
			g->nodes = linked_list_new();
			return;
        }
        g->nodes->head = nodo_head->next;
        linked_list_delete(nodo->out_edges);
        free(nodo_head);
        free(nodo);
        return;
    }
  //  while(it != NULL){ //non è la testa






     //   it = linked_list_iterator_next(it);
}*/

void graph_remove_node(graph* g, graph_node* v) {
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	linked_list_node* head = (linked_list_node*)it;
	graph_node* head_node = ((graph_node*)(head->value));
	// Case remove head
	if (head_node == v) {
		linked_list_iterator* it2 = linked_list_iterator_new(head_node->out_edges);
		for (; it2 != NULL; ) {
			linked_list_iterator * itera = linked_list_iterator_next(it2);
			graph_node* v2 = (graph_node*)(((linked_list_node*)it2)->value);
			graph_remove_edge(g, head_node, v2);
			it2 = itera;
		}
		if (g->nodes->head == g->nodes->tail) {
			linked_list_delete(head_node->out_edges);
			free(head_node);
			free(head->next);
			linked_list_delete(g->nodes);
			g->nodes = linked_list_new();
			return;
		}
		g->nodes->head = head->next;
		linked_list_delete(head_node->out_edges);
		free(head_node);
		free(head);
		return;
	}
	else {
		for (; it != NULL; it = linked_list_iterator_next(it)) {
			linked_list_node* nxt = (linked_list_node*)linked_list_iterator_next(it);
			if (nxt == NULL)
				return;
			graph_node* nxt_node = (graph_node*)(nxt->value);
			int found = 0;
			if (nxt_node == v) {
				found = 1;
				linked_list_iterator* it2 = linked_list_iterator_new(nxt_node->out_edges);
				for (; it2 != NULL; ) {
					linked_list_iterator* itera = linked_list_iterator_next(it2);
					graph_node* v2 = (graph_node*)(((linked_list_node*)it2)->value);
					graph_remove_edge(g, nxt_node, v2);
					it2 = itera;
				}
			}
			if (found) {
				linked_list_node* cur_node = (linked_list_node*)it;
				cur_node->next = nxt->next;
				linked_list_delete(nxt_node->out_edges);
				if (g->nodes->tail == nxt)
					g->nodes->tail = (linked_list_node*)it;
				free(nxt_node);
				free(nxt);
				return;
			}
		}
	}
}

void graph_delete(graph * g) {
	if (g == NULL)
		return;
	linked_list_iterator * i = linked_list_iterator_new(g->nodes);
	while (i != NULL) {
		graph_node * n = linked_list_iterator_getvalue(i);
		free(n->value);
		linked_list_delete(n->out_edges);
		i = linked_list_iterator_next(i);
	}
    linked_list_delete(g->nodes);
    free(g);
}

graph* graph_read_ff(FILE* input) {
	return NULL;
}

void graph_print(graph* g) {
    linked_list* l = g->nodes;
    int size, i;
    size= l->size;
    for(i=0; i < size; i++){
        graph_node* n = (graph_node*) linked_list_get(l, i);
        if(size == -1){
            printf("%s -> \n", (char*)n->value);
            break;
        }
        printf("%s -> ", (char*) n->value);
    }
    printf("\n");
}

void print_edges(graph* g){
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        n->state = EXPLORED;
        linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
        while( it2 != NULL){
            linked_list_iterator* itera2 = linked_list_iterator_next(it2);
            graph_node* n2 = (graph_node*) linked_list_iterator_getvalue(it2);
            if( n2->state == UNEXPLORED){
                printf("%s - %s\n", (char*)n->value, (char*) n2->value);
                //n2->state = EXPLORED;
            }
            it2 = itera2;
        }
        it = itera;
    }
}

void graph_print2(graph* g){
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    int nodi = 0;
    int archi = 0;
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        nodi++;
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
        while( it2 != NULL){
            linked_list_iterator* itera2 = linked_list_iterator_next(it2);
            archi ++;
            it2 = itera2;
        }
        it = itera;
    }
    printf("%d  %d\n", nodi, archi/2);
    print_edges(g);

}

void DFS(graph_node* nodo){
    nodo->state = EXPLORING;
    linked_list_iterator* it = linked_list_iterator_new(nodo->out_edges);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* n = linked_list_iterator_getvalue(it);
        if(n->state == UNEXPLORED){
            DFS(n);
        }
        it = itera;
    }
    nodo->state = EXPLORED;
}

void DFS2(graph_node* nodo, linked_list* l){
    nodo->state = EXPLORING;
    linked_list_add(l,(void*) nodo);
    printf("aggiungo nodo %s\n", (char*)nodo->value);
    linked_list_iterator* it = linked_list_iterator_new(nodo->out_edges);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* n = linked_list_iterator_getvalue(it);
        if(n->state == UNEXPLORED){
            DFS2(n,l);
        }
        it = itera;
    }
    nodo->state = EXPLORED;
}

int graph_n_con_comp(graph * g) {
    setUnexplored(g);
    int count = 0;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->state == UNEXPLORED){
            count++;
            DFS(nodo);
        }
        it = itera;
    }
	return count;
}

linked_list* graph_get_con_comp(graph* g) {
    setUnexplored(g);
    linked_list* l = linked_list_new();
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->state == UNEXPLORED){
            linked_list* to_add= linked_list_new();
            linked_list_add(l, to_add);
            DFS2(nodo, to_add);
        }
        it = itera;
    }
	return l;
}

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(it != NULL){
        linked_list_iterator* itera = linked_list_iterator_next(it);
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        n->state = UNEXPLORED;
        linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
        while(it2 != NULL){
            linked_list_iterator* itera2 = linked_list_iterator_next(it2);
            graph_node* nn = (graph_node*) linked_list_iterator_getvalue(it2);
            nn->state = UNEXPLORED;
            it2 = itera2;
        }
        it = itera;
    }
}

void remove_edge_aux(graph* g, graph_node* v1, graph_node* v2) {
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);
	while (it != NULL) {
		graph_node* n = linked_list_iterator_getvalue(it);
		if (graph_get_node_value(n) == graph_get_node_value(v1)) {
			linked_list_node *it2_head = (n->out_edges->head);
			linked_list_node *it2_tail = (n->out_edges->tail);
			if (((graph_node*)(it2_head->value)) == v2) {
				linked_list_node* to_remove = it2_head;
				if (to_remove == it2_tail) {
					free(to_remove);
					free(n->out_edges);
					n->out_edges = linked_list_new();
					return;
				}
				else {
					n->out_edges->head = it2_head->next;
					free(to_remove);
					(g->nodes->size)--;
					return;
				}
			}
			while (it2_head != NULL) {
				if (it2_head->next != NULL) {
					if (((graph_node*) (it2_head->next->value)) == v2) {
						linked_list_node* to_remove = it2_head->next;
						if (to_remove == it2_tail)
							n->out_edges->tail = it2_head;
						it2_head->next = it2_head->next->next;
						free(to_remove);
						(g->nodes->size)--;
						return;
					}
				}
				it2_head = it2_head->next;
			}
		}
		it = linked_list_iterator_next(it);
	}
}

/*void remove_edge_aux(graph* g, graph_node* v1, graph_node* v2) {  //utilizzo iteratore solo x scandire la lista dei nodi del grafo,non la lista dei vicini del nodo
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    graph_node* n = linked_list_iterator_getvalue(it);
    while(it != NULL){
        if(graph_get_node_value(n) == graph_get_node_value(v1)){ // ho trovato v1 nella lista dei nodi del grafo
            linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
            graph_node* head2 = linked_list_iterator_getvalue(it2);
            linked_list_node* testalista = n->out_edges->head;
            linked_list_node* codalista = n->out_edges->tail;
            if((graph_node*) testalista->value == v2){   //verifico che testa==v2
                linked_list_node* darimuovere = testalista;
                if(testalista == codalista){            //verifico che testa==coda (solo un elemento nella lista dei vicini) quindi elimino tutto
                    free(darimuovere);
                    free(n->out_edges);
                    n->out_edges = linked_list_new();
                    return;
                }
                n->out_edges->head = testalista->next;
                free(darimuovere);
            }
            //caso in cui la lista dei vicini contenga più di un elemento, devo trovare v2, quindi la lista va scandita
            linked_list_node* prec = NULL;
            while(testalista != NULL){
                if((graph_node*) testalista->value == v2){
                    if(head2 == ((graph_node*)codalista->value)){
                        n->out_edges->tail = testalista;
                    }
                    prec->next = testalista->next;
                    free(testalista);
                    return;
                }
                testalista = testalista->next;
            }
        }
        it= linked_list_iterator_next(it);
    }
}*/

