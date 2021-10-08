#ifndef __BINTREE_H__
#define __BINTREE_H__

/**
 * Struttura per rappresentare un albero binario.
*/
typedef struct binTree {
    int key;
    struct binTree *left, *right;
} binTree;

/**
 * Crea un nuovo albero binario avente l'intero passato in input come chiave della radice.
*/
binTree *bintree_new(int);

/**
 * Inserisce un nuovo bintree alla sinistra del bintree passato in input.
 * La funzione ritorna il bintree appena inserito oppure NULL in caso di errore
 * o se il bintree in input aveva gia' un figlio sinistro.
*/
binTree *bintree_set_left_child(binTree*, int);

/**
 * Inserisce un nuovo bintree alla destra del bintree passato in input.
 * La funzione ritorna il bintree appena inserito oppure NULL in caso di errore
 * o se il bintree in input aveva gia' un figlio destro.
*/
binTree *bintree_set_right_child(binTree*, int);

/**
 * Distrugge l'albero binario in input.
*/
void bintree_delete(binTree*);

/**
 * Stampa a video una rappresentazione del bintree in input.
 */
void bintree_print(binTree*);

#endif