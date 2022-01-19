#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

struct tree {
	int key;
    void * value;
    struct tree * left;
    struct tree * right;
};

tree * build_tree_1() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->left = n3;
	n6->right = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_2() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	tree * n7 = calloc(sizeof(tree), 1);
	n7->key = 7;

	tree * n15 = calloc(sizeof(tree), 1);
	n15->key = 15;

	n6->right = n3;
	n6->left = n12;

	n3->left = n1;
	n3->right = n5;

	n12->left = n7;
	n12->right = n15;

	return n6;
}

tree * build_tree_3() {

	tree * n6 = calloc(sizeof(tree), 1);
	n6->key = 6;

	tree * n3 = calloc(sizeof(tree), 1);
	n3->key = 3;

	tree * n12 = calloc(sizeof(tree), 1);
	n12->key = 12;

	tree * n1 = calloc(sizeof(tree), 1);
	n1->key = 1;

	tree * n5 = calloc(sizeof(tree), 1);
	n5->key = 5;

	n6->left = n3;

	n3->left = n1;
	n3->right = n5;

	n5->right = n12;

	return n6;
}

void tree_delete(tree * tt) {

	tree * t = tt;
	if (t == NULL)
		return;

	tree_delete(t->left);
	tree_delete(t->right);
	free(t);
}

int tree_is_bst_aux(tree* tt, int somma){
    it(tt== NULL) return 0;
    if(tt->right == NULL && tt->left == NULL){
        return 1;
    }
    else if(tt->right == NULL){
        if(tt->key < (tt->left)->key){
            return 0;
        }
    }
    else if(tt->left == NULL){
        if(tt->key > (tt->right)->key){
            return 0;
        }
    }
    else{
        if((tt->key < (tt->left)->key) && (tt->key > (tt->right)->key)){
            return 0;
        }
    }
}

int tree_is_bst(tree * tt) {
    if(tt == NULL) return 0;
    tree_is_bst(tt->left,somma);
    tree_is_bst_aux(tt->left,somma);
    tree_is_bst(tt->right,somma);
}

int tree_is_balanced(tree * tt) {
	return 1;
}

int tree_is_avl(tree * tt) {
	return 1;
}
