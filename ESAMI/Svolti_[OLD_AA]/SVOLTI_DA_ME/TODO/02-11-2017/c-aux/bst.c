#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "queue.h"


BinNode * newBinNode(int k) {
    /*OK*/
    BinNode * b = malloc(sizeof(BinNode));
	b->key = k;
	b->left = NULL;
	b->right = NULL;

	return b;
}

BST * newBST() {
    /*OK*/
    BST * b = malloc(sizeof(BST));
    b->root = NULL;

	return b;
}

// altri prototipi (per funzioni locali)
static void print(BinNode *t, int level, char pos);
// fine prototipi



static void print(BinNode *t, int level, char pos) {
    if(t == NULL) return;
    for (int i = 0; i < level - 1; i++) printf("   ");
    if (level > 0) printf(" %c:--", pos);

    printf("%d\n", t->key);
    print(t->left, level + 1, 'l');
    print(t->right, level + 1, 'r');
}

void BST_print(BST *t){
    if(t != NULL && t->root != NULL) print(t->root, 0, ' ');
}

BinNode* BST_insert_aux(BinNode* node, int k){

  if(k < node->key){
    if(node->left == NULL){
      node->left = newBinNode(k);
      return node->left;
    }else
      return BST_insert_aux(node->left, k);
  }else if(k > node->key){
    if(node->right == NULL){
      node->right = newBinNode(k);
      return node->right;
    }else
      return BST_insert_aux(node->right, k);
  }
  return NULL;
}

BinNode *BST_insert(BST *t, int k) {
  if(t->root == NULL){
    t->root = newBinNode(k);
    return t->root;
  }
  return BST_insert_aux(t->root, k);
}

int isBST_aux(BinNode* node){
  if(node == NULL)
    return 0;

  int left = isBST_aux(node->left);
  int right = isBST_aux(node->right);

  if(left < 0 || right < 0)
    return -1;

  if(left == 0 || right == 0)
    return node->key;
  
  if(node->key >= left && node->key <= right)
    return right;
  return -1;
}

int isBST(BST *t) {
  if(t->root == NULL)
    return 0;
  int res = isBST_aux(t->root);
  return (res > 0) ? 1 : 0;
}


int isBalanced_aux(BinNode* node){
  if(node == NULL)
    return 0;

  int left = isBalanced_aux(node->left);
  int right = isBalanced_aux(node->right);

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

int isAVL_aux(BinNode* node, int* height){
  if(node == NULL){
    *height = 0;
    return 0;
  }

  int hl, hr;

  int left = isAVL_aux(node->left, &hl);
  int right = isAVL_aux(node->right, &hr);

  if(left < 0 || right < 0)
    return -1;
  
  int res = (hl - hr > 0) ? hl - hr : hr - hl;
  if(res <= 1)
    *height =  ((hl > hr) ? hl : hr) + 1;
  else
    return -1;
  
  if(left == 0 || right == 0)
    return node->key;

  if(node->key >= left && node->key <= right)
    return right;
  return -1;
}


int isAVL(BST *t) {
  if(t->root == NULL)
    return 0;

  int height = 0;
  int res = isAVL_aux(t->root, &height);
  return (res < 0) ? 0 : 1;
}