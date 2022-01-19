#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

typedef struct tree{
    int info;
    struct tree* firstchild;
    struct tree* nextsibling;
}tree;

node_tree * new_node_tree(int info) {
    tree* nodo = malloc(sizeof(tree));
    nodo->info = info;
    nodo-> firstchild = NULL;
    nodo-> nextsibling = NULL;
	return (node_tree*)nodo;
}

int get_node_info(node_tree * n) {
    tree* nodo = (tree*)n;
    int i = nodo->info;
	return i;
}

void set_first_child(node_tree * n, node_tree * first_child) {
    tree* nodo = (tree*)n;
    tree* figlio = first_child;
    nodo->firstchild = figlio;
	return;
}

node_tree * get_first_child(node_tree * n) {
    tree* nodo =(tree*) n;
    tree* figlio = nodo->firstchild;
	return (node_tree*)figlio;
}

void set_next_sibling(node_tree * n, node_tree * next_sibling) {
    tree* nodo = (tree*)n;
    tree* fratello = next_sibling;
    nodo->nextsibling = fratello;
	return;
}

node_tree * get_next_sibling(node_tree * n) {
    tree* nodo = (tree*)n;
    tree* fratello = nodo->nextsibling;
	return (node_tree*)fratello;
}

void delete_tree(node_tree * nt) {
    if(nt == NULL) return;
    tree* n = (tree*) nt;
    delete_tree((node_tree*) n->firstchild);
    delete_tree((node_tree*) n->nextsibling);
    free(n);
	return;
}

void print_tree2(tree* node, int livello){
    if(node == NULL) return;
    int i;
    for(i=0; i< livello; i ++){
        printf("-");
    }
    printf("%d\n", node->info);
    print_tree2(node->firstchild, livello +1);
    print_tree2(node->nextsibling, livello);
}

void print_tree(node_tree * node) {
    if(node == NULL) return;
    tree* n = (tree*) node;
    print_tree2( n , 0);
	return;
}
