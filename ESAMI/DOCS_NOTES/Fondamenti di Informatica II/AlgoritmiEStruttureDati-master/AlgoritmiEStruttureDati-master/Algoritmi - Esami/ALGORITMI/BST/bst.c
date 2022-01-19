#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

#define MAGGIORE 1
#define MINORE 2

typedef struct bst_node{
    int key;
    void* value;
    struct bst_node* left;
    struct bst_node* right;
}bst_node;

struct bst{
    bst_node* root;
};

bst_node* crea_nodo(int k, void * v){

    bst_node* my_nodo = (bst_node*)malloc(sizeof(bst_node));
    my_nodo->value = v;
    my_nodo->key = k;
    my_nodo->right = NULL;
    my_nodo->left = NULL;

    return my_nodo;
}

bst * bst_new(int k, void * v) {

    bst* my_bst = (bst*)malloc(sizeof(bst));
    my_bst->root = crea_nodo(k, v);

	return my_bst;
}

void my_bst_insert(bst_node* padre, bst_node* figlio, int k, void * v, int index){

    if(figlio == NULL){
        if(index == MAGGIORE)
            padre->right = crea_nodo(k,v);
        else
            padre->left = crea_nodo(k,v);

        return;
    }

    if(figlio->key == k){
        figlio->value = v;
        return;
    }

    else if(k > figlio->key)
        my_bst_insert(figlio, figlio->right, k, v, MAGGIORE);

    else
        my_bst_insert(figlio, figlio->left, k, v, MINORE);
}

void bst_insert(bst * b, int k, void * v) {

    bst_node* padre = b->root;
    bst_node* figlio = NULL;

    if(padre->key == k){
        padre->value = v;
        return;
    }

    if(k > padre->key){
        figlio = padre->right;
        my_bst_insert(padre, figlio, k, v, MAGGIORE);
    }
    else{
        figlio = padre->left;
        my_bst_insert(padre, figlio, k, v, MINORE);
    }

    return;

}

void * my_bst_find(bst_node* nodo_padre, int k){

    if(nodo_padre == NULL)
        return NULL;

    if(nodo_padre->key == k)
        return nodo_padre->value;

    else if(k > nodo_padre->key)
        return my_bst_find(nodo_padre->right, k);

    else
        return my_bst_find(nodo_padre->left, k);
}

void * bst_find(bst * b, int k) {

    bst_node* nodo = b->root;

    return my_bst_find(nodo, k);
}

int bst_find_min(bst * b) {
	return 0;
}

void bst_remove_min(bst * b) {
	return;
}

void bst_remove(bst * b, int k) {
	return;
}

void bst_delete(bst * b) {
	return;
}

void print_node(bst_node* nodo){
    printf("%d, %s\n", nodo->key, (char*)nodo->value);
}

void my_bst_print(bst_node* nodo){

    if(nodo == NULL)
        return;

    else{
        my_bst_print(nodo->left);
        print_node(nodo);
        my_bst_print(nodo->right);
    }
}

void bst_print(bst * b){

    my_bst_print(b->root);

	return;
}

int bst_predecessor(bst * b, int k) {
    bst_node* result = NULL;
    bst_node* t = b->root;
    while(t){
        if(t->key< k){
            result= t;
            t= t->right;
        }
        else t = t->left;
    }
    return result->key;
}
