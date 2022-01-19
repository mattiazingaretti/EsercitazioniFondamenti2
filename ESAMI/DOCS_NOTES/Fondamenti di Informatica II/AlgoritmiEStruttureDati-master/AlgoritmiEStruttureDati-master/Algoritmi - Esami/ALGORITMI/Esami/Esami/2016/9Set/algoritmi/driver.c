#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"


node_tree * build_one() {

    node_tree * root = new_node_tree(7);
    node_tree * a = new_node_tree(0);
    node_tree * b = new_node_tree(6);
    node_tree * c = new_node_tree(2);

    node_tree * d = new_node_tree(3);
    node_tree * e = new_node_tree(5);

    node_tree * f = new_node_tree(1);
    node_tree * g = new_node_tree(4);

    set_left_child(root, a);
    set_right_child(root, b);
    set_left_child(a, c);

    set_right_child(a, d);
    set_left_child(c, e);

    set_left_child(b,f);
    set_right_child(b,g);

    return root;
}



int main(int argc, char** argv) {


        // printf("Building tree...\n");
        node_tree * root = build_one();

        // printf("\nPrinting tree...\n");
        print_tree(root);

        int valore=min_val(root);
        printf("Valore minimo non presente nell'albero: [%d]\n",valore);

        // printf("\nDeleting tree...\n");
        delete_tree(root);







    return EXIT_SUCCESS;
}

