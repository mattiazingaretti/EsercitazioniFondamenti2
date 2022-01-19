#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

node_tree * new_node_tree(int info) {
	node * n = malloc(sizeof(node));
	n->value = info;
	n->left = NULL;
	n->right = NULL;

	return (node_tree *) n;
}

int get_node_info(node_tree * n) {
	return ((node *) n)->value;
}

void set_left_child(node_tree * n, node_tree * left) {
	((node *) n)->left = left;
}

node_tree * get_left_child(node_tree * n) {
	return ((node *) n)->left;
}

void set_right_child(node_tree * n, node_tree * right) {
	((node *) n)->right = right;
}

node_tree * get_right(node_tree * n) {
	return ((node *) n)->right;
}

void delete_tree(node_tree * nt) {

	if (nt == NULL)
		return;

	node * n = (node *) nt;

	// printf("Deleting node: %d\n", n->value);

	delete_tree(n->left);
	delete_tree(n->right);
	free(n);
}

void print_tree_ric(node * n, int depth) {

	if (n == NULL)
		return;

	int i;
	for (i = 0; i < depth; i++)
		printf("-");

	printf("%d\n", n->value);
	print_tree_ric(n->left, depth + 1);
	print_tree_ric(n->right, depth+1);
}

void print_tree(node_tree * node) {
	print_tree_ric(node, 0);
}


int min_val(node_tree* n){
    if(n==NULL) return -1;

    node* nodo=n;
    int num_nodi=num_nodi_albero(nodo);
    int array[num_nodi];
    inizializza_array(array,num_nodi);
    verifica_min(nodo,array,num_nodi);
    int i;
    for (i=0; i < num_nodi; i++){
        if(array[i]==0){
            return i;
        }
    }
    return num_nodi;



}

int num_nodi_albero(node*nodo){
    if(nodo==NULL){
        return 0;
    }
    return 1+num_nodi_albero(nodo->left) + num_nodi_albero(nodo->right);
}

void inizializza_array(int* array,int size){
    int i;
    for (i=0; i < size; i++){
        array[i]=0;
    }
    return;
}

void verifica_min(node *nodo,int* array, int size){
    if(nodo==NULL) return;
    if(nodo->value<size && array[nodo->value]==0){
        array[nodo->value]=1;
    }
    if(nodo->left!=NULL) verifica_min(nodo->left,array,size);
    if(nodo->right!=NULL) verifica_min(nodo->right,array,size);
}


