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

  graph* gr = graph_new();
  graph_node** storage = (graph_node**) malloc(sizeof(graph_node*)*n);
  int i;

  for(i = 0; i < n; i++){
    graph_node* node = graph_add_node(gr, char_gen(i));
    storage[i] = node;
  }
  
  int j;

  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++){
      if(g[i][j] == 1)
	graph_add_edge(gr, storage[i], storage[j]);
    }
  }

  return gr;
}


void DDFS(graph_node* node){

  node->tag = DISCOVERY;
  
  linked_list_iterator* it = linked_list_iterator_new(node->outgoing_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);

  for(; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->tag == UNEXPLORED){
      graph_node* opp = graph_get_edge_opposite(edge, node);
      edge->tag = DISCOVERY;
      
      if(opp->tag == UNEXPLORED)
	DDFS(opp);
    }
  }
  linked_list_iterator_delete(it);
}

void DDFS_transposed(graph_node* node){
  node->tag = DISCOVERY;
  
  linked_list_iterator* it = linked_list_iterator_new(node->incoming_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);

  for(; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->tag == UNEXPLORED){
      graph_node* opp = graph_get_edge_opposite(edge, node);
      edge->tag = DISCOVERY;
      
      if(opp->tag == UNEXPLORED)
	DDFS(opp);
    }
  }
  linked_list_iterator_delete(it);
}


int is_strongly_connected(graph* g){
  if(g == NULL)
    return 0;

  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  //Setting vertices's tag and edges's tag to unexplored
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->outgoing_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    node->tag = UNEXPLORED;
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
      edge->tag = UNEXPLORED;
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  //First DFS
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  int ret = 0;
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag == UNEXPLORED){
      DDFS(node);
      ret++;
    }
  }
  linked_list_iterator_delete(it);

  //if there are more than 1 connected component, the graph isn't strongly connected.
  if(ret > 1) return 0;

  //Otherwise, setting again vertices's tag and edges's tag to unexplored
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->incoming_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    node->tag = UNEXPLORED;
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
      edge->tag = UNEXPLORED;
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);

  //Second DFS
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  ret = 0;
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag == UNEXPLORED){
      DDFS_transposed(node);
      ret++;
    }
  }
  linked_list_iterator_delete(it);

  return (ret == 1) ? 1 : 0;
}

int** mat_alloc(int n){
  int ** mat = (int**) malloc(sizeof(int*)*n);
  int i;

  for(i = 0; i < n; i++)
    mat[i] = (int*) malloc(sizeof(int)*n);

  return mat;
}


int getIndex(graph_node** storage, graph_node* target, int size){

  int i = 0;

  while(i < size){
    if(storage[i] == target)
      return i;
    i++;
  }
  return -1;
}

void list2mat(graph* g, int** mat){

  //Store vertices's references in storage array
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);
  graph_node** storage = (graph_node**) malloc(sizeof(graph_node*)*g->n_nodes);
  int i;

  for(i = 0; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it), i++)
    storage[i] = node;
  linked_list_iterator_delete(it);


  //Build matrix representation for graph
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);

  for(i = 0; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it), i++){
    linked_list_iterator* iti = linked_list_iterator_new(node->outgoing_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti)){
      graph_node* opp = graph_get_edge_opposite(edge, node);
      int opp_index = getIndex(storage, opp, g->n_nodes);

      if(opp_index == -1){
	printf("[ERROR] index not found\n");
	exit(0);
      }
      
      mat[i][opp_index] = 1;
    }
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);
}


void mat_print(int** mat, int n){
  int i, j;

  for(i = 0; i < n; i++){
    for(j = 0; j < n; j++)
      printf("%d\t", mat[i][j]);
    printf("\n");
  }
}


void DFS(graph_node* node, graph_node* start, graph_node** storage, int** closure, int size){
  node->tag = DISCOVERY;

  linked_list_iterator* it = linked_list_iterator_new(node->outgoing_edges);
  graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(it);
  
  for(; linked_list_iterator_hasnext(it); edge = (graph_edge*) linked_list_iterator_next(it)){
    if(edge->tag == UNEXPLORED){
      graph_node* opp = graph_get_edge_opposite(edge, node);
      edge->tag = DISCOVERY;
      
      if(opp->tag == UNEXPLORED){
	closure[getIndex(storage, start, size)][getIndex(storage, opp, size)] = 1;
	DFS(opp, start, storage, closure, size);
      }
    }
  }
  linked_list_iterator_delete(it);
}



int mat_compare(int** m1, int** m2, int size){
  int i, j;

  for(i = 0; i < size ; i++){
    for(j = 0; j < size; j++){
      if(m1[i][j] != m2[i][j])
	return 0;
    }
  }
  return 1;
}




int is_closed(graph* g){
  if(g == NULL)
    return 0;

  int size = g->n_nodes;
  
  int ** mat = mat_alloc(size);

  list2mat(g, mat);
  printf("Equivalent matrix :\n");
  mat_print(mat, size);
  printf("\n");

  //Initialize transitive closure with graph's matrix representation
  int** closure = mat_alloc(size);
  int i, j;
  
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++)
      closure[i][j] = mat[i][j];
  }

  //Setting vertices's tag and edges's tag to unexplored 
  linked_list_iterator* it = linked_list_iterator_new(g->nodes);
  graph_node* node = (graph_node*) linked_list_iterator_getvalue(it);

  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    linked_list_iterator* iti = linked_list_iterator_new(node->outgoing_edges);
    graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
    node->tag = UNEXPLORED;
    
    for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
      edge->tag = UNEXPLORED;
    linked_list_iterator_delete(iti);
  }
  linked_list_iterator_delete(it);


  graph_node** storage = (graph_node**) malloc(sizeof(graph_node*)*size);
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  
  for(i = 0; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it), i++)
    storage[i] = node;
  linked_list_iterator_delete(it);
    


  //Build transitive closure
  it = linked_list_iterator_new(g->nodes);
  node = (graph_node*) linked_list_iterator_getvalue(it);
  
  for( ; linked_list_iterator_hasnext(it); node = (graph_node*) linked_list_iterator_next(it)){
    if(node->tag == UNEXPLORED)
      DFS(node, node, storage, closure, size);

    //Setting vertices's tag and edges's tag to unexplored 
    linked_list_iterator* it1 = linked_list_iterator_new(g->nodes);
    graph_node* node1 = (graph_node*) linked_list_iterator_getvalue(it1);

    for( ; linked_list_iterator_hasnext(it1); node1 = (graph_node*) linked_list_iterator_next(it1)){
      linked_list_iterator* iti = linked_list_iterator_new(node->outgoing_edges);
      graph_edge* edge = (graph_edge*) linked_list_iterator_getvalue(iti);
      node1->tag = UNEXPLORED;
      
      for( ; linked_list_iterator_hasnext(iti); edge = (graph_edge*) linked_list_iterator_next(iti))
	edge->tag = UNEXPLORED;
      linked_list_iterator_delete(iti);
    }
    linked_list_iterator_delete(it1);
  }
  linked_list_iterator_delete(it);

  printf("Transitive closure matrix :\n");
  mat_print(closure, size);

  return mat_compare(mat, closure, size);
}
