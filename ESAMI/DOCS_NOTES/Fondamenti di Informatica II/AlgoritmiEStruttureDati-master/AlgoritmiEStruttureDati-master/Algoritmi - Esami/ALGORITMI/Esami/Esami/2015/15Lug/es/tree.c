#include <stdlib.h>
#include <stdio.h>

#include "tree.h"



node_tree * new_node_tree(int info) {
	node * n = malloc(sizeof(node));
	n->key = info;
	n->right=NULL;
	n->left = NULL;

	return (node_tree *) n;
}

int get_node_info(node_tree * n) {
	return ((node *) n)->key;
}

void set_right_child(node_tree * n, node_tree * right) {
	((node *) n)->right= right;
}

node_tree * get_right_child(node_tree * n) {
	return ((node *) n)->right;
}

void set_left_child(node_tree * n, node_tree * left) {
	((node *) n)->left = left;
}

node_tree * get_left_child(node_tree * n) {
	return ((node *) n)->left;
}

void delete_tree(node_tree * nt) {

	if (nt == NULL)
		return;

	node * n = (node *) nt;

	// printf("Deleting node: %d\n", n->value);

	delete_tree(n->right);
	delete_tree(n->left);
	free(n);
}

void print_tree_ric(node * n, int depth) {

	if (n == NULL)
		return;

	int i;
	for (i = 0; i < depth; i++)
		printf("-");

	printf("%d\n", n->key);
	print_tree_ric(n->left, depth + 1);
	print_tree_ric(n->right, depth);
}

void print_tree(node_tree * node) {

	print_tree_ric(node, 0);
}

int testBello(node_tree* n){
    if(n==NULL){
        return 0;
    }
    node* nodo=n;
    int ver=verifica(nodo);
    if(ver==-1){
        return 0;
    }
    else{
        return 1;
    }
}

int verifica(node* nodo){
    int somma_dx=0;
    int somma_sx=0;
    int mia_somma = 0;

    if(nodo == NULL)
        return 0;

    mia_somma=nodo->key;

    somma_sx=verifica(nodo->left);
    if(somma_sx==-1){
        return -1;
    }

    somma_dx=verifica(nodo->right);
    if(somma_dx==-1){
        return -1;
    }

    int diff=somma_sx - somma_dx;
    if(diff<0) diff=-diff;
    if(mia_somma>= diff){
        return mia_somma+somma_dx+somma_sx;
    }
    else{
        return -1;
    }


}
