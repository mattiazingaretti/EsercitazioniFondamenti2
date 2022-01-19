#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        n->status = UNEXPLORED;
        n = linked_list_iterator_next(it);
    }
    free(n);
    linked_list_iterator_delete(it);
}

void bfs_aux(graph* g, graph_node* n) {
    n->status = EXPLORED;
    printf("%s\n", (char*)n->value);
    linked_list* l = linked_list_new();   //CREO UNA LISTA
    linked_list_enqueue(l, n);       //LO METTO NELLA LISTA
    linked_list_iterator* it = linked_list_iterator_new(l);
    while(linked_list_iterator_hasnext(it)){    //SCANDISCO LA LISTA
        graph_node* nn = (graph_node*)linked_list_iterator_getvalue(it);
        linked_list_iterator* it2 = linked_list_iterator_new(nn->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            graph_edge* arco = (graph_edge*)linked_list_iterator_getvalue(it2);
            graph_node* nodo = arco->target;
            if(nodo->status == UNEXPLORED){
                printf("%s\n", (char*)nodo->value);
                nodo->status = EXPLORED;
                linked_list_enqueue(l, nodo);
            }
            nodo = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        nn = linked_list_iterator_next(it);
    }
    linked_list_delete(l);
    linked_list_iterator_delete(it);
}

void bfs(graph* g){
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        if(nodo->status == UNEXPLORED){
            bfs_aux(g, nodo);
        }
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}


void single_source_shortest_path(graph* g, graph_node* source) {
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    min_heap* heap = min_heap_new();
    graph_node* nodo = (graph_node*)linked_list_iterator_getvalue(it);
    while(linked_list_iterator_hasnext(it)){
        if(nodo == source) nodo->dist = 0;
        else nodo->dist = 1000;
        min_heap_insert(heap, nodo->dist, nodo);
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    int i = 0;
    while(i < g->properties->n_vertices){
        min_heap_struct_entry* entry = min_heap_remove_min(heap);
        graph_node* n = (graph_node*)entry->value;
        it = linked_list_iterator_new(n->out_edges);
        while(linked_list_iterator_hasnext(it)){
            graph_edge* arco = (graph_edge*)linked_list_iterator_getvalue(it);
            graph_node* target = arco->target;
            if(target->dist > n->dist + arco->weight){
                target->dist = n->dist + arco->weight;
                min_heap_insert(heap, target->dist, target);
            }
            arco = linked_list_iterator_next(it);
        }
        linked_list_iterator_delete(it);
        i++;
    }
    it= linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* v = (graph_node*)linked_list_iterator_getvalue(it);
        printf("%s %d\n", (char*)v->value, v->dist);
        v = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    min_heap_free(heap);
}

void mst(graph* g) {
    setUnexplored(g);
    min_heap* heap = min_heap_new();
    int i = 0;
    partition* p = partition_new(g->properties->n_vertices);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        n->map = i;
        partition_makeset(p, i);
        i++;
        n = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nn = (graph_node*)linked_list_iterator_getvalue(it);
        nn->status = EXPLORED;
        linked_list_iterator* it2 = linked_list_iterator_new(nn->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            graph_edge* arco = (graph_edge*)linked_list_iterator_getvalue(it2);
            printf("arco %d\n", arco->weight);
            min_heap_insert(heap, arco->weight, arco);
            arco = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        nn = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    while(!(min_heap_is_empty(heap))){
        min_heap_struct_entry* entry = min_heap_remove_min(heap);
        graph_edge* arco = (graph_edge*) entry->value;
        graph_node* sorgente = arco->source;
        graph_node* destinazione = arco->target;
        if(partition_find(p, sorgente->map) != partition_find(p, destinazione->map)){
            int x = partition_union(p, sorgente->map, destinazione->map);
            sorgente->map = x;
            destinazione->map = x;
            printf("%s -> %s\n", (char*)sorgente->value,(char*)destinazione->value);
        }
    }
    min_heap_free(heap);

}
