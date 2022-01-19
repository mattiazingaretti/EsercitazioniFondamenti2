#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


node_tree * build_one() {

    node_tree * root = node_tree_new("root");
    node_tree * a = node_tree_new("root");
    node_tree * b = node_tree_new("root");
    node_tree * c = node_tree_new("m");
    node_tree * f = node_tree_new("claudia");
    node_tree * d = node_tree_new("root");
    node_tree * e = node_tree_new("e");
    //node_tree * f = node_tree_new(5, 1, "f");
    //node_tree * g = node_tree_new(10, 1, "g");
    //node_tree * h = node_tree_new(17, 1, "h");

    set_first_child(root, a);
    set_next_sibling(a, b);
    //set_first_child(b, f);
    //set_first_child(f,g);
    //set_next_sibling(g,h);
    set_next_sibling(b, c);

    set_first_child(a, d);
    set_next_sibling(d, e);

    set_first_child(e, f);

    return root;
}

int main() {

    // printf("Building tree...\n");
    node_tree * root = build_one();

    stampo_percorso(root,"claudia");
    //stampa_percorsi_etichette(root, "c1");
    // printf("\nDeleting tree...\n");

    return EXIT_SUCCESS;
}
