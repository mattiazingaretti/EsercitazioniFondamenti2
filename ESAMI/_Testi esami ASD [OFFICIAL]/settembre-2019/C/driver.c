#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

void print_help() {
    printf("Richiesto argomento: {ordina, outer_range, altezza}\n");
}

int main(int argc, char** argv) {

    if (argc != 2) {
        print_help();
        return EXIT_FAILURE;
    }
    
    int exit_code = EXIT_FAILURE;
    
    bst * b = bst_new(6, "Pisa");

    bst_insert(b, 3, "Roma");
    bst_insert(b, 12, "Milano");
    bst_insert(b, 7, "Bologna");
    bst_insert(b, 5, "Firenze");
    bst_insert(b, 1, "Torino");
    bst_insert(b, 15, "Siracusa");
    bst_insert(b, 8, "Bari");


    if (strcmp(argv[1], "ordina") == 0) {
        // Test ordinamento
        printf("BST di partenza:\n");
        bst_print(b);
        printf("\n");
        printf("Test ordinamento: il programma dovrebbe stampare [1, 3, 5, 6, 7, 8, 12, 15]\n");
        printf("Il tuo programma stampa ");
        ordina(b);                
        printf("\n\n");
        exit_code = EXIT_SUCCESS;
    } else if (strcmp(argv[1], "outer_range") == 0) {
        // Test outer_range
        printf("BST di partenza:\n");
        bst_print(b);
        printf("\n");
        printf("Test outer_range con chiavi esterne all'intervallo [5, 12]: il programma dovrebbe stampare [1, 3, 15]\n");
        printf("Il tuo programma stampa "); 
        outer_range(b, 5, 12);               
        printf("\n\n");
        exit_code = EXIT_SUCCESS;
    } else if (strcmp(argv[1], "altezza") == 0) {
        // Test altezza
        printf("BST di partenza:\n");
        bst_print(b);
        printf("\n");
        printf("Test altezza: il programma dovrebbe stampare: 3\n");
        printf("Il tuo programma stampa %d\n", altezza(b));                
        printf("\n");
        exit_code = EXIT_SUCCESS;
    } else print_help();
    
    return exit_code;
}
