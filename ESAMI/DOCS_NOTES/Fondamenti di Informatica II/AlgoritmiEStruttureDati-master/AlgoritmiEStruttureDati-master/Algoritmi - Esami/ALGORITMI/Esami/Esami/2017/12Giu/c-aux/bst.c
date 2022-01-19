#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

static BinNode * BST_node_new(int k) {
        BinNode * b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * BST_new() {
        BST * b = malloc(sizeof(BST));
        b->root = NULL;

	return b;
}


BinNode * BST_insert(BST * b, int k) {
    /*DA IMPLEMENTARE*/
     //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    if(b==NULL) return NULL;
    if(b->root==NULL){

        b->root=BST_node_new(k);
        return;
    }
    else return BST_insert_aux(b->root,k);
}

BinNode* BST_insert_aux(BinNode* nodo, int k){
    BinNode* new=BST_node_new(k);
    if(k<nodo->key){
        if(nodo->left==NULL){
            nodo->left=new;
        }
        else{
            return BST_insert_aux(nodo->left,k);
        }
    }
    else if(k>nodo->key){
        if(nodo->right==NULL){
            nodo->right=new;
        }
        else{
            return BST_insert_aux(nodo->right,k);
        }
    }
    else{
        return nodo;
    }

}


BinNode * BST_find(BST * b, int k) {
    /*DA IMPLEMENTARE*/
    //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    if(b==NULL) return NULL;
    return BST_find_aux(b->root,k);
}

BinNode* BST_find_aux(BinNode* nodo, int k){
    if(nodo==NULL) return NULL;
    if(k==nodo->key){
        return nodo;
    }
    else if(k<nodo->key){
        return BST_find_aux(nodo->left,k);
    }
    else{
        return BST_find_aux(nodo->right,k);
    }


}

static void BST_delete_aux(BinNode * t) {
	if (t == NULL)
		return;

        BST_delete_aux(t->left);
        BST_delete_aux(t->right);
	free(t);
}

void BST_delete(BST * b) {
	if (b == NULL)
		return;

        BST_delete_aux(b->root);
        free(b);
}

void BST_print_aux(BinNode * t, int level) {
	if (t == NULL)
		return;

    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" |--");
    }

    printf("%d\n", t->key);

    BST_print_aux(t->left, level + 1);
    BST_print_aux(t->right, level + 1);
}

void BST_print(BST * b){
    return BST_print_aux(b->root, 0);
}

int maxOnLevel (BST * b, int level){
    /*DA IMPLEMENTARE*/
    //questa istruzione è stata inserita per permettere la compilazione e va rimossa
    if(b==NULL) return -1;
    return maxOnLevel_aux(b->root,level,1);
}

int maxOnLevel_aux(BinNode* nodo, int level,int i){
    //~ queue q1=newQueue();
    //~ queue q2=newQueue();

    if(nodo==NULL) return -1;
    if(i==level) return nodo->key;
    int val_dx=maxOnLevel_aux(nodo->right,level,i+1);
    int val_sx=maxOnLevel_aux(nodo->left,level,i+1);

    if(val_dx>val_sx) return val_dx;
    else return val_sx;


}
