#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

static BinNode * BST_node_new(int x, int y) {
    /*NON MODIFICARE*/
    BinNode * b = malloc(sizeof(BinNode));
	b->coordinates[0] = x;
	b->coordinates[1] = y;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * BST_new() {
    /*NON MODIFICARE*/
        BST * b = malloc(sizeof(BST));
        b->root = NULL;

	return b;
}

void BST_insert_aux(BinNode* b, BinNode* nodo, int x, int y){
    if((b->coordinates[0] < x) || ((b->coordinates[0] == x) && (b->coordinates[1] < y))){
        if(b->right != NULL) BST_insert_aux(b->right, nodo, x, y);
        else b->right = nodo;
    }
    else{
        if(b->left != NULL) BST_insert_aux(b->left, nodo, x, y);
        else b->left = nodo;
    }
}

BinNode * BST_insert(BST * b, int x, int y) {
        /*DA IMPLEMENTARE*/
        BinNode* nodo = malloc(sizeof(BinNode));
        nodo->coordinates[0] = x;
        nodo->coordinates[1] = y;
        nodo->left = NULL;
        nodo->right = NULL;
        if(b->root == NULL) b->root = nodo;
        else BST_insert_aux(b->root, nodo, x, y);
        return nodo; //istruzione aggiunta per permettere la compilazione
}


static void BST_delete_aux(BinNode * t) {
/*NON MODIFICARE*/
	if (t == NULL)
		return;

        BST_delete_aux(t->left);
        BST_delete_aux(t->right);
	free(t);
}

void BST_delete(BST * b) {
/*NON MODIFICARE*/
	if (b == NULL)
		return;

        BST_delete_aux(b->root);
        free(b);
}

void BST_print_aux(BinNode * t, int level) {
    /*MODIFICABILE*/
    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" |--");
    }

    if (t == NULL){
        printf("%c \n",35);
        return;
    }

    printf("(%d,%d)\n", t->coordinates[0],t->coordinates[1]);

    BST_print_aux(t->left, level + 1);
    BST_print_aux(t->right, level + 1);
}

void BST_print(BST * b){
    /*MODIFICABILE*/
    return BST_print_aux(b->root, 0);
}

void aligned2(BinNode* b, int x, queue* q){
    if(b == NULL) return;
    if(b->coordinates[0] == x){
        enqueue(q, (void*) b);
        aligned2(b->left, x, q);
        aligned2(b->right, x, q);}
    else if(b->coordinates[0] < x) aligned2(b->right, x, q);
    else aligned2(b->left, x, q);
}

int aligned(BST * b, int x){
        /*DA IMPLEMENTARE*/
        if( b == NULL || b->root == NULL) return 0;
        queue* q = newQueue();
        aligned2(b->root, x, q);
        if(isEmptyQueue(q)) return 0;
        return q->size; //istruzione aggiunta per permettere la compilazione
}

void rangeQ2(BinNode* b, int x1, int y1,int x2, int y2, queue* q){
    if(b == NULL) return;
    rangeQ2(b->left, x1, y1, x2, y2, q);
    int maxasc=0, minasc=0, minord=0, maxord=0;
    if(x1 < x2){
        maxasc = x2;
        minasc = x1;
    }
    else{
        maxasc = x1;
        minasc = x2;
    }
    if(y1 < y2){
        maxord = y2;
        minord = y1;}
    else{
        maxord = y1;
        minord = y2;}
    if(b->coordinates[0] >= minasc && b->coordinates[1] >= minord && b->coordinates[0] <= maxasc && b->coordinates[1] <= maxord){
        enqueue(q, (void*) b);
    }
    rangeQ2(b->right, x1, y1, x2, y2, q);
}

int rangeQ(BST * b, int x1, int y1, int x2, int y2){
        /*DA IMPLEMENTARE*/
        if(b == NULL || b->root == NULL) return 0;
        queue* q = newQueue();
        rangeQ2(b->root, x1, y1, x2, y2, q);
        if(isEmptyQueue(q)) return 0;
        return q->size; //istruzione aggiunta per permettere la compilazione
}





