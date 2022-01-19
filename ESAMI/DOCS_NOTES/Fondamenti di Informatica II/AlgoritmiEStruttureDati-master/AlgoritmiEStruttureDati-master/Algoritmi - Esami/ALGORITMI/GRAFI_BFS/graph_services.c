#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"
#include "limits.h"
#include <stdio.h>
#include <stdlib.h>

void setUnexplored(graph* g){
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it);
        nodo->status = UNEXPLORED;
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
}

void bfs_aux(graph* g, graph_node* nodo){
    linked_list* l = linked_list_new();
    nodo->status = EXPLORED;
    linked_list_enqueue(l, nodo);
    int i=0;
    printf("%d, %s\n", i, (char*)nodo->value);
    int s = linked_list_size(l);
    linked_list_iterator* it = linked_list_iterator_new(l);
    while(linked_list_iterator_hasnext(it)){
        if(s == linked_list_size(l)) i++;
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        linked_list_iterator* it2 = linked_list_iterator_new(n->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            s++;
            graph_edge* arco = (graph_edge*) linked_list_iterator_getvalue(it2);
            if(arco->target->status == UNEXPLORED){
                printf("%d, %s\n", i, (char*)arco->target->value);
                arco->target->status = EXPLORED;
                linked_list_enqueue(l, arco->target);
            }
            arco = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        n = linked_list_iterator_next(it);
    }
    free(nodo);
    linked_list_delete(l);
    linked_list_iterator_delete(it);
    return;
}


void bfs(graph* g) {
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it);
         if(nodo->status == UNEXPLORED){
             bfs_aux(g, nodo);
         }
         nodo = linked_list_iterator_next(it);
     }
     linked_list_iterator_delete(it);
}

void single_source_shortest_path(graph* g, graph_node* source) {
    setUnexplored(g);
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    min_heap* heap = min_heap_new();
    while(linked_list_iterator_hasnext(it)){
        graph_node* n = (graph_node*) linked_list_iterator_getvalue(it);
        if( n == source) n->dist = 0;
        else n->dist = 10000;
        min_heap_insert(heap, n->dist, n);
        n = linked_list_iterator_next(it);
    }
    int i;
    for(i = 0; i < g->properties->n_vertices; i++){
        min_heap_struct_entry* e = min_heap_remove_min(heap);
        graph_node* nodo = (graph_node*) e->value;
        linked_list_iterator* it = linked_list_iterator_new(nodo->out_edges);
        while(linked_list_iterator_hasnext(it)){
            graph_edge* arco = (graph_edge*) linked_list_iterator_getvalue(it);
            graph_node* tizio = arco->target;
            if(tizio->dist == 10000 || tizio->dist > nodo->dist + arco->weight){
                tizio->dist = nodo->dist + arco->weight;
                min_heap_insert(heap, tizio->dist, tizio);
            }
            arco = linked_list_iterator_next(it);
        }
    }
    linked_list_iterator_delete(it);
    it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it);
        printf("%s %d\n", (char*) nodo->value, nodo->dist);
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    min_heap_free(heap);
}

void mst(graph* g) {
    partition* p = partition_new(6);
    min_heap* heap = min_heap_new();
    int i=0;
    linked_list_iterator* it = linked_list_iterator_new(g->nodes);
    while(linked_list_iterator_hasnext(it)){
        graph_node* nodo = (graph_node*) linked_list_iterator_getvalue(it);
        nodo->map =i;
        partition_makeset(p, i);
        i++;
        linked_list_iterator* it2 = linked_list_iterator_new(nodo->out_edges);
        while(linked_list_iterator_hasnext(it2)){
            graph_edge* arco = (graph_edge*) linked_list_iterator_getvalue(it2);
            min_heap_insert(heap, arco->weight, arco);
            arco = linked_list_iterator_next(it2);
        }
        linked_list_iterator_delete(it2);
        nodo = linked_list_iterator_next(it);
    }
    linked_list_iterator_delete(it);
    while(!(min_heap_is_empty(heap))){
        min_heap_struct_entry* e = min_heap_remove_min(heap);
        graph_edge* spigolo = (graph_edge*) e->value;
        graph_node* source = spigolo->source;
        graph_node* target = spigolo->target;
        if((partition_find(p, source->map)) != (partition_find(p, target->map))){
            int x = partition_union(p, source->map, target->map);
            source->map = x;
            target->map = x;
            printf("%s -> %s\n", (char*)source->value, (char*) target->value);
        }
    }
}
