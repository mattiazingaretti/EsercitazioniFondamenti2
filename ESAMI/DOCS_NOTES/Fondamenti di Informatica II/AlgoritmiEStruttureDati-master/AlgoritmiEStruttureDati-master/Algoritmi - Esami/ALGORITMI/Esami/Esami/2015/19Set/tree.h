#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node{
    int key;
    struct node* firstChild;
    struct node* nextSibling;
}node;

typedef struct tree{
    struct node* nodo;
    int info;
}tree;

node_tree * new_node_tree(int key);

int get_node_size(node_tree * node);

void set_first_child(node_tree * node, node_tree * firstChild);
node_tree * get_first_child(node_tree * node_tree);

void set_next_sibling(node_tree * node, node_tree * set_next_sibling);
node_tree * get_next_sibling(node_tree * node_tree);

//void print_tree(node_tree * node_tree);

void delete_tree(node_tree * node_tree);

void nodo_print(node_tree* n, node_tree* x, node_tree* y);

tree* lca(node* nodo,node* x, node* y);
tree* lca_2(node* nodo,node* x,node* y);


#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */
