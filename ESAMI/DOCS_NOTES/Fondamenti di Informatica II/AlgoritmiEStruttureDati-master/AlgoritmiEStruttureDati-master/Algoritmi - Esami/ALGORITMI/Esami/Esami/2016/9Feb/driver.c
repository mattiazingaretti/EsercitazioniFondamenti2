#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"



node_tree * build_two() {

    node_tree * root = new_node_tree(20);
    node_tree * a = new_node_tree(40);
    node_tree * b = new_node_tree(10);
    node_tree * c = new_node_tree(5);

    node_tree * d = new_node_tree(11);
    node_tree * e = new_node_tree(7);

    node_tree * f = new_node_tree(25);
    node_tree * g = new_node_tree(42);

    set_left_child(root, b);
    set_right_child(root, a);

    set_left_child(b, c);
    set_right_child(b,d);

    set_right_child(c, e);

    set_left_child(a,f);
    set_right_child(e,g);

    return root;
}

int main(int argc, char** argv) {


        // printf("Building tree...\n");
        node_tree * root = build_two();


        // printf("\nPrinting tree...\n");
        print_tree(root);

        is_avl(root);

        // printf("\nDeleting tree...\n");
        delete_tree(root);



    return EXIT_SUCCESS;
}

