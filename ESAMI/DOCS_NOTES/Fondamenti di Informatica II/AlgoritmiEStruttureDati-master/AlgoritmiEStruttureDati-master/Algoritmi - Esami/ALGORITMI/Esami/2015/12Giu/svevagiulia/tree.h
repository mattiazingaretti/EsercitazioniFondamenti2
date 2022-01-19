#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node{
    char* etichetta;
    struct node* right;
    struct node* left;
}node;

typedef struct res{
    char* per_max;
    char* per_min;
}res;

node_tree * new_node_tree(char* etichetta);

res* new_res(char* percorsoMax,char* percorsoMin);

char* get_node_info(node_tree * node);

void set_left_child(node_tree * n, node_tree * left);
node_tree * get_left_child(node_tree * node_tree);

void set_right_child(node_tree * n, node_tree * right);
node_tree * get_right_child(node_tree * right);

void print_tree(node_tree * n);

res* verifica(node* nodo,char* buffer);

char* aggiorna_percorso(char* s1, char* s2);

void delete_tree(node_tree * node_tree);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

