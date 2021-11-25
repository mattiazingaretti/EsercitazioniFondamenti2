#ifndef __GRAPH_H__
#define	__GRAPH_H__

#include "linked_list.h"
#include <stdio.h>

/**
* Etichette potenzialmente utili, associabili agli archi di un grafo.
*/

#define UNEXPLORED (0)
#define DISCOVERY (1)
#define BACK (2)
#define EXCLUDED (3)

/**
* Grafo semplice diretto rappresentato mediante liste delle incidenze.
*/

typedef struct graph {
	linked_list* nodes;		// lista di graph_node
	int n_nodes;
	int n_edges;
} graph;

typedef struct graph_node {
	int key;
	int tag;
	char* label;
	linked_list* incoming_edges;	// lista di graph_edge in entrata
	linked_list* outgoing_edges;	// lista di graph_edge in uscita
} graph_node;

typedef struct graph_edge {
	int key;
	int tag;
	graph_node* n1;
	graph_node* n2;
} graph_edge;

/**
* Crea un nuovo grafo vuoto.
*/
graph * graph_new();

/**
* Ritorna la lista dei nodi del grafo g. Notare che e' possibile ottenere questa lista anche attraverso g->nodes.
*/
linked_list * graph_get_nodes(graph * g);

/**
* Ritorna la prossima chiave da assegnare al nodo di un qualsiasi grafo.
*/
int graph_get_next_node_key();

/**
* Ritorna la prossima chiave da assegnare all' arco di un qualsiasi grafo.
*/
int graph_get_next_edge_key();

/**
* Ritorna la lista degli archi in entrata ad n. Notare che e' possibile ottenere questa lista anche attraverso n->incoming_edges.
*/
linked_list * graph_get_incoming_edges(graph * g, graph_node * n);

/**
* Ritorna la lista degli archi in uscita da n. Notare che e' possibile ottenere questa lista anche attraverso n->outgoing_edges.
*/
linked_list * graph_get_outgoing_edges(graph * g, graph_node * n);


/**
* Aggiunge un nodo al grafo con la label specificata.
*/
graph_node * graph_add_node(graph * g, char* label);

/**
* Aggiunge al grafo g un arco che collega i nodi n1 ed n2, in direzione n1 -> n2.
*/
void graph_add_edge(graph * g, graph_node * n1, graph_node * n2);

/**
* Ritorna la chiave del nodo n. Notare che e' possibile ottenere tale chiave anche attraverso n->key.
*/
int graph_get_node_key(graph_node * n);

/**
* Ritorna la chiave dell'arco n. Notare che e' possibile ottenere tale chiave anche attraverso e->key.
*/
int graph_get_edge_key(graph_edge* e);

/**
* Ritorna la label del nodo n. Notare che e' possibile ottenere tale label anche attraverso n->label.
*/
char* graph_get_node_label(graph_node* n);

/**
* Ritorna il nodo in posizione opposta a cur, rispetto all'arco e.
*/
graph_node* graph_get_edge_opposite(graph_edge* e, graph_node* cur);

/**
* Rimuove dal grafo g l'arco che collega i nodi v1 e v2, in direzione v1 -> v2. Libera solo la memoria assegnata all'arco.
*/
void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2);

/**
* Rimuove il nodo v e tutti gli archi incidenti a v dal grafo g. Libera la memoria di entrambi il nodo e gli archi, ma non dei vertici
* opposti agli archi liberati.
*/
void graph_remove_node(graph* g, graph_node* v);

/**
* Cancella il grafo g e libera la memoria allocata per tutti i suoi nodi ed archi.
*/
void graph_delete(graph * g);

/**
* Stampa a video una rappresentazione del grafo g.
*/
void graph_print(graph* g);

#endif	/* __GRAPH_H__ */