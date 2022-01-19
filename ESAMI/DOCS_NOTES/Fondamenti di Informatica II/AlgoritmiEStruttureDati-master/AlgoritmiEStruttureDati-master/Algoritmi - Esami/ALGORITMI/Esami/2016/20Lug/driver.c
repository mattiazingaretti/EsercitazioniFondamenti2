#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


void print_help() {
    printf("Richiesto argomento: {bst, predecessor, tree, balanced, avl}\n");
}

int main(int argc, char** argv) {



        bst * b1 = bst_new(6, "Pisa");

        bst_insert(b1, 1, "Torino");
        bst_insert(b1, 2, "Milano");
       //bst_insert(b1, 8, "Bologna");
        bst_insert(b1, 78, "Firenze");
        bst_insert(b1, 4, "Padova");
        bst_insert(b1, 3, "sasas");

        bst_print(b1);

        bst * b2 = bst_new(6, "Pisa");

        bst_insert(b2, 1, "Bari");
        bst_insert(b2, 2, "Milano");
        bst_insert(b2, 4, "Milano");
        bst_insert(b2, 3, "Bologna");
        bst_insert(b2, 5, "Torino");
        bst_insert(b2, 78, "Siracusa");
        bst_insert(b2, 9, "Bari");

        bst_print(b2);

        sottoinsieme(b1,b2);





    return EXIT_SUCCESS;
}
