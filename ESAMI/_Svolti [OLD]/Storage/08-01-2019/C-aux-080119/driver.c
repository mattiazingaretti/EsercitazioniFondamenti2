#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"
#include "graph_services.h"

int** read_from_stdin(int n);

void print_help() {
    printf("Manca argomento: {mat2list, is_sconn, is_closed}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}

	else if(strcmp(argv[1], "graph") == 0){
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "A");
		graph_node* b = graph_add_node(g, "B");
		graph_node* c = graph_add_node(g, "C");
		graph_node* d = graph_add_node(g, "D");
		graph_node* e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, d);
		graph_add_edge(g, c, e);
		graph_add_edge(g, e, c);
		graph_add_edge(g, c, b);

		printf("Initial graph:\n");
		graph_print(g);
		printf("\n");

		printf("Removing A -> B:\n");
		graph_remove_edge(g, a, b);
		graph_print(g);
		printf("\n");

		printf("Removing C -> E:\n");
		graph_remove_edge(g, c, e);
		graph_print(g);
		printf("\n");

		printf("Removing C:\n");
		graph_remove_node(g, c);
		graph_print(g);
		printf("\n");

		printf("Removing A:\n");
		graph_remove_node(g, a);
		graph_print(g);
		printf("\n");

		printf("Removing B:\n");
		graph_remove_node(g, b);
		graph_print(g);
		printf("\n");

		printf("Removing D:\n");
		graph_remove_node(g, d);
		graph_print(g);
		printf("\n");

		printf("Removing E:\n");
		graph_remove_node(g, e);
		graph_print(g);
		
		graph_delete(g);
	}

	else if (strcmp(argv[1], "mat2list") == 0){
		int n;
		scanf("%d", &n);
		int** mat = read_from_stdin(n);

		graph* g = mat2list(mat, n);
		graph_print(g);

		for(int i = 0; i < n; i++){
			free(mat[i]);
		}
		free(mat);
		graph_delete(g);
	}

	else if (strcmp(argv[1], "is_sconn") == 0){

		printf("######## Uno #########\n");

		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "A");
		graph_node* b = graph_add_node(g, "B");
		graph_node* c = graph_add_node(g, "C");
		graph_node* d = graph_add_node(g, "D");
		graph_node* e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, d);
		graph_add_edge(g, c, e);
		graph_add_edge(g, e, c);
		graph_add_edge(g, c, b);

		graph_print(g);
		printf("\n");

		printf("Is Strongly Connected? -> %d\n", is_strongly_connected(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "A");
		b = graph_add_node(g, "B");
		c = graph_add_node(g, "C");
		d = graph_add_node(g, "D");
		e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, a);
		graph_add_edge(g, c, e);
		graph_add_edge(g, e, c);

		printf("######## Due #########\n");
		graph_print(g);
		printf("Is Strongly Connected? -> %d\n", is_strongly_connected(g));
		printf("\n");
		graph_delete(g);

		g = graph_new();
		a = graph_add_node(g, "A");
		b = graph_add_node(g, "B");
		c = graph_add_node(g, "C");
		d = graph_add_node(g, "D");
		e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, b, a);
		graph_add_edge(g, c, e);
		graph_add_edge(g, e, c);
		graph_add_edge(g, c, b);
		graph_add_edge(g, b, c);
		graph_add_edge(g, e, d);
		graph_add_edge(g, d, e);

		printf("######## Tre #########\n");
		graph_print(g);
		printf("Is Strongly Connected? -> %d\n", is_strongly_connected(g));
		printf("\n");
		graph_delete(g);
	}

	else if (strcmp(argv[1], "is_closed") == 0){
		printf("######## Uno #########\n");
		graph* g = graph_new();
		graph_node* a = graph_add_node(g, "A");
		graph_node* b = graph_add_node(g, "B");
		graph_node* c = graph_add_node(g, "C");
		graph_node* d = graph_add_node(g, "D");
		graph_node* e = graph_add_node(g, "E");
		graph_print(g);
		printf("Is Closed? -> %d\n", is_closed(g));
		printf("\n");
		graph_delete(g);

		printf("######## Due #########\n");
		g = graph_new();
		a = graph_add_node(g, "A");
		b = graph_add_node(g, "B");
		c = graph_add_node(g, "C");
		d = graph_add_node(g, "D");
		e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, e, d);
		graph_add_edge(g, c, e);
		graph_print(g);
		printf("Is Closed? -> %d\n", is_closed(g));
		printf("\n");
		graph_delete(g);

		printf("######## Tre #########\n");
		g = graph_new();
		a = graph_add_node(g, "A");
		b = graph_add_node(g, "B");
		c = graph_add_node(g, "C");
		d = graph_add_node(g, "D");
		e = graph_add_node(g, "E");

		graph_add_edge(g, a, b);
		graph_add_edge(g, e, d);
		graph_add_edge(g, c, e);
		graph_add_edge(g, c, d);
		graph_print(g);
		printf("Is Closed? -> %d\n", is_closed(g));
		printf("\n");
		graph_delete(g);
	}

	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int** read_from_stdin(int n){
	int** to_ret = (int**) malloc(sizeof(int*) * n);
	for(int i = 0; i < n; ++i){
		to_ret[i] = (int*) malloc(sizeof(int) * n);
		for(int j = 0; j < n; ++j){
			scanf("%d", &to_ret[i][j]);
		}
	}
	return to_ret;
}