#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node{
    int key;
    struct node* right;
    struct node* left;
}node;



node_tree * new_node_tree(int info);

int get_node_info(node_tree * node);

void set_left_child(node_tree * n, node_tree * left);
node_tree * get_left_child(node_tree * node_tree);

void set_right_child(node_tree * n, node_tree * right);
node_tree * get_right_child(node_tree * right);

void print_tree(node_tree * n);

int testBello(node_tree* n);
int verifica(node* nodo);

void delete_tree(node_tree * node_tree);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

