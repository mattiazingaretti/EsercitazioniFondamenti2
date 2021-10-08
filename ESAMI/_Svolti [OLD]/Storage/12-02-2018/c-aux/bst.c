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

BinNode* BST_insert_aux(BinNode* b, char* k){

  if(strcmp(k, b->key) < 0){
    if(b->left == NULL){
      b->left = BST_node_new(k);
      return b->left;
    }else
      return BST_insert_aux(b->left, k);
  }else if(strcmp(k, b->key) > 0){
    if(b->right == NULL){
      b->right = BST_node_new(k);
      return b->right;
    }else
      return BST_insert_aux(b->right, k);
  }
  
  (b->cont)++;
  return b;
}


BinNode *BST_insert(BST *b, char *k) {
  if(b->root == NULL){
    b->root = BST_node_new(toUppercase(k));
    return b->root;
  }

  return BST_insert_aux(b->root, toUppercase(k));
}

int BST_find_aux(BinNode* b, char* k){
  if(b == NULL)
    return 0;
  
  if(strcmp(k, b->key) < 0)
    return BST_find_aux(b->left, k);
  else if(strcmp(k, b->key) > 0)
    return BST_find_aux(b->right, k);
  return b->cont;
}

int BST_find(BST * b, char *k) {
  if(b->root == NULL)
    return 0;
  return BST_find_aux(b->root, toUppercase(k));
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


void mostFrequentString_aux(BinNode* b, BinNode** data){
  if(b == NULL)
    return;

  mostFrequentString_aux(b->left, data);
  mostFrequentString_aux(b->right, data);

  if(*data == NULL)
    *data = b;
  else if(b->cont > (*data)->cont)
    *data = b;
  return;
}


char *mostFrequentString(BST *t){
  if(t->root == NULL)
    return NULL;

  BinNode* tmp = NULL;
  mostFrequentString_aux(t->root, &tmp);
  
  return (tmp == NULL) ? NULL : tmp->key;
}

int isBalanced_aux(BinNode* b){
  if(b == NULL)
    return 0;

  int left = isBalanced_aux(b->left);
  int right = isBalanced_aux(b->right);

  if(left < 0 || right < 0)
    return -1;

  int res = (left - right < 0) ? right - left : left - right;

  if(res <= 1)
    return ((left > right) ? left : right) + 1;
  return -1;
}


int isBalanced(BST *t) {
  if(t->root == NULL)
    return 0;

  int res = isBalanced_aux(t->root);

  return (res < 0) ? 0 : 1;
}



