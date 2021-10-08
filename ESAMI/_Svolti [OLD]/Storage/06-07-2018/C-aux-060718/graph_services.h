#include "graph.h"
#include "linked_list.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__

/**
 * Dato un grafo in input, la funziona ritorna 1 se il grafo è un albero, 0 altrimenti.
*/
int is_tree(graph*);

/**
 * Dato un grafo g e tre nodi x,y,z appartenenti a g, la funziona ritorna la lunghezza
 * del cammino minimo che connette x e z in g, passando per y. Se non esiste alcun cammino
 * la funzione deve ritornare il valore di default -1.
*/
int get_size_constrained_path(graph*, graph_node*, graph_node*, graph_node*);

#endif // !__GRAPH_SERVICES_H__
