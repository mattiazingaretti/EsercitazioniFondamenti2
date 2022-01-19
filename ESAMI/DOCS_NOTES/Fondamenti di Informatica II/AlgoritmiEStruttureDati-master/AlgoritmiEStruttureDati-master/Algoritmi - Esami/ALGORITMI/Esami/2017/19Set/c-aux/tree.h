#ifndef TREEH
#define TREEH

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "node.h"
#include "queue.h"

typedef struct Tree {
    Node *root;
    int size;
} Tree;

typedef struct res{
    Node* nodo;
    int byte_rimossi;

}res;

int nodeInTree(Tree *t, Node *v); //  a scopo debug
Tree *newTree();
Node *insertFile(Tree *t, Node *p, char *nome, int size);
Node *insertDir(Tree *t, Node *p, char *nome);
void findAll(Tree *t, char *s);
int cleanSmallDirs(Tree *t, int min);
void printTree(Tree *t);

void insertDir_aux(Node* nodo,Node* p,char* nome,Node* v);
void insertFile_aux(Node* nodo, Node* p,char* nome,int size,Node*v);
void findAll_aux(Node* nodo, char* s,char* percorso);
char* aggiorna_percorso(char* s1,char* s2);
res* new_res(Node* nodo, int byte);
res* cleanSmallDirs_aux(Node* nodo, int min);
int byte_cartella_interna(Node* nodo, queue* coda);
int byte_cartella_vuota(Node* nodo);
int is_cartella_eliminare(Node* nodo, queue* coda, int min);
void wrapper_figli_coda(Node* nodo, queue* coda);


#endif
