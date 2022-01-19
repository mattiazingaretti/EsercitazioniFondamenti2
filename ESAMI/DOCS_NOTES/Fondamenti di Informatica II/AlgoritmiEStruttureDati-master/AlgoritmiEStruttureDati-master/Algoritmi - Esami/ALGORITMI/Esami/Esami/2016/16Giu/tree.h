#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct node_tree {
    int value;
    struct node_tree * firstChild;
    struct node_tree * nextSibling;
} node_tree;

typedef struct res{
    node_tree* nodo;
    int completo;
    int altezza;
}res;


node_tree * new_node_tree(int info);

int get_node_info(node_tree * node);

void set_firstChild_child(node_tree * n, node_tree * firstChild);
node_tree * get_firstChild_child(node_tree * n);

void set_nextSibling(node_tree * n, node_tree * nextSibling);
node_tree * get_nextSibling(node_tree * n);

res* new_res(node_tree* nodo,int altezza,int completo);

node_tree* max_sotto_albero_completo(node_tree* n,int k);
res* max_sotto_albero_completo_aux(node_tree* nodo, int k);
res* max_child(res** result,int k);
res** child_result(node_tree* nodo, int k);

void print_tree(node_tree * n);

void delete_tree(node_tree * n);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

