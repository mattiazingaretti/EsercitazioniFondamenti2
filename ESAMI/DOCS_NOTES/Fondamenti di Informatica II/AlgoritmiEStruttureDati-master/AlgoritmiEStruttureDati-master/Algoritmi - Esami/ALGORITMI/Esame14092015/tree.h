#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct res{
    int value;
    tree* puntatore;
}res;

typedef struct tree{
    int info;
    struct tree* firstchild;
    struct tree* nextsibling;
}tree;

node_tree * new_node_tree(int info);

int get_node_info(node_tree * node);

void set_first_child(node_tree * node, node_tree * firstChild);
node_tree * get_first_child(node_tree * node_tree);

void set_next_sibling(node_tree * node, node_tree * set_next_sibling);
node_tree * get_next_sibling(node_tree * node_tree);

void print_tree(node_tree * node_tree);

void delete_tree(node_tree * node_tree);

tree* getLCA(node_tree* root, node_tree* x, node_tree* y);
res* _getLCA(tree* nodo, tree* x, tree* y);
res* wrapperSuiFigli(tree* nodo, tree* x , tree* y);
res* new_struct(int value, tree* puntatore);



#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

