#include <stdlib.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"


void graph_init(graph* g){
  if(g == NULL)
    return;
  
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
}

void DFS(graph_node* node){

  node->key = DISCOVERY;

  linked_list_iterator* it = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->key == UNEXPLORED){
      edge->key = DISCOVERY;
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      if(opposite->key == UNEXPLORED)
	DFS(opposite);
    }
  }
  linked_list_iterator_delete(it);
}

int is_connected(graph* g){
  if(g == NULL)
    return 0;

  //Initialize each vertex and edge labels to UNEXPLORED
  graph_init(g);

  //Check if the graph is connected
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  int ret = 0;
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->key == UNEXPLORED){
      DFS(node);
      ret++;
    }
  }
  linked_list_iterator_delete(it);

  //int res = (ret == 1) ? 1 : 0;
  //printf("is_connected : %d\n", res);
  return (ret == 1) ? ret : 0;
}


int cycleDFS(graph_node* node){
  node->key = DISCOVERY;

  int ret = 0;
  linked_list_iterator* it = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->key == UNEXPLORED){
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      if(opposite->key == UNEXPLORED){
	edge->key = DISCOVERY;
	ret = cycleDFS(opposite);

	if(ret)
	  return ret;
      }else
	return 1;
    }
  }
  linked_list_iterator_delete(it);

  return ret;
}


int is_Acyclic(graph* g){
  if(g == NULL)
    return 0;

  graph_init(g);
  //Check if the graph contains cycles
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  int ret = 0;
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->key == UNEXPLORED){
      ret = cycleDFS(node);

      if(ret)
	return 0;
    }
  }
  linked_list_iterator_delete(it);
  return 1;
}




int is_tree(graph* g){

  return (is_connected(g) && is_Acyclic(g));
}

int get_size_constrained_path_aux(graph_node* start, graph_node* end, graph_node* ref,
				  int to_avoid) {

  linked_list* list = linked_list_new();
  linked_list* l2 = linked_list_new();
  int step = 1;
  
  linked_list_insert_tail(list, start);
  start->key = DISCOVERY;

  while(linked_list_size(list) > 0){

    while(linked_list_size(list) > 0){
      graph_node* node = (graph_node*) linked_list_remove_head(list);
      //printf("%s at distance %d\n", node->label, step);
      
      linked_list_iterator* it = linked_list_iterator_new(node->incident_edges);
      graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);
    
      for( ; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
	graph_node* opposite = graph_get_edge_opposite(edge, node);

	if(opposite->label == end->label)
	  return step;

	if(opposite->key == UNEXPLORED){
	  if(to_avoid && opposite->label == ref->label)
	    continue;
	    //printf("skip this vertex.\n");
	  else{
	    opposite->key = DISCOVERY;
	    linked_list_insert_tail(l2, opposite);
	  }
	}
      }
      linked_list_iterator_delete(it);
    }
    
    step++;
    list = l2;
    l2 = linked_list_new();
  }
  return -1;
}

int get_size_constrained_path(graph* g, graph_node* x, graph_node* y, graph_node* z){
  if(g == NULL)
    return -1;

  graph_init(g);
  int d1 = get_size_constrained_path_aux(x, y, z, 1);

  graph_init(g);
  int d2 = get_size_constrained_path_aux(y, z, x, 0);

  //printf("d1 : %d, d2 : %d\n", d1, d2);

  return (d1 < 0 || d2 < 0) ? -1 : d1 + d2;
}
