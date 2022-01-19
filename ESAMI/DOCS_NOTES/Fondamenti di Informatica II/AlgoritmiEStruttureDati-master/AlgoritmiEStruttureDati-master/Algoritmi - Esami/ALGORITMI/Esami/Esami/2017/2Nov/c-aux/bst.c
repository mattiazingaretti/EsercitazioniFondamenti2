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
    for (int i = 0; i < level - 1; i++) printf("   ");
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
    return NULL;
}

int isBST(BST *t) {
    /* DA IMPLEMENTARE */
    return -1;
}


int isBalanced(BST *t) {
    /* DA IMPLEMENTARE */
    return -1;
}


int isAVL(BST *t) {
    /* DA IMPLEMENTARE */
    return -1;
}