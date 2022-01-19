#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"



int main(int argc, char** argv) {
    node_tree * root = new_node_tree(10);
    node_tree * a = new_node_tree(1);
    node_tree * b = new_node_tree(4);
    node_tree * c = new_node_tree(5);

    node_tree * d = new_node_tree(13);
    node_tree * e = new_node_tree(7);


    set_first_child(root, a);
    set_next_sibling(a, b);

    set_next_sibling(b, c);

    set_first_child(a, d);
    set_next_sibling(d, e);


    // printf("Building tree...\n");

    nodo_print(root,d,e);
    //stampa_percorsi_etichette(root, "c1");
    // printf("\nDeleting tree...\n");
    delete_tree(root);

    return EXIT_SUCCESS;
}
