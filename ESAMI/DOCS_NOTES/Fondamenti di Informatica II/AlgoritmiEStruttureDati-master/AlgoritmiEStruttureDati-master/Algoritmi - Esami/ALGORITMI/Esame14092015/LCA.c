#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct res{
    int value;
    tree* puntatore;
}res;

tree* getLCA(node_tree* root, node_tree* x, node_tree* y){
    if(root == NULL || x == NULL || y == NULL){
        return NULL;
    }
    tree* myroot= (node*) root;
    tree* myx = (node*) x;
    tree* myy = (node*) y;

    res* result =_getLCA(myroot, myx, myy);

    return result->nodo;
}

res* _getLCA(tree* nodo, tree* x, tree* y){
    if(nodo == NULL){
        return new_struct(0, NULL);
    }
    if(nodo == x && nodo == y){
        return new_struct(2, NULL);
    }
    if(nodo == x || nodo==y){
        return new_struct(1, NULL);
    }

    res* result = wrapperSuiFigli(nodo->firstchild, x, y);

    if(result->trovati == 2 && result->nodo != NULL){
        result->nodo = nodo;
    }
    return result;
}

res* wrapperSuiFigli(tree* nodo, tree* x , tree* y){
    res* result = (res*)malloc(sizeof(res));
    res* parziale;
    tree* figlio = nodo;
    while(figlio != NULL){
        parziale = _getLCA(figlio, x, y);
        result->trovati += parziale->trovati;
        figlio= figlio->nextsibling;
    }
    printf("%d\n", result->trovati);
    return result;
}

res* new_struct(int value, tree* puntatore){
    res* result = (res*)malloc(sizeof(res));
    result->trovati = value;
    result->nodo = puntatore;
    return result;
}
