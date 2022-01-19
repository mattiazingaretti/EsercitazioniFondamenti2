#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

node_tree * build_one() {

    node_tree * root = new_node_tree(10);
    node_tree * a = new_node_tree(6);
    node_tree * b = new_node_tree(5);
    node_tree * c = new_node_tree(9);

    node_tree * d = new_node_tree(2);
    node_tree * e = new_node_tree(8);

    set_first_child(root, a);
    set_next_sibling(a, b);
    set_next_sibling(b, c);

    set_first_child(a, d);
    set_next_sibling(d, e);

    return root;
}

node_tree * build_two() {

    node_tree * root = new_node_tree(10);
    node_tree * a = new_node_tree(6);
    node_tree * b = new_node_tree(5);
    node_tree * c = new_node_tree(9);

    node_tree * d = new_node_tree(2);
    node_tree * e = new_node_tree(8);

    node_tree * f = new_node_tree(3);
    node_tree * g = new_node_tree(11);

    set_first_child(root, a);
    set_next_sibling(a, b);
    set_next_sibling(b, c);

    set_first_child(a, d);
    set_next_sibling(d, e);

    set_first_child(c, f);
    set_next_sibling(f, g);

    return root;
}

int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Richiesto argomento: {tree, parse, max, postorder}\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "tree") == 0) {

        // printf("Building tree...\n");
        node_tree * root = build_one();

        // printf("\nPrinting tree...\n");
        print_tree(root);

        tree* antenato = getLCA(root, f, g);
        printf("Antenato di 3 e 11 é %d\n", antenato->info);

}

    return EXIT_SUCCESS;
}

