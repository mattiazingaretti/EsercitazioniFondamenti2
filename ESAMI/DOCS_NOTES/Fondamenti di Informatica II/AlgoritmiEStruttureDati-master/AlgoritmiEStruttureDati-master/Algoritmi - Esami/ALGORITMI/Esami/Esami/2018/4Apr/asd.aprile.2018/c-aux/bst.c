#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


BinNode * newBinNode(int k) {
    /*OK*/
    BinNode * b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * newBST() {
    /*OK*/
    BST * b = malloc(sizeof(BST));
    b->root = NULL;

	return b;
}

static void print(BinNode *t, int level, char pos) {
    if(t == NULL) return;
    int i;
    for (i = 0; i < level - 1; i++) printf("   ");
    if (level > 0) printf(" %c:--", pos);

    printf("%d\n", t->key);
    print(t->left, level + 1, 'l');
    print(t->right, level + 1, 'r');
}

void BST_print(BST *t){
    if(t != NULL && t->root != NULL) print(t->root, 0, ' ');
}

BinNode *BST_insert(BST *t, int k) {
    /* DA IMPLEMENTARE */
    if(t==NULL) return NULL;
    BinNode* new=newBinNode(k);
    if(t->root==NULL){
        t->root=new;
        return new;
    }
    BST_insert_aux(t->root,new);
    return new;
}

void BST_insert_aux(BinNode* nodo, BinNode* new){
    if(new->key==nodo->key) return;
    else if( new->key<nodo->key){
        if(nodo->left==NULL) nodo->left=new;
        else BST_insert_aux(nodo->left,new);
    }
    else{
        if(nodo->right==NULL) nodo->right=new;
        else BST_insert_aux(nodo->right,new);
    }
}

int isBST(BST *t) {
    /* DA IMPLEMENTARE */
    if(t==NULL) return 0;
    int val=isBST_aux(t->root,0);
    if(val==-1) return 0;
    else return 1;
}

int isBST_aux(BinNode* nodo,int key){
    if(nodo==NULL) return key;

    key=isBST_aux(nodo->left,key);
    if(key>nodo->key) return -1;
    key=isBST_aux(nodo->right,nodo->key);
    if(key<nodo->key) return -1;
    return key;


}

int isBalanced(BST *t) {
    /* DA IMPLEMENTARE */
    if(t==NULL) return 0;
    int val=isBalanced_aux(t->root,0);
    if(val==-1) return 0;
    else return 1;
}

int isBalanced_aux(BinNode* nodo, int altezza){

    if(nodo==NULL) return altezza;

    int h_sx=isBalanced_aux(nodo->left,altezza);
    if(h_sx==-1) return -1;

    int h_dx=isBalanced_aux(nodo->right,altezza);
    if(h_dx==-1) return -1;

    int diff=h_sx-h_dx;
    if(diff<-1 || diff>1) return -1;

    if(h_sx>=h_dx) return h_sx+1;
    else return h_dx+1;

}




