#ifndef _BSTH
#define _BSTH

#include "bstnode.h"

struct bst {
    bstnode *root;
    int size;
};

typedef struct bst bst;

typedef struct res{
    bstnode* nodo;
    double area;
    int is_corona;
}res;

bst *newBST();
bstnode *insert(bst *t, double x, double y);
static double raggio(double x, double y);
static double raggiop(bstnode *u);
static double fase(double x, double y);
static double fasep(bstnode *p);
static void _print(bstnode *t, int ind, char *msg);
void print(bst *t);
int corona(bst *t, double r1, double r2);
double maxCorona(bst *t);

void insert_aux(bstnode* nodo,bstnode* new);
void corona_aux(bstnode* nodo, double r1, double r2,int* cont);
int maxCorona_aux(bstnode* nodo,double* array,int i);
int num_nodi_albero(bstnode* nodo);
#endif
