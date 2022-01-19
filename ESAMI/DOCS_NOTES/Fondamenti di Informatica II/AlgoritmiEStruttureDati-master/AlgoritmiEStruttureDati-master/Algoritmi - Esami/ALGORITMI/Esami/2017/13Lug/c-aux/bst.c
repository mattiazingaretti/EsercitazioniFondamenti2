#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"

static BinNode * BST_node_new(int x, int y) {
    /*NON MODIFICARE*/
    BinNode * b = malloc(sizeof(BinNode));
	b->coordinates[0] = x;
	b->coordinates[1] = y;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * BST_new() {
    /*NON MODIFICARE*/
        BST * b = malloc(sizeof(BST));
        b->root = NULL;

	return b;
}

BinNode * BST_insert(BST * b, int x, int y) {
        /*DA IMPLEMENTARE*/
        if(b==NULL) return NULL;
        if(b->root==NULL){
            b->root=BST_node_new(x,y);
            return;
        }
        return BST_insert_aux(b->root,x,y);

}

BinNode* BST_insert_aux(BinNode* nodo, int x,int y){
    BinNode* new=BST_node_new(x,y);
    if(nodo==NULL) return nodo;
    if(x==nodo->coordinates[0] && y==nodo->coordinates[1]) return NULL;
    else if((x<nodo->coordinates[0] && y<nodo->coordinates[1])|| (x==nodo->coordinates[0] && y<nodo->coordinates[1])){
        if(nodo->left==NULL) nodo->left=new;
        else return BST_insert_aux(nodo->left,x,y);
    }
    else{
        if(nodo->right==NULL) nodo->right=new;
        else return BST_insert_aux(nodo->right,x,y);
    }
}

static void BST_delete_aux(BinNode * t) {
/*NON MODIFICARE*/
	if (t == NULL)
		return;

        BST_delete_aux(t->left);
        BST_delete_aux(t->right);
	free(t);
}

void BST_delete(BST * b) {
/*NON MODIFICARE*/
	if (b == NULL)
		return;

        BST_delete_aux(b->root);
        free(b);
}

void BST_print_aux(BinNode * t, int level) {
    /*MODIFICABILE*/
    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" |--");
    }

    if (t == NULL){
        printf("%c \n",35);
        return;
    }

    printf("(%d,%d)\n", t->coordinates[0],t->coordinates[1]);

    BST_print_aux(t->left, level + 1);
    BST_print_aux(t->right, level + 1);
}

void BST_print(BST * b){
    /*MODIFICABILE*/
    return BST_print_aux(b->root, 0);
}

int aligned(BST * b, int x){
        /*DA IMPLEMENTARE*/
        if(b==NULL) return -1;
        return aligned_aux(b->root,x,0);
}

int aligned_aux(BinNode* nodo, int x,int cont){

    if(nodo==NULL) return cont;
    if(x==nodo->coordinates[0]) cont++;
    cont=aligned_aux(nodo->right, x,cont);
    cont=aligned_aux(nodo->left,x,cont);
}

int rangeQ(BST * b, int x1, int y1, int x2, int y2){
        /*DA IMPLEMENTARE*/
        if(b==NULL) return -1;
        return rangeQ_aux(b->root,x1,y1,x2,y2,0);
}

int rangeQ_aux(BinNode* nodo, int x1,int y1,int x2,int y2,int cont){
    if(nodo==NULL) return cont;
    if((nodo->coordinates[0]>x1 && nodo->coordinates[0]<x2) && (nodo->coordinates[1]>y1 && nodo->coordinates[1]<y2)){
        cont++;
    }
    else if((nodo->coordinates[0]>x1 && nodo->coordinates[0]<x2) && nodo->coordinates[1]==y1){
        cont++;
    }
    else if((nodo->coordinates[0]>x1 && nodo->coordinates[0]<x2) && nodo->coordinates[1]==y2){
        cont++;
    }
    else if((nodo->coordinates[1]>y1 && nodo->coordinates[1]<y2) && nodo->coordinates[0]==x1){
        cont++;
    }
    else if((nodo->coordinates[1]>y1 && nodo->coordinates[1]<y2) && nodo->coordinates[0]==x2){
        cont++;
    }
    else if(nodo->coordinates[0]==x1 && nodo->coordinates[0]==x2 && nodo->coordinates[1]==y2 && nodo->coordinates[1]==y1){
        cont++;
    }
    cont=rangeQ_aux(nodo->right,x1,y1,x2,y2,cont);
    cont=rangeQ_aux(nodo->left,x1,y1,x2,y2,cont);




}





