#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

tree* new_tree(node_tree* nodo, int info){
    tree* t=malloc(sizeof(tree));
    t->nodo=nodo;
    t->info=info;

}

node_tree* new_node_tree(int key){
    node* n=malloc(sizeof(node));
    n->key=key;
    n->firstChild=NULL;
    n->nextSibling=NULL;
    return (node_tree*)n;
}

int get_node_key(node_tree* n){
    node* nodo=n;
    return nodo->key;
}

void set_first_child(node_tree* n, node_tree* first_child){
    node* nodo=n;
    nodo->firstChild=first_child;
}

void set_next_sibling(node_tree* n, node_tree* next_sibling){
    node*nodo=n;
    nodo->nextSibling=next_sibling;
}

node_tree * get_first_child(node_tree * n) {
    node* nodo = n;
    node * figlio = nodo->firstChild;
	return (node_tree*) figlio;
}

node_tree * get_next_sibling(node_tree * n) {
    node* nodo = n;
    node * fratello = nodo->nextSibling;
	return (node_tree*) fratello;
}

void delete_tree(node_tree * nt) {
    node* aux = nt;
    if(aux == NULL){
        return;
    }
    delete_tree(aux->firstChild);
    delete_tree(aux->nextSibling);
    free(aux);
}

void nodo_print(node_tree* n, node_tree* x, node_tree* y){

    if(n==NULL || x==NULL || y==NULL){
        return;
    }
    node* nodo=n;
    node* first=x;
    node* sec=y;
    tree* new=lca(nodo,first,sec);
    printf("Valore della chiave del padre deve essere 1, essa è [%d]\n", new->nodo->key);
}

tree* lca(node* nodo,node* x, node* y){

    if(nodo==NULL){
        return new_tree(NULL,0);
    }
    if(nodo==x && nodo==y){
        return new_tree(NULL,2);
    }
    if(nodo==x || nodo==y){
        return new_tree(NULL,1);
    }
    tree* new=lca_2(nodo->firstChild,x,y);
    if(new->info==2 && new->nodo==NULL){
        new->nodo=nodo;
    }
    return new;
}

tree* lca_2(node* nodo,node* x,node* y){
    tree* new=malloc(sizeof(tree));
    tree* parziale;
    node* figlio=nodo;
    while(figlio!=NULL){
        parziale=lca(figlio,x,y);
        new->info+=parziale->info;
        figlio=figlio->nextSibling;
    }
    return new;
}

