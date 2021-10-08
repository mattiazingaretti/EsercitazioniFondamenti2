//#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "bst.h"

static void ordina_aux(_bst_node* b) {
    if (!b)
        return;
    else {
        ordina_aux(b->left);
        printf("%d, ", b->key);
        ordina_aux(b->right);
    }
}

void ordina (bst *b) {
    bst* t = b;
    //puts("\n[");
    ordina_aux(t->root);
    //puts("]\n");
    return;
}

static void outer_range_aux(_bst_node* b, int k1, int k2) {
    if (!b)
        return;
    outer_range_aux(b->left, k1, k2);
    if (b->key < k1 || b->key > k2)
        printf("%d, ", b->key);
    outer_range_aux(b->right, k1, k2);
}

void outer_range(bst *t, int k1, int k2) {
    bst* b = t;
    puts("\n");
    outer_range_aux(b->root, k1, k2);
    puts("\n");
    return;
}

static int height(_bst_node* b) {
    if (!b)
        return 0;
    else {
        int sx = height(b->left);
        int dx = height(b->right);
        return (sx >= dx ? sx : dx)+1;
    }
}

int altezza(bst *b) {
    bst* t = b;
    if (!t)
        return -3; // solo x restituire un valore anomalo
    return height(t->root)-1;
}
