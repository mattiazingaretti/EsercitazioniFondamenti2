#ifndef TREEC
#define TREEC

#include "tree.h"
#include "node.h"
#include "queue.h"
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

/* DA IMPLEMENTARE */
Node *insertFile(Tree *t, Node *p, char *nome, int size){
    if((illegalName(nome)) == 1) return NULL;
    Node* nodo = newNode(nome, size, 0);
    if(t->root->firstChild == NULL){
        t->root->firstChild = nodo;
        nodo->parent = t->root;
        t->size++;
        return nodo;
    }
    if(p->firstChild != NULL) nodo->nextSibling = p->firstChild;
    p->firstChild = nodo;
    nodo->parent = p;
    printf("Aggiungo a padre %s il figlio file %s\n", nodo->parent->nome, p->firstChild->nome);
    t->size++;
    return nodo; // inserita per permettere la compilazione
}

/* DA IMPLEMENTARE */
Node *insertDir(Tree *t, Node *p, char *nome){
    if((illegalName(nome))== 1)return NULL;
    Node* nodo = newNode(nome, 1024, 1);
    if(t->root->firstChild == NULL){
        t->root->firstChild = nodo;
        nodo->parent = t->root;
        t->size++;
        return nodo;
    }
    printf("Aggiungo a padre %s il figlio directory %s\n", p->nome, nome);
    if(p->firstChild != NULL) nodo->nextSibling = p->firstChild;
    p->firstChild = nodo;
    nodo->parent = p;
    t->size++;
    return nodo; // inserita per permettere la compilazione
}

void eliminanodo(Node* t, Node* n){
    if(t == NULL) return;
    if(t->firstChild == n){
        t->firstChild = n->nextSibling;
        free(n);
        return;
    }
    else if(t->nextSibling == n){
        t->nextSibling = n->nextSibling;
        free(n);
        return;
    }
    eliminanodo(t->firstChild, n);
    eliminanodo(t->nextSibling, n);
}

int figlituttifile(Node*n){
    int x = 1;
    Node* figlio = n->firstChild;
    while(figlio != NULL){
        if(figlio->isDir == 1){
             x = 0;
        }
        figlio = figlio->nextSibling;
    }
    return x;
}

int sommafile(Node* n){
    int somma = 0;
    somma += n->size;
    if(n->firstChild == NULL) return somma;
    Node* figlio = n->firstChild;
    while(figlio != NULL){
        somma += figlio->size;
        figlio = figlio->nextSibling;
    }
    return somma;
}

void clean2(Node* n, int min, queue* q){
    if(n == NULL) return ;
    if(n->isDir == 1){
        if(n->firstChild != NULL){
            if(figlituttifile(n) == 1){
                if(sommafile(n) < min){
                    printf("%s : Lo elimino perchè ha tutti i figli file e sommafile = %d\n",n->nome, sommafile(n));
                    enqueue(q, n);
                }
            }
        }
        else if(n->size < min){
            enqueue(q,n);
            printf("%s: Lo elimino perchè non ha i figli e sommafile = %d (padre %s)\n", n->nome, sommafile(n), n->parent->nome);
        }
    }
    clean2(n->firstChild, min, q);
    clean2(n->nextSibling, min, q);
}

/* DA IMPLEMENTARE */
int cleanSmallDirs(Tree *t, int min) {
    int cancellati=0 ;
    queue* q = newQueue();
    clean2(t->root, min, q);
    while(q->size > 0){
        Node* n = (Node*) dequeue(q);
        cancellati += sommafile(n);
        eliminanodo(t->root, n);
    }
    return cancellati; // inserita per permettere la compilazione
}

void printpercorsi(Node* b){
    queue* q = newQueue();
    while(b!= NULL){
        enqueue(q, b);
        b= b->parent;
    }
    int n = q->size -1;
    char* array[n];
    while( q->size > 0){
        Node* n = (Node*) dequeue(q);
        array[q->size -1] = n->nome;
    }
    int i;
    for(i=0; i < n; i ++){
        printf("/%s", array[i]);
    }
    printf("\n");
}

void findAll2(Tree* t, Node* b, char* s){
    if(b == NULL) return;
    findAll2(t, b->firstChild, s);
    findAll2(t, b->nextSibling, s);
    if(strcmp(b->nome, s) == 0){
        printf("/%s", t->root->nome);
        printpercorsi(b);
    }
}

/* DA IMPLEMENTARE */
void findAll(Tree *t, char *s) {
    if(t->root->nome == s){
        printf("/%s/\n", s);
        return;
    }
    findAll2(t,t->root,s);
    return; // inserita per permettere la compilazione
}


#endif
