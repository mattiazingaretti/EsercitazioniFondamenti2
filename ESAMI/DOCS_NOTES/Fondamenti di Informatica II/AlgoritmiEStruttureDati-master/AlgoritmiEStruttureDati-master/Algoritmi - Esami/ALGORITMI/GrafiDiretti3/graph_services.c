#include <stdio.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*)linked_list_iterator_getvalue(it);
        n->status = UNEXPLORED;
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

int sweep_aux(graph_node* n, int time){
    n->status = EXPLORING;
    n->timestamp = time;
    int loctime = 1;
    linked_list_iterator* it = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = linked_list_iterator_getvalue(it);
        if(nodo->status == UNEXPLORED){
            printf("%s(%d) -> %s(%d) TREE\n", (char*)n->value, n->timestamp, (char*) nodo->value, nodo->timestamp);
            time++;
            loctime += sweep_aux(nodo, time);
        }
        else if(nodo->status == EXPLORING){
            printf("%s(%d) -> %s(%d) BACK\n", (char*)n->value, n->timestamp, (char*) nodo->value, nodo->timestamp);
        }
        else{
            if(nodo->timestamp > n->timestamp){
                printf("%s(%d) -> %s(%d) FORWARD\n", (char*)n->value, n->timestamp, (char*) nodo->value, nodo->timestamp);
            }
            else printf("%s(%d) -> %s(%d) CROSS\n", (char*)n->value, n->timestamp, (char*) nodo->value, nodo->timestamp);
        }
        nodo = linked_list_iterator_next(it);
    }
    n->status = EXPLORED;
    linked_list_iterator_delete(it);
    return loctime;
}

void sweep(graph * g, char * format_string) {
    setUnexplored(g);
    int time = 0;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        if(n->status == UNEXPLORED){
            time += sweep_aux(n, time);
        }
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

int topologicalDFS(graph_node* nodo, linked_list* l){
    if(nodo->status == EXPLORING) return 1;
    else if(nodo->status == EXPLORED) return 0;
    int ret = 0;
    nodo->status = EXPLORING;
    linked_list_iterator* it = linked_list_iterator_new(nodo->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        ret += topologicalDFS(n, l);
        n= linked_list_iterator_next(it);
    }
    nodo->status = EXPLORED;
    linked_list_add(l, 0, nodo);
    linked_list_iterator_delete(it);
    return ret;
}

void topological_sort(graph * g){
    setUnexplored(g);
    linked_list* l = linked_list_new();
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        if(n->status == UNEXPLORED){
            if(topologicalDFS(n, l)){
                printf("ERRORE: non è possibile ordinare topologicamente poichè non aciclico\n");
                linked_list_iterator_delete(it);
                linked_list_delete(l);
                return;
            }
        }
        n= linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    it = linked_list_iterator_new(l);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nome = linked_list_iterator_getvalue(it);
        printf("%s\n", (char*) nome->value);
        nome = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    linked_list_delete(l);
}


void DDFStrasposta(graph* g, graph_node* n, linked_list* l){
    if(n->status != UNEXPLORED) return;
    n->status = EXPLORED;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nn = (graph_node*) linked_list_iterator_getvalue(it);
        linked_list_iterator* it2 = linked_list_iterator_new(nn->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it2);
            if(nodo == n){
                DDFStrasposta(g, nn, l);
            }
            nodo = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        nn = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    linked_list_enqueue(l,n->value);
}

void strong_connected_components(graph  *g) {
    setUnexplored(g);
    linked_list* l = linked_list_new();
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        if(n->status == UNEXPLORED){
            topologicalDFS(n,l);
        }
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    setUnexplored(g);
    it = linked_list_iterator_new(l);
    while(linked_list_iterator_hasnext(it)){
        linked_list* lista = linked_list_new();
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        if(n->status == UNEXPLORED){
            DDFStrasposta(g, n, lista);
            linked_list_iterator* it2 = linked_list_iterator_new(lista);
            printf("Nuova componente fortemente connessa:\n");
            while(linked_list_iterator_hasnext(it2)){
                void* nome = linked_list_iterator_getvalue(it2);
                printf("%s\n", (char*) nome);
                nome = linked_list_iterator_next(it2);
            }
            linked_list_iterator_delete(it2);
        }
        linked_list_delete(lista);
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    linked_list_delete(l);
}
