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

BinNode* BST_insert2(BinNode* n, int k){
    if(n->key == k) return n;
    if(n->key < k){
        if(n->right != NULL) BST_insert2(n->right, k);
        else{
            BinNode* nodo = newBinNode(k);
            n->right = nodo;
            return nodo;
        }
    }
    else{
        if(n->left != NULL) BST_insert2(n->left, k);
        else{
            BinNode* nodo = newBinNode(k);
            n->left = nodo;
            return nodo;
        }
    }
}

BinNode *BST_insert(BST *t, int k) {
    /* DA IMPLEMENTARE */
    if(t->root == NULL){
        BinNode* nodo = newBinNode(k);
        t->root = nodo;
        return nodo;
    }
    BinNode* nodo = BST_insert2(t->root,k);
    return nodo;
}

int isBST2(BinNode* b, int lastmax){
    if(b == NULL) return lastmax;
    int max = isBST2(b->left, lastmax);
    if(max == -1 || max > b->key) return -1;
    return isBST2(b->right, b->key);
}

int isBST(BST *t) {
    /* DA IMPLEMENTARE */
    if(t->root == NULL) return 0;
    int x = isBST2(t->root, 0);
    if(x < 0) return 0;
    else return 1;
}

int isBalanced_aux(BinNode* b){
    if(b == NULL) return;
    int l = isBalanced_aux(b->left);
    int r= isBalanced_aux(b->right);
    if( l <0 || r < 0) return -1;
    int diff;
    if( l>= r) diff = l-r;
    else diff = r -l;
    if( diff <= 1){
        if( l>= r) return l+1;
        else return r+1;
    }
    return -1;
}

int isBalanced(BST *t) {
    /* DA IMPLEMENTARE */
    if(t->root == NULL) return 0;
    int x = isBalanced_aux(t->root);
    if(x < 0) return 0;
    else return 1;
}


