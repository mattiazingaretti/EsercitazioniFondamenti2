#include "graph.h"
#include "linked_list.h"

#ifndef __GRAPH_SERVICES_H__
#define __GRAPH_SERVICES_H__

/**
 * Dato un grafo g, rappresentato mediante matrice di adiacenze, ritornare il grafo g'
 * che e' uguale a g, ma e' rappresentato mediante lista di incidenze.
*/
graph* mat2list(int** g, int n);

/**
 * Dato un grafo in input, la funziona ritorna 1 se il grafo e' fortemente connesso, 0 altrimenti.
*/
int is_strongly_connected(graph* g);

/**
 * Dato un grafo g, ritornare 1 se il grafo e' uguale alla sua chiusura transitiva, 0 altrimenti. 
*/ 
int is_closed(graph* g);

#endif // !__GRAPH_SERVICES_H__
