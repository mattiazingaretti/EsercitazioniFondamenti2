#include <stdio.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = linked_list_iterator_getvalue(it);
        nodo->status = UNEXPLORED;
        nodo->timestamp = 0;
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

int sweep_aux(graph_node* n, int timestamp){
    n->status = EXPLORING;
    n->timestamp = timestamp;
    int localtime = 1;
    linked_list_iterator* it = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->status == UNEXPLORED){
            printf("(%d)%s -> (%d)%s TREE\n",n->timestamp, (char*)n->value, nodo->timestamp,(char*)nodo->value);
            localtime += sweep_aux(nodo, timestamp +1 );
        }
        else if(nodo->status == EXPLORING){
            printf("(%d)%s -> (%d)%s BACK\n", n->timestamp, (char*)n->value, nodo->timestamp, (char*)nodo->value);
        }
        else{
            if(n->timestamp >= nodo->timestamp){
              printf("(%d)%s ->(%d) %s CROSS\n", n->timestamp,(char*)n->value, nodo->timestamp, (char*)nodo->value);
            }
            else printf("(%d)%s -> (%d)%s FORWARD\n", n->timestamp,(char*)n->value,nodo->timestamp, (char*)nodo->value);
        }
        nodo = linked_list_iterator_next(it);
    }
    n->status = EXPLORED;
    linked_list_iterator_delete(it);
    return localtime;
}


void sweep(graph * g, char * format_string) {
    setUnexplored(g);
    int loctime = 0;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->status == UNEXPLORED){
            loctime += sweep_aux(nodo, loctime);
        }
        nodo = linked_list_iterator_next(it);
    }
}

int DDFS(graph_node* n, linked_list* l){
    if(n->status == EXPLORED) return 0;
    if(n->status == EXPLORING) return 1;
    int ret = 0;
    n->status = EXPLORING;
    linked_list_iterator* it = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->status == UNEXPLORED){
            ret += DDFS(nodo, l);
        }
        nodo = linked_list_iterator_next(it);
    }
    n->status = EXPLORED;
    linked_list_add(l, 0, n);
    linked_list_iterator_delete(it);
    return ret;
}

void topological_sort(graph * g){
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    linked_list* l = linked_list_new();
    graph_node* nodo = linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        if(nodo->status == UNEXPLORED){
            if(DDFS(nodo,l)){
                printf("Non può essere ordinato topologicamente");
                linked_list_iterator_delete(it);
                linked_list_delete(l);
                return;
            }
        }
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    it = linked_list_iterator_new(l);
    while(linked_list_iterator_hasnext(it)){
        char* ll = (char*)linked_list_iterator_getvalue(it);
        printf("%s \n", ll);
        ll = linked_list_iterator_next(it);
    }
    linked_list_delete(l);
    linked_list_iterator_delete(it);
}

static void transposed_DDFS(graph* g, graph_node * node, linked_list* list) {
	if (node->status != UNEXPLORED)
		return;
	node->status = EXPLORING;
	linked_list_iterator* it = linked_list_iterator_new(g->nodes);      //SCANDISCO I NODI DEL GRAFO
	graph_node* to = (graph_node*)linked_list_iterator_getvalue(it);     //PRENDO UN NODO
	while(linked_list_iterator_hasnext(it)) {
		linked_list_iterator* it2 = linked_list_iterator_new(to->out_edges);    //SCANDISCO I SUOI VICINI
		graph_node* frm = (graph_node*)linked_list_iterator_getvalue(it2);
		while(linked_list_iterator_hasnext(it2)) {
			if (frm == node){                        //QUANDO TRA I VICINI DI UN NODO A CASO NEL GRAFO E' UGUALE A QUELLO CHE HA CHIAMATO LA DFS, LA RICHIAMO
				transposed_DDFS(g, to, list);
            }
            frm = linked_list_iterator_next(it2);
		}
		linked_list_iterator_delete(it2);
        to = linked_list_iterator_next(it);
	}
	linked_list_iterator_delete(it);
	linked_list_enqueue(list, node);
	node->status = EXPLORED;
}

void strong_connected_components(graph  *g) {
    setUnexplored(g);  //SET UNEXPLORED
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    linked_list* l = linked_list_new();
    graph_node* nodo = linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        if(nodo->status == UNEXPLORED){  //PRIMA DDFS E CREO LISTA
            DDFS(nodo, l);
        }
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    setUnexplored(g);           //SET UNEXPLORED
    it = linked_list_iterator_new(l);   //SECONDA DDFS MA SECONDO L'ORDINE DELLA LISTA PRECEDENTE
    nodo = (graph_node*) linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        if(nodo->status == UNEXPLORED){
            linked_list* ret = linked_list_new();   //Mi creo una nuova lista
			transposed_DDFS(g, nodo, ret);              //chiamo la DDFS sul grafo traposto in modo da poter salvare i nodi sulla lista
			linked_list_iterator *it2 = linked_list_iterator_new(ret);    //scandisco la lista
			graph_node* cur = (graph_node*)linked_list_iterator_getvalue(it2);
			printf("Strong connected component:\n");                  //stampo i nodi della lista = nodi della comp fortemente connessa
			for (; linked_list_iterator_hasnext(it2); cur = linked_list_iterator_next(it2)) {
				printf("%s ", (char*)(cur->value));
			}
			printf("\n");
			linked_list_iterator_delete(it2);
			linked_list_delete(ret);
		}
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    linked_list_delete(l);
}
