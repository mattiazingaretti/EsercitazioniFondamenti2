#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bintree.h"
#include "bintree_services.h"


typedef struct {
  int size;
  int complete;
  binTree* root;
}isComplete;


int getHeight(int size) {
  return ceil(log2(size + 1));
}


//for further details see at https://www.geeksforgeeks.org/find-the-largest-complete-subtree-in-a-given-binary-tree/
isComplete* get_size_max_complete_subtree_aux(binTree* bt){
  isComplete* ic = (isComplete*) malloc(sizeof(isComplete));

  if(bt == NULL){
    ic->complete = 1;
    ic->size = 0;
    ic->root = NULL;
    return ic;
  }
  //printf("Visiting node : %d\n", bt->key);

  isComplete* icl = get_size_max_complete_subtree_aux(bt->left);
  isComplete* icr = get_size_max_complete_subtree_aux(bt->right);

  if(icl->complete && icr->complete && getHeight(icl->size) == getHeight(icr->size)){
    ic->complete = 1;
    ic->size = icl->size + icr->size + 1;
    ic->root = bt;
  }else{
    ic->complete = 0;
    ic->size = (icl->size > icr->size) ? icl->size : icr->size;
    ic->root = (icl->size > icr->size) ? icl->root : icr->root;
  }
  return ic;
}



int get_size_max_complete_subtree(binTree* bt){
  if(bt == NULL)
    return 0;

  isComplete* ret = get_size_max_complete_subtree_aux(bt);
  
  //printf("ret : \n-size :\t %d\n-complete :\t %d\n-root :\t %d\n", ret->size, ret->complete, ret->root->key);
  return ret->size;
}
