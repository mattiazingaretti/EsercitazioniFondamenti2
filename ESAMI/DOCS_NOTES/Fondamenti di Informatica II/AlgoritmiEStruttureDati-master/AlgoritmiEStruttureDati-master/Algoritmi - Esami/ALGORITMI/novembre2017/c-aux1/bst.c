#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"


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

// altri prototipi (per funzioni locali)
static void print(BinNode *t, int level, char pos);
// fine prototipi



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

void BST_insert_aux(BinNode* b, BinNode* nodo){
    if(b->key < nodo->key){
        if(b->right != NULL) BST_insert_aux(b->right, nodo);
        else b->right = nodo;
    }
    else{
        if(b->left != NULL) BST_insert_aux(b->left, nodo);
        else b->left = nodo;
    }
}

BinNode *BST_insert(BST *t, int k) {
    /* DA IMPLEMENTARE */
    BinNode* nodo = malloc(sizeof(BinNode));
    nodo->key = k;
    nodo->right = NULL;
    nodo->left = NULL;
    if(t == NULL || t->root == NULL) t->root = nodo;
    else BST_insert_aux(t->root, nodo);
    return nodo;
}

int isBST_aux(BinNode* b, int lastmax){
    if(b== NULL) return lastmax;
    int max = isBST_aux(b->left, lastmax);
    if( max == -1 || max> b->key) return -1;
    return isBST_aux(b->right, b->key);
}

int isBST(BST *t) {
    /* DA IMPLEMENTARE */
    if(t->root == NULL) return 0;
    int x = isBST_aux(t->root, 0);
    if( x < 0) return 0;
    else return 1;
}

int isBalancedaux(BinNode* b){
    if(b == NULL) return;
    int l = isBalancedaux(b->left);
    int r = isBalancedaux(b->right);
    if( l < 0 || r < 0) return -1;
    int diff;
    if( l >= r) diff = l-r;
    else diff = r- l;
    if(diff <= 1){
        if(l>=r) return l+1;
        else return r+1;
    }
    return -1;
}

int isBalanced(BST *t) {
    /* DA IMPLEMENTARE */
    if(t->root == NULL) return 0;
    int x = isBalancedaux(t->root);
    if( x < 0) return 0;
    else return 1;
}


int isAVL(BST *t) {
    /* DA IMPLEMENTARE */
    return -1;
}
