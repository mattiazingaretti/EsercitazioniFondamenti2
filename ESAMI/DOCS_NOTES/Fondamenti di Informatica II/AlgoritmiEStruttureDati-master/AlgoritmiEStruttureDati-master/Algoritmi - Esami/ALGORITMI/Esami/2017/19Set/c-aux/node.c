#ifndef NODEC
#define NODEC

#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Node *newNode(char *n, int s, int isD) {
    if(illegalName(n)) return NULL;
    Node *new = malloc(sizeof(Node));
    new->nome = malloc((16+1)*sizeof(char));
    new->nome[16] = 0;
    strncpy(new->nome, n, 16);
    new->size = s;
    new->isDir = isD;
    new->parent = NULL;
    new->firstChild = NULL;
    new->nextSibling = NULL;
    return new;
}

int illegalName(char *s) {
    if(*s==0) return 1;
    while(*s != 0) if(*(s++) == '/') return 1;
    return 0;
}

int getIsDir(Node *v){
    return v->isDir;
}


#endif