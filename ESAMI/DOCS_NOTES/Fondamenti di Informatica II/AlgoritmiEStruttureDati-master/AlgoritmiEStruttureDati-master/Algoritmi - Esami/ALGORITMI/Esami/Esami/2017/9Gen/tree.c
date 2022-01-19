#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

node_tree* node_tree_new(char* etichetta){
    node*nodo=malloc(sizeof(node));
    nodo->etichetta=etichetta;
    nodo->firstChild=NULL;
    nodo->nextSibling=NULL;
    return (node_tree*)nodo;
}

char* get_etichetta(node_tree* n){
    node* nodo=n;
    return nodo->etichetta;
}

void set_first_child(node_tree* n, node_tree* firstChild){
    node* nodo=n;
    nodo->firstChild=firstChild;
}

void set_next_sibling(node_tree*n,node_tree* nextSibling){
    node* nodo=n;
    nodo->nextSibling=nextSibling;
}

node_tree* get_first_child(node_tree*n){
    node* nodo=n;
    node* figlio=nodo->firstChild;
    return (node_tree*)figlio;
}

node_tree* get_next_sibling(node_tree*n){
    node* nodo=n;
    node* fratello=nodo->nextSibling;
    return (node_tree*)fratello;
}

void stampo_percorso(node_tree* n,char* s){
    if(n==NULL) return;
    node* nodo=n;
    cerca_percorso(nodo,s,"");
    return;

}

void cerca_percorso(node* nodo, char* s,char* percorso){


    if (nodo-> nextSibling!=NULL){
        cerca_percorso(nodo->nextSibling,s,percorso);
    }
    char* buffer=aggiorna_percorso(percorso,nodo->etichetta);
    if (nodo->firstChild!=NULL){
        cerca_percorso(nodo->firstChild,s,buffer);
    }
    if(strcmp(nodo->etichetta,s)==0){
        printf("%s\n", buffer);
    }
    return;
}

char* aggiorna_percorso(char* s1,char* s2){
    char* res=malloc(sizeof(strlen(s1)+strlen(s2)+2));
    res=strcat(res,s1);
    res=strcat(res,"/");
    res=strcat(res,s2);
    return res;


}
