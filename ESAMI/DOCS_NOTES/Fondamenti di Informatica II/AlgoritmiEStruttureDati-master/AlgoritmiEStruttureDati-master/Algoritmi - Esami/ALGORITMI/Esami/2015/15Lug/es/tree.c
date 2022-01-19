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
	print_tree_ric(n->right, depth +1);
}

void print_tree(node_tree * node) {

	print_tree_ric(node, 0);
}

int sommanodi(node* n){
    if(n == NULL) return 0;
    int l = sommanodi(n->left);
    int r = sommanodi(n->right);
    int diff;
    if(l >= r) diff = l-r;
    else diff = r-l;
    if(diff > n->key) return -1;
    printf("%d \n", l+r+n->key);
    return l + r +n->key;
}

int somma(node*n, int sum){
    if(n== NULL) return sum;
    sum= somma(n->left, sum);
    sum += n->key;
    sum = somma(n->right, sum);
    return sum;
}

int testBello(node_tree* t){
    if(t == NULL){
        return 0;
    }
    node* n = (node*) t;
    int tutti = somma(n, 0);
    int x= sommanodi(n);
    printf(" x = %d\n", x);
    if( x < tutti) return 0;
    return 1;


}
