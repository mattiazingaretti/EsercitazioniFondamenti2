#include "graph_services.h"
#include "min_heap.h"
#include "partition.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist(point* p1, point* p2){
	double dx = p1->x - p2->x;
	double dy = p1->y - p2->y;
	return sqrt((dx*dx) + (dy*dy));
}

int edge_to_code(int x, int y){
	if(y < x){
		int z = y;
		y = x;
		x = z;
	}
    return (int)((x*100) + y);
}

int* code_to_edge(int x){
    int* ret = (int*) malloc(sizeof(int) * 2);
    double tmp = x/100.;
    ret[0] = (int)(tmp);
    ret[1] = (int)((tmp - ret[0])*100);
    return ret;
}

graph* make_graph(point** points, int n){
  graph* g = graph_new(n);
  int i, j;

  for(i = 0; i < n; i++){
    for(j = i+1; j < n; j++){
	g->mat[i][j] = dist(points[i], points[j]);
	g->mat[j][i] = dist(points[j], points[i]);
	(g->n_edges)++;
    }
    g->mat[i][i] = 0;
  }
  return g;
}

graph* get_best_connections(graph* g){
  if(g == NULL)
    return NULL;

  //Sort edges by their weights
  min_heap* mh = min_heap_new();
  int i, j, size = g->n_vertices;
 
  for(i = 0;  i < size; i++){
    for(j = i+1; j < size; j++){
      if(g->mat[i][j] != (double) -1){
	int etc = edge_to_code(i, j);
	min_heap_insert(mh, g->mat[i][j], etc);
      }
    }
  }

  //Build mst of graph g
  graph* mst = graph_new(g->n_vertices);
  partition* p = partition_new(g->n_vertices);
  
  for(i = 0; i < size; i++)
    partition_makeset(p, i);
  
  while(min_heap_size(mh) > 0){
    min_heap_struct_entry* mhe = min_heap_remove_min(mh);
    int etc = (int) mhe->value;
    int* edge = code_to_edge(etc);

    // printf("(%d,%d) : %lf\n", edge[0], edge[1], (double) mhe->key);

    int id1 = partition_find(p, edge[0]);
    int id2 = partition_find(p, edge[1]);

    if(id1 != id2){
      partition_union(p, id1, id2);
      mst->mat[edge[0]][edge[1]] = g->mat[edge[0]][edge[1]];
      mst->mat[edge[1]][edge[0]] = g->mat[edge[1]][edge[0]];
      (mst->n_edges)++;
    }
  }
  min_heap_free(mh);
  
  return mst;
}

int get_tree_height_aux(graph* g, int** paths, int root){
  int size = g->n_vertices;
  int j, res = 1;
  
  for(j = 0; j < size; j++){
    if((int) g->mat[root][j] != -1 && paths[root][j]  == 0){
      paths[root][j] = 1;
      paths[j][root] = 1;
      int ret = 1 + get_tree_height_aux(g, paths, j);
      if(ret > res)
	res = ret;
    }
  }
  return res;
}


int get_tree_height(graph* g, int v){
  if(g == NULL)
    return 0;

  int i, j, size = g->n_vertices;
  int** paths = (int**) malloc(sizeof(int*)*size);
 

  for(i = 0; i < size; i++)
    paths[i] = (int*) malloc(sizeof(int)*size);

  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++)
      paths[i][j] = 0;
  }
  
  return get_tree_height_aux(g, paths, v);
}
