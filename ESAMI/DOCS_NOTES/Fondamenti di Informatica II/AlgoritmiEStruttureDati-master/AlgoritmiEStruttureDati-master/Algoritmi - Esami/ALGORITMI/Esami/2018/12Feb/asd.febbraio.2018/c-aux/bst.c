#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bst.h"

static char *toUppercase(char *s) {
    /*OK*/
    char *u = malloc(sizeof(char)*(strlen(s)+1));
    strcpy(u, s);
    int i = 0;
    while(u[i] != 0) {
        u[i] = toupper(u[i]);
        i++;
    }
    return u;
}


static BinNode *BST_node_new(char *k) {
    /*OK*/
    BinNode *b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;
	b->cont = 1;
	return b;
}

BST * BST_new() {
    /*OK*/
    BST *b = malloc(sizeof(BST));
    b->root = NULL;
	return b;
}


BinNode *BST_insert(BST *b, char *k) {
        /* DA IMPLEMENTARE */
        if(b==NULL) return NULL;
        BinNode* new=BST_node_new(k);
        if(b->root==NULL){
            b->root=new;
            return new;
        }
        BST_insert_aux(b->root,new);
        return new;
}

void BST_insert_aux(BinNode* nodo,BinNode* new){
    if(strcmp(new->key,nodo->key)==0){
        nodo->cont++;
        return;
    }
    if(strcmp(new->key,nodo->key)<0){
        //~ printf("----MINORI---\n");
        //~ printf("valore nodo %s e valore new %s, risultato %d\n",nodo->key,new->key,strcmp(new->key,nodo->key));
        if(nodo->left==NULL) nodo->left=new;
        else BST_insert_aux(nodo->left,new);
    }
    if(strcmp(new->key,nodo->key)>0){
        //~ printf("----MAGGIORI---\n");
        //~ printf("valore nodo %s e valore new %s, risultato %d\n",nodo->key,new->key,strcmp(new->key,nodo->key));
        if(nodo->right==NULL) nodo->right=new;
        else BST_insert_aux(nodo->right,new);
    }

}

int BST_find(BST * b, char *k) {
        /*DA IMPLEMENTARE*/
       if(b==NULL) return 0;
       else return BST_find_aux(b->root,k);
}

int BST_find_aux(BinNode* nodo, char* k){
    if(nodo==NULL) return 0;
    if(strcmp(toUppercase(k),toUppercase(nodo->key))==0) return nodo->cont;

    if(strcmp(toUppercase(k),toUppercase(nodo->key))<0) return BST_find_aux(nodo->left, k);

    if(strcmp(toUppercase(k),toUppercase(nodo->key))>0) return BST_find_aux(nodo->right,k);
}

static void BST_print_aux(BinNode * t, int level, char pos) {
    /* OK, MODIFICABILE */
	if (t == NULL)
		return;

    int i;
    for (i = 0; i < level - 1; i++) {
    	printf("   ");
    }

    if (level > 0) {
    	printf(" %c:--", pos);
    }

    printf("key: |%s|\toccorrenze: %d\n", t->key, t->cont);

    BST_print_aux(t->left, level + 1, 'l');
    BST_print_aux(t->right, level + 1, 'r');
}

void BST_print(BST * b){
    /* OK, MODIFICABILE */
    if(b != NULL) return BST_print_aux(b->root, 0, ' ');
}

char *mostFrequentString(BST *t){
        /*DA IMPLEMENTARE*/
        if(t==NULL) return "";
        else return mostFrequentString_aux(t->root,"",0);
}

char* mostFrequentString_aux(BinNode* nodo,char* max, int max_cont){
    if(nodo==NULL) return max;

    if(nodo->cont>max_cont){
        max_cont=nodo->cont;
        max=nodo->key;
    }

    max=mostFrequentString_aux(nodo->left,max,max_cont);
    max=mostFrequentString_aux(nodo->right,max,max_cont);

    return max;

}



int isBalanced(BST *t) {
    if(t==NULL) return 0;
    int val=isBalanced_aux(t->root,0);
    if(val==-1) return 0;
    else return 1;
}

int isBalanced_aux(BinNode* nodo, int altezza){
    if(nodo==NULL) return altezza;

    int sx=isBalanced_aux(nodo->left,altezza);
    if(sx==-1) return -1;
    int dx=isBalanced_aux(nodo->right, altezza);
    if(dx==-1) return -1;

    int diff=sx-dx;
    if(diff<-1 || diff>1) return -1;

    if(dx>=sx) return dx+1;
    else return sx+1;
}



