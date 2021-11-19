#include <stdlib.h>
#include <stdio.h>

#include "bintree.h"

binTree* bintree_new(int k) {
    binTree *t = malloc(sizeof(binTree));
    t->key = k;
    t->left = t->right = NULL;
    return t;
}

binTree* bintree_set_left_child(binTree *t, int k) {
    if(t==NULL) return NULL;
    if(t->left != NULL) return NULL;
    return t->left = bintree_new(k);
}

binTree* bintree_set_right_child(binTree *t, int k) {
    if(t==NULL) return NULL;
    if(t->right != NULL) return NULL;
    return t->right = bintree_new(k);
}

void bintree_delete(binTree* bt){
    if(!bt)
        return;
    else{
        bintree_delete(bt->left);
        bintree_delete(bt->right);
        free(bt);
    }
}

static void bintree_print_rec(binTree* bt, int level){
    if(bt == NULL){
        return;
    }
    else{
        int i = 0;
        while(i < level){
            printf(" |");
            i++;
        }
        printf("-");
        printf("%d\n", bt->key);
        bintree_print_rec(bt->left, level + 1);
        bintree_print_rec(bt->right, level + 1);
    }
}

void bintree_print(binTree* bt){
    bintree_print_rec(bt, 0);
}