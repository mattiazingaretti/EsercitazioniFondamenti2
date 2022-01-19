#ifndef _BSTC
#define _BSTC

#include "bst.h"
#include "bstnode.h"
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define PI 3.14159265


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
    for( i = 0; i < ind; i++) printf("--");
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

bstnode *insert(bst *t, double x, double y) {
    /* DA IMPLEMENTARE */
    if(t==NULL) return NULL;
    bstnode* new=newBSTNode(x,y);
    if(t->root==NULL){
        t->root=new;
        t->size++;
        return new;
    }
    insert_aux(t->root,new);
    if(new!=NULL){
        t->size++;
    }
    return new;

}

void insert_aux(bstnode* nodo,bstnode* new){
    if(nodo->x_coord==new->x_coord && nodo->y_coord==new->y_coord){
        new=NULL;
    }
    else if(raggiop(new)==raggiop(nodo)){
        if(fasep(new)<fasep(nodo)){
            if(nodo->left==NULL){
                nodo->left=new;
                return;
            }
            else{
                insert_aux(nodo->left,new);
            }
        }
        else{
            if(nodo->right==NULL){
                nodo->right=new;
                return;
            }
            else{
                insert_aux(nodo->right,new);
            }
        }
    }
    else if(raggiop(new)<raggiop(nodo)){
        if(nodo->left==NULL){
            nodo->left=new;
            return;
        }
        else{
            insert_aux(nodo->left,new);
        }
    }
    else{
        if(nodo->right==NULL){
            nodo->right=new;
            return;
        }
        else{
            insert_aux(nodo->right,new);
        }
    }
}

int corona(bst *t, double r1, double r2) {
    /* DA IMPLEMENTARE */
    if(t==NULL) return -1;
    int cont=0;
    corona_aux(t->root,r1,r2,&cont);
    return cont;
}

void corona_aux(bstnode* nodo, double r1, double r2,int* cont){
    if(nodo==NULL) return;
    if(raggiop(nodo)>=r1 && raggiop(nodo)<=r2){
        (*cont)++;
    }
    corona_aux(nodo->left,r1,r2,cont);
    corona_aux(nodo->right,r1,r2,cont);
}

double maxCorona(bst *t) {
    /* DA IMPLEMENTARE */
    if(t==NULL)return -1; /* SOLO PER COMPILAZIONE */
    int num=num_nodi_albero(t->root);
    double array[num];
    maxCorona_aux(t->root,array,0);
    int i;
    double max=0;
    for(i=1; i< num; i++){
        printf("%g\n", array[i-1]);
        double area=PI*((array[i]*array[i])-(array[i-1]*array[i-1]));
        if(area>max){
            max=area;

        }
    }

    return max;
}


int maxCorona_aux(bstnode* nodo,double* array,int i){
    if(nodo==NULL) return i;

    i=maxCorona_aux(nodo->left,array,i);
    array[i]=raggiop(nodo);
    i++;
    i=maxCorona_aux(nodo->right,array,i);
    return i;

}

int num_nodi_albero(bstnode* nodo){
    if(nodo==NULL) return 0;
    return 1+num_nodi_albero(nodo->left)+num_nodi_albero(nodo->right);
}


#endif
