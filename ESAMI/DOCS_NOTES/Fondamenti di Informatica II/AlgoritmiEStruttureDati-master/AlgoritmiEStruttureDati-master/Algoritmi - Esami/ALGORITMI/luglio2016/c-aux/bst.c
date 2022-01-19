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

void BST_insert_aux(BinNode* b , BinNode* nodo){
    if(b->key >nodo->key){
        if(b->left != NULL) BST_insert_aux(b->left, nodo);
        else b->left = nodo;
    }
    else{
        if(b->right != NULL) BST_insert_aux(b->right, nodo);
        else b->right = nodo;
    }
}

BinNode * BST_insert(BST * b, int k) {
    /*DA IMPLEMENTARE*/
    BinNode* nodo = malloc(sizeof(BinNode));
    nodo->key = k;
    nodo->left = NULL;
    nodo->right = NULL;
    if(b->root == NULL) b->root = nodo;
    else{
        BST_insert_aux(b->root, nodo);
    }
    b->size ++;
    return nodo; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
}

BinNode* BST_find2(BinNode* b ,int k){
    if(b == NULL) return NULL;
    if(b->key > k){
        BST_find2(b->left, k);
    }
    else if( b->key == k) return b;
    else{
        BST_find2(b->right, k);
    }
}

BinNode * BST_find(BST * b, int k) {
    /*DA IMPLEMENTARE*/
    if(b == NULL || b->root == NULL) return;
    BinNode* nodo = BST_find2(b->root, k);
    return nodo; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
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

void BST_print2(BinNode* nodo){
    if(nodo == NULL) return;
    BST_print2(nodo->left);
    printf(" %d", nodo->key);
    BST_print2(nodo->right);
}

void maxOnLevel2(BinNode* b, int level, int corr, queue* s){
    if(b == NULL) return;
    if( corr == level){
        enqueue(s,(void*) b);
        return;
    }
    maxOnLevel2(b->left, level, corr+1, s);
    maxOnLevel2(b->right, level, corr+1, s);
}

int maxOnLevel (BST * b, int level){
    /*DA IMPLEMENTARE*/
    int max= 0;
    if( b == NULL || b->root == NULL) return -1;
    queue* s = newQueue();
    maxOnLevel2(b->root, level, 1, s);
    if(isEmptyQueue(s)) return -1;
    int i;
    queueItem* q = s->head;
    for(i = 0; i< s->size; i++){
        BinNode* nodo = (BinNode*)q->item;
        if(nodo->key > max) max = nodo->key;
        q = q->next;
    }
    return max; //questa istruzione è stata inserita per permettere la compilazione e va rimossa
}

int inseriscielementi(BinNode* b, int* array, int i){
    if(b== NULL) return 0;
    int x = inseriscielementi(b->left, array, i);
    array[x] = b->key;
    i++;
    inseriscielementi(b->right, array,i);
    return i;
}

int sottoinsieme(BST* b1, BST* b2){
    //int array1[b1->size];
    //int array2[b2->size];
    //inseriscielementi(b1->root, array1, 0);
    //inseriscielementi(b2->root, array2, 0);
    int array1[8];
    int array2[3];
    array1[0] = 1;
    array1[1] = 2;
    array1[2] = 3;
    array1[3] = 4;
    array1[4] = 5;
    array1[5] = 6;
    array1[6] = 7;
    array1[7] = 8;
    array2[0] = 1;
    array2[1] = 5;
    array2[2] = 8;
    array2[3] = 9;
    int i;
    int j=0;
        for(i=0; i < 8; i++){
            if(array2[j] == array1[i]) j++;
        }
        if(j < 4) return 0;
        return 1;
}

