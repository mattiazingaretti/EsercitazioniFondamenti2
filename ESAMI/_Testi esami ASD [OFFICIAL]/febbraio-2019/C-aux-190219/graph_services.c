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
	for (i=0; i<n; i++) {
		for (j=i+1; j<n; j++) {
			g->mat[i][j] = dist(points[i], points[j]);
			g->mat[j][i] = dist(points[j], points[i]);
			g->n_edges++;
		}
		g->mat[i][i] = 0;
	}
	return g;
}

graph* get_best_connections(graph* g){
	if (!g)
		return NULL;

	//Add edges to a min heap to have them sortedly stored
	min_heap* pq = min_heap_new();
	int n = g->n_vertices;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i != j) {
				int code = edge_to_code(i, j);
				min_heap_insert(pq, g->mat[i][j], code);
			}
		}
	}

	//Build MST of graph* g
	graph* MST = graph_new(n);
	partition* p = partition_new(n);

	for (int i=0; i<n; i++)
		partition_makeset(p, i);

	while (!min_heap_is_empty(pq)) {
		min_heap_struct_entry* entry = min_heap_remove_min(pq);
		int code = (int) entry->value;
		int* edge = code_to_edge(code);

		int p1 = partition_find(p, edge[0]);
		int p2 = partition_find(p, edge[1]);

		if (p1 != p2) {
			partition_union(p, p1, p2);
			MST->mat[edge[0]][edge[1]] = (double)entry->key;
			MST->mat[edge[1]][edge[0]] = (double)entry->key;
			MST->n_edges++;
		}
	}
	min_heap_free(pq);

	return MST;
}

int get_tree_height(graph* g, int v){
	/*DA IMPLEMENTARE*/
	return 0;
}