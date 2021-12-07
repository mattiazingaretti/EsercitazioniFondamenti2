#include <stdlib.h>

#include "graph_services.h"
#include "graph.h"
#include "linked_list.h"


int DFS(graph_node* node){
  
  node->tag = DISCOVERY;

  int ret = 1;
  linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);

  for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
    if(edge->tag == UNEXPLORED){
      edge->tag = DISCOVERY;
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      if(opposite->tag == UNEXPLORED){
	ret = DFS(opposite);
      }	
    }
  }
  linked_list_iterator_delete(iti);
  return ret;
}

int conn_comp(graph* g){
  if(g == NULL)
    return 0;

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  //Initialize each node and edge to UNEXPLORED
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag != UNEXPLORED)
      node->tag = UNEXPLORED;
    
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);

    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      if(edge->tag != UNEXPLORED)
	edge->tag = UNEXPLORED;
    }
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  //Now, count connected components of graph
  int ret = 0;
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag == UNEXPLORED){
      //printf("Call DFS.\n");
      ret += DFS(node);
    }
  }
  linked_list_iterator_delete(it);

  return ret;  
}

void contract(graph* g){
  if(g == NULL)
    return;

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    
    //Se deg(node) = 2, allora verifica se è possibile effettuare una contrazione
    if(linked_list_size(node->incident_edges) == 2){
      graph_edge* e1 = (graph_edge*) node->incident_edges->head->value;
      //printf("(%s, %s)\n", e1->n1->label, e1->n2->label);
      graph_edge* e2 = (graph_edge*) node->incident_edges->head->next->value;

      graph_node* u = graph_get_edge_opposite(e1, node);
      graph_node* w = graph_get_edge_opposite(e2, node);

      //Controllo se è presente un arco (u, w)
      linked_list_iterator* iti = linked_list_iterator_new(u->incident_edges);
      graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
      int to_contract = 1;
      
      for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
	graph_node* opp = graph_get_edge_opposite(edge, u);
	if(opp == w)
	  to_contract = 0;
      }
      linked_list_iterator_delete(iti);

      if(to_contract){
	graph_add_edge(g, u, w);
	graph_remove_edge(g, node, u);
	graph_remove_edge(g, node, w);
	graph_remove_node(g, node);
      }
    }
  }
  linked_list_iterator_delete(it);
}

int isContained(graph_node* from, graph_node* to){

  linked_list_iterator* iti = linked_list_iterator_new(from->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
  
  for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
    graph_node* opp = graph_get_edge_opposite(edge, from);
    if(opp == to)
      return 1;
  }
  linked_list_iterator_delete(iti);

  return 0;
}


int getCompleteSubgraph(graph_node* node){

  //printf("current node : %s\n", node->label);
  
  linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
  int found = 0;

  graph_node** neighbors = (graph_node**) malloc(sizeof(graph_node*)*linked_list_size(node->incident_edges));
  int i;
  
  for(i = 0; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti), i++)
    neighbors[i] = graph_get_edge_opposite(edge, node);
  linked_list_iterator_delete(iti);


  int j = linked_list_size(node->incident_edges);
  int k;
  
  for(i = 0; i < j; i++){
    for(k = i + 1; k < j; k++){
	if(neighbors[i]->tag != EXCLUDED && neighbors[k]->tag != EXCLUDED){
	  if(isContained(neighbors[i], neighbors[k]) && isContained(neighbors[k], neighbors[i]))
	    found++;
	}
    }
  }
  
  return found;
}



/*
int getCompleteSubgraph(graph_node* node, int step, graph_node* start){

  //printf("current node : %s\n", node->label);
  
  linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
  int found = 0;
  
  for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
    if(step < 2){
	graph_node* opposite = graph_get_edge_opposite(edge, node);

	if(edge->tag == UNEXPLORED){
	  edge->tag = DISCOVERY;
	  if(opposite->tag != EXCLUDED)
	    found += getCompleteSubgraph(opposite, step + 1, start);
	}
    }else{
      graph_node* opposite = graph_get_edge_opposite(edge, node);
      //printf("(%s,%s)\n", opposite->label, node->label);
      
      if(opposite == start){
	//printf("start : %s, opposite : %s\n", start->label, opposite->label);
	return 1;
      }
    }
  }
  linked_list_iterator_delete(iti);  
  
  return found;
}
*/


int count_k3(graph* g){
  if(g == NULL)
    return 0;

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  
  //Initialize each node and edge to UNEXPLORED
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag != UNEXPLORED)
      node->tag = UNEXPLORED;
    
    linked_list_iterator* iti = linked_list_iterator_new(node->incident_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      if(edge->tag != UNEXPLORED)
	edge->tag = UNEXPLORED;
    }
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  int ret = 0;
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag != EXCLUDED){
      node->tag = EXCLUDED;
      ret += getCompleteSubgraph(node);
      //printf("Call terminated.\n");


      linked_list_iterator* it1 = linked_list_iterator_new(g->nodes);
      graph_node* node = (graph_node*) linked_list_iterator_getvalue(it1);
      
      //Initialize each node and edge to UNEXPLORED
      for( ; linked_list_iterator_hasnext(it1); node = (graph_node*) linked_list_iterator_next(it1)){
 
	linked_list_iterator* it2 = linked_list_iterator_new(node->incident_edges);
	graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it2);
	
	for( ; linked_list_iterator_hasnext(it2); edge = (graph_edge*) linked_list_iterator_next(it2)){
	  if(edge->tag != UNEXPLORED)
	    edge->tag = UNEXPLORED;
	}
	linked_list_iterator_delete(it2);
      }
      linked_list_iterator_delete(it1);
    }
  }
  linked_list_iterator_delete(it);

  return ret;
}
