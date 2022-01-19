#ifndef TREEC
#define TREEC

#include "tree.h"
#include "node.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int nodeInTree(Tree *t, Node *v) {
    if(v == NULL) return 0;
    if(v == t->root) return 1;
    return nodeInTree(t, v->parent);
}

Tree *newTree() {
    Tree *new = malloc(sizeof(Tree));
    new->root = newNode("Volume", 1024, 1);
    new->size = 1;
    return new;
}

res* new_res(Node* nodo, int byte){
    res* ris=malloc(sizeof(res));
    ris->nodo=nodo;
    ris->byte_rimossi=byte;
    return ris;
}
/* DA IMPLEMENTARE */
Node *insertFile(Tree *t, Node *p, char *nome, int size){
    if(t==NULL|| p==NULL) return NULL;
    Node* v=newNode(nome,size,0);
    v->parent=p;
    v->nextSibling=p->firstChild;
    p->firstChild=v;
    t->size++;
    return v;
}

/*void insertFile_aux(Node* nodo, Node* p,char* nome,int size,Node*v){
    if(nodo==NULL) return;
    if(nodo=p){
        if(nodo->firstChild==NULL){
            nodo->firstChild=v;
            return;
        }
        else{
            Node* tmp=nodo->firstChild;
            nodo->firstChild=v;
            v->nextSibling=tmp;
            return;
        }
    }
    insertFile_aux(nodo->firstChild,p,nome,size,v);
    insertFile_aux(nodo->nextSibling,p,nome,size,v);

}*/


/* DA IMPLEMENTARE */
Node *insertDir(Tree *t, Node *p, char *nome){
    if(t==NULL || p==NULL ) return NULL;
    Node* v=newNode(nome,1024,1);
    v->parent=p;
    v->nextSibling=p->firstChild;
    p->firstChild=v;
    t->size++;
    return v;
}

/*void insertDir_aux(Node* nodo,Node* p,char* nome,Node* v){
    if(nodo==NULL) return;
    if(nodo=p){
        if(nodo->firstChild==NULL){
            nodo->firstChild=v;
            return;
        }
        else{
            Node* tmp=nodo->firstChild;
            nodo->firstChild=v;
            v->nextSibling=tmp;
            return;
        }
    }
    insertDir_aux(nodo->firstChild,p,nome,v);
    insertDir_aux(nodo->nextSibling,p,nome,v);

}*/

/* DA IMPLEMENTARE */
int cleanSmallDirs(Tree *t, int min) {
    if(t==NULL) return -1;
    res* ris=cleanSmallDirs_aux(t->root,min);
    return ris->byte_rimossi;

}

res* cleanSmallDirs_aux(Node* nodo, int min){
    if(nodo==NULL) return new_res(NULL,0);

    res* mioRes=new_res(nodo,nodo->size);
    res* fratelli=NULL;
    res* figli=NULL;

    fratelli=cleanSmallDirs_aux(nodo->nextSibling,min);
    nodo->nextSibling=fratelli->nodo;
    mioRes->byte_rimossi+=fratelli->byte_rimossi;

    queue* coda=newQueue();
    wrapper_figli_coda(nodo,coda);
    if(is_cartella_eliminare(nodo,coda,min)==1){
        mioRes->nodo=nodo->nextSibling;             // DEVO ELIMINARE NODO, FACCIO PUNTARE AL FRATELLO COSI DA POTERLO ELIMINARE
        mioRes->byte_rimossi+=byte_cartella_interna(nodo,coda);
        mioRes->byte_rimossi+=byte_cartella_vuota(nodo);

    }
    else{
        figli=cleanSmallDirs_aux(nodo->firstChild,min);
        nodo->firstChild=figli->nodo;
        mioRes->byte_rimossi+=figli->byte_rimossi;


    }
    return mioRes;
}

int byte_cartella_interna(Node* nodo, queue* coda){
    int ris=0;
    if(coda->size==0) return ris;

    queueItem* head=coda->head;
    while(isEmptyQueue(coda)==FALSE){
        Node* nodo=(Node*)dequeue(coda);
        ris+=nodo->size;
        free(nodo);

    }
    return ris;

}

int byte_cartella_vuota(Node* nodo){
    int ris=nodo->size;
    free(nodo);
    return ris;
}

int is_cartella_eliminare(Node* nodo, queue* coda, int min){
    // VERIFICO SE I FRATELLI DI UN NODO CHE SONO CONTENUTI NELLA CODA SONO FILE O NO E QUINDI SE SONO TUTTI FILE E NODO È CARTELLA LO DEVO ELIMINARE
     int peso_cartella=nodo->size;
    if(coda->size==0)
        if(peso_cartella<min && nodo->isDir==1) return 1;


    queueItem* head=coda->head;
    while(head!=NULL){
        Node* nodo=(Node*)head->item;
        if(nodo->isDir){                        // APPENA TROVO CARTELLA CON FIGLI TRA I FRATELLI ESCO, NON DEVO ELIMINARE CARTELLA
            return 0;
        }
        peso_cartella+= nodo->size;
        head=head->next;
    }
    if(peso_cartella<min) return 1;
    else return 0;

}

void wrapper_figli_coda(Node* nodo, queue* coda){
    while(nodo!=NULL){
        enqueue(coda,(Node*)nodo);      // AGGIUNGO ALLA CODA I FRATELLI, N.B. LAST IN FIRST OUT
        nodo=nodo->nextSibling;
    }
}






/* DA IMPLEMENTARE */
void findAll(Tree *t, char *s) {
    if(t==NULL) return;
    findAll_aux(t->root,s,"");

}

void findAll_aux(Node* nodo, char* s,char* percorso){
    if(nodo->nextSibling!=NULL){
        findAll_aux(nodo->nextSibling,s,percorso);
    }
    char* buffer=aggiorna_percorso(percorso,nodo->nome);
    if(nodo->firstChild!=NULL){
        findAll_aux(nodo->firstChild,s,buffer);
    }

    if(strcmp(nodo->nome,s)==0){
        if(nodo->isDir) printf("%s/\n", buffer);
        else printf("%s\n",buffer);
    }

}

char* aggiorna_percorso(char* s1,char* s2){
    char* ris=malloc(strlen(s1)+strlen(s2)+2);
    ris=strcat(ris,s1);
    ris=strcat(ris, "/");
    ris=strcat(ris,s2);
    return ris;
}


#endif
