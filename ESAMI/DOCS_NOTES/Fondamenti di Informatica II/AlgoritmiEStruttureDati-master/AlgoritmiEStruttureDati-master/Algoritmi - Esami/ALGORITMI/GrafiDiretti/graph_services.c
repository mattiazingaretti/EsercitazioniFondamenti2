#include <stdio.h>

#include "graph.h"
#include "linked_list.h"
#include "graph_services.h"

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*)linked_list_iterator_getvalue(it);
        n->status = UNEXPLORED;
        n->timestamp =0;
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

int DFS(graph_node* n, int timestamp){
    n->status = EXPLORING;
    n->timestamp = timestamp;
    timestamp++;
    linked_list_iterator* it = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node * cur = (graph_node*)linked_list_iterator_getvalue(it);
        if(cur->status == UNEXPLORED){
            printf("%s (%d) -> %s (%d) TREE\n", (char*)n->value, n->timestamp, (char*) cur->value, (cur->timestamp)++);
            DFS(cur, timestamp);
        }
        else if(cur->status == EXPLORING){
            printf("%s (%d) -> %s (%d) BACK\n", (char*)n->value, n->timestamp, (char*) cur->value, (cur->timestamp)++);
        }
        else if(cur->status == EXPLORED){
            if(cur->timestamp > n->timestamp){
                printf("%s (%d) -> %s(%d) FORWARD\n", (char*)n->value, n->timestamp, (char*) cur->value, (cur->timestamp)++);
            }
            else printf("%s(%d) -> %s(%d) CROSS\n", (char*)n->value, n->timestamp, (char*) cur->value, (cur->timestamp)++);
        }
        cur = linked_list_iterator_next(it);
    }
    n->status = EXPLORED;
    linked_list_iterator_delete(it);
    return timestamp;
}

void sweep(graph * g, char * format_string) {
    setUnexplored(g);
    int timestamp = 0;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node * cur = (graph_node*)linked_list_iterator_getvalue(it);
        if(cur->status == UNEXPLORED){
            timestamp = DFS(cur, timestamp);
        }
        cur = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

int topological_DFS(graph* g, graph_node* n, linked_list* l){
    n->status = EXPLORING;
    int ret = 0;
    //linked_list_enqueue(l, (void*) n->value);
    linked_list_iterator* it = linked_list_iterator_new(n->out_edges);
    while(linked_list_iterator_hasnext(it)){
        graph_node * cur = (graph_node*)linked_list_iterator_getvalue(it);
        if(cur->status == UNEXPLORED){
            ret += topological_DFS(g, cur, l);
        }
        else if(cur->status == EXPLORING) return 1;
        cur = linked_list_iterator_next(it);
    }
    n->status = EXPLORED;
    printf("nodo %s\n", (char*) n->value);
    linked_list_add(l, 0, n);
    linked_list_iterator_delete(it);
    return ret ;
}

void topological_sort(graph * g){
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    linked_list* l = linked_list_new();
    while( linked_list_iterator_hasnext(it)){
        graph_node* n = linked_list_iterator_getvalue(it);
        if(n->status == UNEXPLORED){
           if(topological_DFS(g, n, l)){
               printf("Impossibile ordinare topologicamnte \n");
               linked_list_iterator_delete(it);
              linked_list_delete(l);
              return;
        }
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator* it2 = linked_list_iterator_new(l);
    int i =1;
    while( linked_list_iterator_hasnext(it2)){
        graph_node* nodo = linked_list_iterator_getvalue(it2);
        printf("%d %s\n", i, (char*) nodo->value);
        i++;
        nodo = linked_list_iterator_next(it2);
    }
    linked_list_iterator_delete(it2);
    linked_list_iterator_delete(it);
    linked_list_delete(l);
}

void strong_connected_components(graph  *g) {
    setUnexplored(g);
    graph* trasposto = graph_new();
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nn = (graph_node*)linked_list_iterator_getvalue(it);
        graph_add_node(trasposto, nn->value);
        nn= linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    linked_list_iterator* i = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(i)){
        linked_list* lista = linked_list_new();
        graph_node* n = (graph_node*)linked_list_iterator_getvalue(i);
        linked_list_enqueue(lista, (void*) n);
        linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            graph_node* nodo = (graph_node*)linked_list_iterator_getvalue(it2);
            linked_list_enqueue(lista,(void*) nodo);
            nodo = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        int x;
        printf("size lista %d\n", linked_list_size(lista));
        for(x= 1; x < linked_list_size(lista); x++){
            graph_node* agg = (graph_node*)linked_list_get(lista, x);
            graph_add_edge(trasposto, agg, n);
            printf("Aggiunto arco %s -> %s\n", (char*) agg->value, (char*) n->value);
        }
        linked_list_delete(lista);
        n = linked_list_iterator_next(i);
    }
    graph_print(trasposto);
    linked_list_iterator_delete(i);
    graph_delete(trasposto);
}

