#ifndef _BSTC
#define _BSTC

#include "bst.h"
#include "bstnode.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PI 3.14159265

typedef struct tot{
    int totale;
}tot;

tot* newTot(){
    tot* t = malloc(sizeof(tot));
    t->totale = 0;
    return t;
}

bst *newBST() {
    bst *tmp = malloc(sizeof(bst));
    tmp->root = NULL;
    tmp->size = 0;
    return tmp;
}

static double raggio(double x, double y) {
    return sqrt(x*x+y*y);
}

static double raggiop(bstnode *u) {
    return raggio(u->x_coord, u->y_coord);
}

static double fase(double x, double y) {
    if(x == 0)
        if(y == 0) return 0;
        else if(y > 0) return PI/2;
        else return -PI/2;
    double a = atan(y/x);
    if(x > 0) return a;
    else if(y >= 0) return a + PI;
    else return a - PI;
}

static double fasep(bstnode *p) {
    return fase(p->x_coord, p->y_coord);
}

static void _print(bstnode *t, int ind, char *msg) {
    int i;
    for(i = 0; i < ind; i++) printf("--");
    if(t == NULL) { printf("# (%s)\n", msg); return; }
    printf("[NODE (x=%g, y=%g) (raggio=%g, fase=%g)] (%s)\n", t->x_coord, t->y_coord, raggiop(t), fasep(t), msg);
    _print(t->left, ind+1, "figlio SX");
    _print(t->right, ind+1, "figlio DX");
    return;
}

void print(bst *t) {
    printf("Stampa albero in pre-ordine. N.ro nodi: %d\n", t->size);
    _print(t->root, 0, "root");
    printf("Fine stampa albero in pre-ordine\n");
}

void insert2(bst* tree, bstnode* t, bstnode* n){
    if(fasep(t)==fasep(n) && raggiop(t)==raggiop(n)){
        return;
    }
    else if((raggiop(t) < raggiop(n)) ||(raggiop(t) == raggiop(n) && fasep(t) < fasep(n))){
        if(t->right != NULL) insert2(tree,t->right, n);
        else{
            t->right = n;
            tree->size++;
            return;
        }
    }
    else{
        if(t->left != NULL) insert2(tree,t->left, n);
        else{
            t->left = n;
            tree->size++;
            return;
        }
    }
}

bstnode *insert(bst *t, double x, double y) {
    /* DA IMPLEMENTARE */
    bstnode* n = newBSTNode(x, y);
    if(t->root == NULL){
        t->root = n;
        t->size++;
        return n;
    }
    int size = t->size;
    insert2(t, t->root, n);
    if(size == t->size) return NULL;
    return n; /* SOLO PER COMPILAZIONE */
}

void corona2(bstnode* n, double r1, double r2, tot* totale){
    if(n == NULL) return;
    if(raggiop(n) <= r2 && raggiop(n)>= r1){
        totale->totale++;
    }
    corona2(n->left, r1, r2, totale);
    corona2(n->right, r1, r2, totale);
}

int corona(bst *t, double r1, double r2) {
    if(r2 == 0) return 0;
    if(r1 == r2  && r2== 0) return 0;
    tot* totale = newTot();
    corona2(t->root, r1, r2, totale);
    /* DA IMPLEMENTARE */
    return totale->totale; /* SOLO PER COMPILAZIONE */
}

void memorizzanodi(bstnode* n, double* array, tot* totale){
    if(n == NULL) return;
    memorizzanodi(n->left, array, totale);
    array[totale->totale] = raggiop(n);
    totale->totale++;
    memorizzanodi(n->right, array, totale);
}

double maxCorona(bst *t) {
    /* DA IMPLEMENTARE */
    double array[t->size];
    tot* totale = newTot();
    memorizzanodi(t->root, array, totale);
    int i;
    double areamax = 0;
    printf("%f ", array[0]);
    for(i= 0; i < totale->totale-1; i++){
        printf(" %f", array[i+1]);
        if(((((array[i+1])*(array[i+1]))-((array[i])*(array[i])))*PI) >areamax) areamax = PI*(((array[i+1])*(array[i+1]))-((array[i])*(array[i])));
    }
    return areamax; /* SOLO PER COMPILAZIONE */
}

#endif
