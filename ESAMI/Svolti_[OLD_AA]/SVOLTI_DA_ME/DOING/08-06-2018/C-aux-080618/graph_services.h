#include "graph.h"
#include "linked_list.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__

/**
* Ritorna la lista degli archi di g.
*/
linked_list* graph_get_edges(graph* g);

/**
* Ritorna 1 se il grafo g è connesso, 0 altrimenti.
*/
int graph_is_connected(graph* g);

/**
* Ritorna 1 se il grafo g è 1-connesso, 0 altrimenti.
*/
int graph_is_1_connected(graph* g);

#endif // !__GRAPH_SERVICES_H__
