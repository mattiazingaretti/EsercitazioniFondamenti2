#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"


void print_help() {
    printf("Richiesto argomento: {bst, predecessor, tree, balanced, avl}\n");
}

int main(int argc, char** argv) {



        bst * b1 = bst_new(6, "Pisa");

        bst_insert(b1, 3, "Torino");
        bst_insert(b1, 12, "Milano");
        bst_insert(b1, 7, "Bologna");
        bst_insert(b1, 5, "Firenze");
        bst_insert(b1, 1, "Torino");
        bst_insert(b1, 15, "Siracusa");
        bst_insert(b1, 8, "Bari");

        bst_print(b1);

        bst * b2 = bst_new(6, "Pisa");

        bst_insert(b2, 8, "Bari");
        bst_insert(b2, 4, "Milano");
        bst_insert(b2, 12, "Milano");
        bst_insert(b2, 7, "Bologna");
        bst_insert(b2, 3, "Torino");
        bst_insert(b2, 23, "Siracusa");
        bst_insert(b2, 9, "Bari");

        bst_print(b2);

        list_print(intersezione_bst(b1,b2));





    return EXIT_SUCCESS;
}
