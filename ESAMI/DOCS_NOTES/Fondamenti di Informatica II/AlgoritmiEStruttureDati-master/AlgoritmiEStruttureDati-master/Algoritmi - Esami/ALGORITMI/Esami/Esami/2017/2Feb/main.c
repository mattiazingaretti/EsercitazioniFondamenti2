#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"


node_tree * build_one() {

    node_tree * root = new_node_tree(10, 1, "root");
    node_tree * a = new_node_tree(10, 1, "a");
    node_tree * b = new_node_tree(10, 1, "b");
    node_tree * c = new_node_tree(10, 1, "c");

    node_tree * d = new_node_tree(13, 1, "d");
    node_tree * e = new_node_tree(1, 1, "e");
    node_tree * f = new_node_tree(5, 1, "f");
    node_tree * g = new_node_tree(10, 1, "g");
    node_tree * h = new_node_tree(17, 1, "h");

    set_first_child(root, a);
    set_next_sibling(a, b);
    set_first_child(b, f);
    set_first_child(f,g);
    set_next_sibling(g,h);
    set_next_sibling(b, c);

    set_first_child(a, d);
    set_next_sibling(d, e);

    return root;
}

int main(int argc, char** argv) {

    // printf("Building tree...\n");
    node_tree * root = build_one();

    nodo_print(root, 12);
    //stampa_percorsi_etichette(root, "c1");
    // printf("\nDeleting tree...\n");
    delete_tree(root);

    return EXIT_SUCCESS;
}

