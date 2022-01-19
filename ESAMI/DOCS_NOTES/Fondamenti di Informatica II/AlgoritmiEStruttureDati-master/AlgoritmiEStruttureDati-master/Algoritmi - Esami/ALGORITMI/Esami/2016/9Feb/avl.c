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

void is_avl(node_tree* n){
    if (n==NULL){
        return;
    }
    node* nodo=n;
    int altezza=0;
    res* ris=verifica_avl_calcolo_altezza(nodo,0,altezza);
    if(ris->altezza==-1 ris->key==-1){
        printf("Albero NON è AVL\n");
    }
    else{
        printf("Albero è AVL\n");
    }
}

res* new_res(int key,int altezza){
    res* r=malloc(sizeof(res));
    r->key=key;
    r->altezza=altezza;
}

res* verifica_avl_calcolo_altezza(node* nodo, int valore, int altezza){
    if(nodo==NULL){
        return new_res(valore,0);
    }

    res* sx;
    res* dx;
    sx=verifica_avl_calcolo_altezza(nodo->left,valore,altezza);

    if(sx->key==-1 || sx->key>nodo->key){
        return new_res(-1,-1);
    }

    dx=verifica_avl_calcolo_altezza(nodo->right,nodo->key,altezza);


    if(dx->key==-1 || dx->key<nodo->key){
        return new_res(-1,-1);
    }

    if(sx->altezza<0 || dx->altezza<0){
        return new_res(-1,-1);
    }

    int diff=dx->altezza-sx->altezza;
    if(diff<-1 || diff>1){
        return new_res(-1,-1);
    }
    if(dx->altezza>=sx->altezza){
        return new_res(nodo->key,dx->altezza+1);
    }
    else{
        return new_res(nodo->key,sx->altezza+1);
    }
}
