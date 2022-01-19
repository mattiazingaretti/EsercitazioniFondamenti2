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

typedef struct res{
    int altezza;
    int key;
}res;

res* new_res(int key,int altezza);
void is_avl(node_tree* n);
res* verifica_avl_calcolo_altezza(node* nodo, int valore, int altezza);
node_tree * new_node_tree(int info);

int get_node_info(node_tree * node);

void set_left_child(node_tree * n, node_tree * left);
node_tree * get_left_child(node_tree * node_tree);

void set_right_child(node_tree * n, node_tree * right);
node_tree * get_right_child(node_tree * right);

void print_tree(node_tree * n);



void delete_tree(node_tree * node_tree);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

