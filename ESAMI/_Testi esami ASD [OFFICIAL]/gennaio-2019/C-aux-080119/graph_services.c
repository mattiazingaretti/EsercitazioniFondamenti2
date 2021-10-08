#include <stdlib.h>
#include <math.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"

static char* char_gen(int seed){
	char* ret = malloc(2 * sizeof(char));
	ret[0] = (char) (65 + (rand() % 26));
	ret[1] = '\0';
	return ret;
}

graph* mat2list(int** g, int n){
    graph* ret = graph_new();
    return ret;
}

int is_strongly_connected(graph* g){

    //Settati alle condizioni iniziali
    linked_list_iterator* lli = linked_list_iterator_new(g->nodes);
    graph_node* n = (graph_node*)linked_list_iterator_getvalue(lli);
    for (; linked_list_iterator_hasnext(lli); n = linked_list_iterator_next(lli)) {
        n->tag = UNEXPLORED;
    }
    linked_list_iterator_delete(lli);

    //Affinchè sia sc da ogni nodo si deve poter arrivare a ogni altro nodo
    lli = linked_list_iterator_new(g->nodes);
    n = (graph_node*)linked_list_iterator_getvalue(lli);

    return 0;
}

int is_closed(graph* g){
    /*DA IMPLEMENTARE*/
    return 0;
}