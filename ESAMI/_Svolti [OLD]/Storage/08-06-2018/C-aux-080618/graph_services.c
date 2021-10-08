#include <stdlib.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"

linked_list * graph_get_edges(graph * g){
  if(g == NULL)
    return NULL;
  
  //Setting edge's keys to unexplored
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
      edge->key = UNEXPLORED;
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  //Insert graph's edges in a linked list
  linked_list* storage = linked_list_new();
  
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      if(edge->key == UNEXPLORED){
	edge->key = DISCOVERY;
	linked_list_insert_tail(storage, edge);
      }
    }
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);

  return storage;
}


void DFS(graph_node* node) {

  node->key = DISCOVERY;

  linked_list_iterator* it = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);
    
  for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->key == UNEXPLORED){
      graph_node* opp = graph_get_edge_opposite(edge, node);

      if(opp->key == UNEXPLORED){
	edge->key = DISCOVERY;
	DFS(opp);
      }
    }
  }
  linked_list_iterator_delete(it);
}


int graph_is_connected(graph * g){
  if(g == NULL)
    return 0;

   //Setting vertices's and edge's keys to unexplored
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    node->key = UNEXPLORED;
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
      edge->key = UNEXPLORED;
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  //Check if the graph is connected
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  int ret = 0;

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->key == UNEXPLORED){
      DFS(node);
      ret++;
    }
  }
  linked_list_iterator_delete(it);

  return (ret == 1) ? 1 : 0;
}

int graph_is_1_connected(graph * g){
  if(g == NULL)
    return 0;

  if(!graph_is_connected(g))
    return 0;
  
  //Check if the graph is 1 connected
  linked_list* edges = graph_get_edges(g);
  linked_list_iterator* it = linked_list_iterator_new(edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    graph_remove_edge(g, edge->n1, edge->n2);

    if(!graph_is_connected(g)){
      graph_add_edge(g, edge->n1, edge->n2);
      linked_list_iterator_delete(it);
      return 1;
    }
    graph_add_edge(g, edge->n1, edge->n2);
  }
  linked_list_iterator_delete(it);
  
  return 0;
}
