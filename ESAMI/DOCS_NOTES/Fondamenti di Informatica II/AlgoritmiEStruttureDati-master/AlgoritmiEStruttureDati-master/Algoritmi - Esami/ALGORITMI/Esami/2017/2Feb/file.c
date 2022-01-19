#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"


int verifica(node* n,int  t,char* percorso);
char* aggiorna_percorso(char* s1, char* s2);

node_tree* new_node_tree(int size, int cartella,char* nome){
    node* n=malloc(sizeof(node));
    n->nome=nome;
    n->size=size;
    n->cartella=cartella;
    n->firstChild=NULL;
    n->nextSibling=NULL;
    return (node_tree*)n;
}

int get_node_size(node_tree* n){
    node* nodo=n;
    return nodo->size;
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

void nodo_print(node_tree* n, int t){

    if(n==NULL){
        return;
    }
    node* nodo=n;
    verifica(nodo,t,"");
}

int verifica(node* n, int t, char* percorso){
    int size_fratelli = 0;
    int size_figlio = 0;
    int size_cartella = n->size;

    if(n->nextSibling != NULL){
        size_fratelli = verifica(n->nextSibling, t, percorso);
    }
    char* buffer = aggiorna_percorso(percorso, n->nome);
    if(n->firstChild != NULL) size_figlio = verifica(n->firstChild, t, buffer);

    size_cartella += size_figlio;
    if(size_cartella >=t) printf("%s\n", buffer);

    return size_cartella+size_fratelli;
}

/*int verifica(node* n,int  t,char* percorso){
    int size_cartella=n->size;
    int size_figli=0;
    int size_fratelli=0;

    if(n->nextSibling!=NULL){
        size_fratelli=verifica(n->nextSibling,t,percorso);
    }
    char* buffer=aggiorna_percorso(percorso,n->nome);
    if (n->firstChild!=NULL){
        size_figli=verifica(n->firstChild,t,buffer);
    }
    size_cartella+=size_figli;
    if(size_cartella>=t){
        printf("%s\n",buffer);
    }
    return size_cartella+size_fratelli;

}
*/
char* aggiorna_percorso(char* s1, char* s2){
    char* res=malloc(sizeof(strlen(s1)+strlen(s2)));
    res=strcat(res,s1);
    res=strcat(res,"/");
    res=strcat(res,s2);
    return res;
}



