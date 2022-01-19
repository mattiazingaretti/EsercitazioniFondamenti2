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

int contaelem(node* n, int somma){
    if(n == NULL) return somma;
    somma = contaelem(n->left, somma);
    somma++;
    somma = contaelem(n->right, somma);
    return somma;
}

void inseriscielementi(int* array, node* b, int size){
    if(b== NULL) return;
    inseriscielementi(array,b->left,size);
    if(b->value <= size){
        array[b->value] = 1;
    }
    inseriscielementi(array,b->right, size);
}

int min_val(node_tree* n){
    node* b = (node*) n;
    int elem = contaelem(b, 0);
    int array[elem+1];
    int i;
    for(i = 0; i< elem+1; i++){
        array[i] = 0;
    }
    inseriscielementi(array, b, elem);
    for(i=0; i< elem+1;i++){
        if(array[i] == 0){
            return i;
        }
    }
    return elem+1;
}

