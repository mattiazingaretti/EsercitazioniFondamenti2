#ifndef TREEH
#define TREEH

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "node.h"

typedef struct Tree {
    Node *root;
    int size;
} Tree;


int nodeInTree(Tree *t, Node *v); //  a scopo debug
Tree *newTree();
Node *insertFile(Tree *t, Node *p, char *nome, int size);
Node *insertDir(Tree *t, Node *p, char *nome);
void findAll(Tree *t, char *s);
int cleanSmallDirs(Tree *t, int min);
void printTree(Tree *t);

#endif