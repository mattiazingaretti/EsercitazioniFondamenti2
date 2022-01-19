#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "bst.h"

typedef struct nodo{
    char* s ;
    int occ;
}nodo;

nodo* newNodo(){
    nodo* node = malloc(sizeof(nodo));
    node->s= "";
    node->occ = 0;
    return node;
}

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

BinNode* BST_insert2(BinNode* n, char* k){
    if(strcmp(n->key, k)== 0){
        n->cont++;
        return n;
    }
    else if(strcmp(n->key, k) < 0){ //n precede il nodo che cerco/voglio creare
        if(n->right != NULL) BST_insert2(n->right, k);
        else{
            BinNode* nodo = BST_node_new(k);
            n->right = nodo;
            return nodo;
        }
    }
    else{
        if(n->left != NULL) BST_insert2(n->left, k);
        else{
            BinNode* nodo = BST_node_new(k);
            n->left = nodo;
            return nodo;
        }
    }
}

BinNode *BST_insert(BST *b, char *k) {
        /* DA IMPLEMENTARE */
        char* key = toUppercase(k);
        if(b->root == NULL){
             BinNode* nodo = BST_node_new(key);
             b->root = nodo;
             return nodo;
         }
        BinNode* nodo = BST_insert2(b->root, key);
        return nodo; // c
}

int BST_find2(BinNode* b, char* k){
    if(b== NULL) return 0;
    if(strcmp(b->key, k) == 0) return b->cont;
    else if(strcmp(b->key, k) < 0){
        BST_find2(b->right, k);
    }
    else BST_find2(b->left,k);
}

int BST_find(BST * b, char *k) {
        /*DA IMPLEMENTARE*/
        if(b->root == NULL) return 0;
        char* key = toUppercase(k);
        int x = BST_find2(b->root,key);
        return x; // per consentire compilazione
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

void mostFrequentString2(BinNode* b, nodo* struttura){
    if(b == NULL) return;
    if(b->cont > struttura->occ){
        struttura->occ = b->cont;
        struttura->s = b->key;
    }
    mostFrequentString2(b->left, struttura);
    mostFrequentString2(b->right, struttura);
}

char *mostFrequentString(BST *t){
        /*DA IMPLEMENTARE*/
        if(t->root == NULL) return "";
        nodo* struttura = newNodo();
        mostFrequentString2(t->root, struttura);
        return struttura->s; // per consentire compilazione
}

int isBalancedaux(BinNode* b){
    if(b== NULL) return;
    int l = isBalancedaux(b->left);
    int r = isBalancedaux(b->right);
    if(l < 0 || r < 0) return -1;
    int diff;
    if(l>=r) diff = l -r;
    else diff = r - l;
    if(diff <= 1){
        if( l>= r) return l+1;
        else return r +1;
    }
    return -1;
}

int isBalanced(BST *t) {
        /*DA IMPLEMENTARE*/
        if(t->root == NULL) return -1;
        int x = isBalancedaux(t->root);
        if( x < 0) return 0;
        else return 1; // per consentire compilazione
}



