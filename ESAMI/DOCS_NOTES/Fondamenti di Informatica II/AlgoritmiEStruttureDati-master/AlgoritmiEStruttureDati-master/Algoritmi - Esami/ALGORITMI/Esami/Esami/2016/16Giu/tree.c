#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

node_tree * new_node_tree(int info) {
	node_tree * n = malloc(sizeof(node_tree));
	n->value = info;
	n->firstChild = NULL;
	n->nextSibling = NULL;

	return n;
}

int get_node_info(node_tree * n) {
	return n->value;
}

void set_firstChild_child(node_tree * n, node_tree * firstChild) {
	n->firstChild = firstChild;
}

node_tree * get_firstChild_child(node_tree * n) {
	return n->firstChild;
}

void set_nextSibling(node_tree * n, node_tree * nextSibling) {
	n->nextSibling = nextSibling;
}

node_tree * get_nextSibling(node_tree * n) {
	return n->nextSibling;
}

void delete_tree(node_tree * nt) {

	if (nt == NULL)
		return;


	// printf("Deleting node: %d\n", n->value);

	delete_tree(nt->firstChild);
	delete_tree(nt->nextSibling);
	free(nt);
}

void print_tree_ric(node_tree* n, int depth) {

	if (n == NULL)
		return;

	int i;
	for (i = 0; i < depth; i++)
		printf("-");

	printf("%d\n", n->value);
	print_tree_ric(n->firstChild, depth + 1);
	print_tree_ric(n->nextSibling, depth);
}

void print_tree(node_tree * node) {
	print_tree_ric(node, 0);
}

res* new_res(node_tree* nodo,int altezza,int completo){
    res* ris=malloc(sizeof(res));
    ris->altezza=altezza;
    ris->nodo=nodo;
    ris->completo=completo;
    return ris;
}

node_tree* max_sotto_albero_completo(node_tree* n,int k){
    res* ris=max_sotto_albero_completo_aux(n,k);
    if(ris==NULL) return NULL;
    return ris->nodo;
}

res* max_sotto_albero_completo_aux(node_tree* nodo, int k){
    if(nodo==NULL) return NULL;

    res** result_child=child_result(nodo,k);

    if(result_child==NULL) return new_res(nodo,0,1);                    //caso foglia

    int i;
    for(i=0; i <k; i++){
        if(result_child[i]==NULL || result_child[i]->completo==0){      //caso in cui ho un figlio che è foglia o che non è completo
            return max_child(result_child,k);
        }
    }
    int altezza=result_child[0]->altezza;
    for(i=1; i < k; i++){
        if(result_child[i]->altezza!=altezza){                          // sono completi ma non hanno stessa altezza
            return max_child(result_child,k);
        }
    }
    return new_res(nodo,altezza+1,1);                                   // figli sono tutti completi e hanno la stessa altezza
}

res* max_child(res** result,int k){
    int max_altezza=result[0]->altezza;
    node_tree*max_node=result[0]->nodo;
    int com=result[0]->completo;

    int i;
    for(i=1; i< k; i++){
        if(result[i]==NULL) break;
        if(result[i]->altezza>max_altezza){
            max_altezza=result[i]->altezza;
            max_node=result[i]->nodo;
            com=result[i]->completo;
        }
    }
    return new_res(max_node,max_altezza,com);

}

res** child_result(node_tree* nodo, int k){                             // mi creao un array di array per ogni radice che avrà al suo interno tutti i figli nelle posizioni i-esime fino a k
    node_tree* figlio=nodo->firstChild;
    if(figlio==NULL) return NULL; // caso foglia

    int i=0;
    res** ris=calloc(1, sizeof(res*)); // caso almeno 1 figlio
    while(i<k && figlio!=NULL){
        ris[i]=max_sotto_albero_completo_aux(figlio,k);
        i++;
        figlio=figlio->nextSibling;
    }
    return ris;
}


