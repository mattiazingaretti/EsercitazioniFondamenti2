#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


node_tree * build_one() {

    node_tree * root = new_node_tree(7);
    node_tree * a = new_node_tree(0);
    node_tree * b = new_node_tree(6);
    node_tree * c = new_node_tree(2);

    node_tree * d = new_node_tree(1);
    node_tree * e = new_node_tree(3);
    node_tree * g = new_node_tree(5);

    set_firstChild_child(root, a);
    set_nextSibling(a, b);
    set_firstChild_child(b, c);
    set_nextSibling(c,d);

    set_firstChild_child(c, e);

    set_nextSibling(e, g);


    return root;
}



int main(int argc, char** argv) {


        // printf("Building tree...\n");
        node_tree * root = build_one();

        // printf("\nPrinting tree...\n");
        print_tree(root);

        node_tree* nodo=max_sotto_albero_completo(root,2);
        printf("la radice sotto albero completo max [%d]\n", nodo->value);

        // printf("\nDeleting tree...\n");
        delete_tree(root);







    return EXIT_SUCCESS;
}

