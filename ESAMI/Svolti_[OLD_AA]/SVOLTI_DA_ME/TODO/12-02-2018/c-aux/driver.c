#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


int main(int argc, char** argv) {
    /*sentitevi liberi di aggiungere nuovi test nel main */
    BST *b = BST_new();

    BST_insert(b, "Se");
    BST_insert(b, "usi");
    BST_insert(b, "il");
    BST_insert(b, "package");
    BST_insert(b, "il");
    BST_insert(b, "prof");
    BST_insert(b, "Lazzeretti");
    BST_insert(b, "ha");
    BST_insert(b, "difficolta");
    BST_insert(b, "a");
    BST_insert(b, "compilare");
    BST_insert(b, "Se");
    BST_insert(b, "il");
    BST_insert(b, "codice");
    BST_insert(b, "non");
    BST_insert(b, "compila");
    BST_insert(b, "con");
    BST_insert(b, "javac");
    BST_insert(b, "dovrai");
    BST_insert(b, "ripetere");
    BST_insert(b, "l");
    BST_insert(b, "esame");


    printf("\tAlbero: \n\n");
    BST_print(b);

    char *k = "se";
    printf("\n\tRicerca valore\n");

    int c = BST_find(b, k);
    if (c == -1)
        printf("Non implementato\n");
    else if (c == 0)
        printf("Nodo con chiave %s NON trovato\n", k);
    else
        printf("Nodo con chiave %s trovato: %d occorrenze\n", k, c);

    k= "ripete";
    c = BST_find(b, k);
    if (c==-1)
        printf("Non implementato\n");
    else if (c==0)
        printf("Nodo con chiave %s NON trovato\n", k);
    else
        printf("Nodo con chiave %s trovato: %d occorrenze\n", k, c);

    printf("\n\tRicerca stringa più frequente\n");
    char *smax = mostFrequentString(b);
    printf("Stringa più frequente: %s\n", smax);

    printf("\n\ttest bilanciamento:\n");
    int result = isBalanced(b);
    if (result==-1)
        printf("Non implementato\n");
    else if (result==0)
        printf("Non bilanciato\n");
    else
        printf("Bilanciato\n");

}
