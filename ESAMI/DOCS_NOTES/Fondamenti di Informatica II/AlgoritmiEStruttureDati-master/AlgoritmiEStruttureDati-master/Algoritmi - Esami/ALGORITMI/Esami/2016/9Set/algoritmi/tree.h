#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node {
    int value;
    struct node * left;
    struct node * right;
} node;


node_tree * new_node_tree(int info);

int get_node_info(node_tree * node);

void set_left_child(node_tree * node, node_tree * left);
node_tree * get_left_child(node_tree * n);

void set_right_child(node_tree * node, node_tree * right);
node_tree * get_right(node_tree * n);

void verifica_min(node *nodo,int* array, int size);
void inizializza_array(int* array,int size);
int num_nodi_albero(node*nodo);
int min_val(node_tree* n);

void print_tree(node_tree * n);

void delete_tree(node_tree * n);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

