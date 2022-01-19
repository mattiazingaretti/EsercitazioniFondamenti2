#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"



node_tree * build_two() {

    node_tree * root = new_node_tree("root");
    node_tree * a = new_node_tree("a");
    node_tree * b = new_node_tree("b");
    node_tree * c = new_node_tree("c");

    node_tree * d = new_node_tree("d");
    node_tree * e = new_node_tree("e");

    node_tree * f = new_node_tree("f");
    node_tree * g = new_node_tree("g");

    set_left_child(root, b);
    set_right_child(root, a);

    set_left_child(b, c);
    set_right_child(b,d);

    set_right_child(c, e);
    set_left_child(e,g);

    set_left_child(a,f);
    //set_right_child(a,g);

    return root;
}

int main(int argc, char** argv) {


        // printf("Building tree...\n");
        node_tree * root = build_two();


        // printf("\nPrinting tree...\n");
        print_tree(root);



        // printf("\nDeleting tree...\n");
        delete_tree(root);



    return EXIT_SUCCESS;
}
