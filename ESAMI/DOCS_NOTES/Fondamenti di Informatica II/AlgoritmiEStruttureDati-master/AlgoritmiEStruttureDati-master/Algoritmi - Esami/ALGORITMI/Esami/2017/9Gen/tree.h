#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node{
    char* etichetta;
    struct node* firstChild;
    struct node* nextSibling;
}node;

node_tree* node_tree_new(char* etichetta);

char* get_etichetta(node_tree* n);

void set_next_sibling(node_tree*n,node_tree* nextSibling);

void set_first_child(node_tree* n,node_tree* firstChild);

node_tree* get_first_child(node_tree*n);

node_tree* get_next_sibling(node_tree*n);

//void print_tree(node_tree * node_tree);

void stampo_percorso(node_tree* n,char* s);
void cerca_percorso(node* nodo, char* s,char*percorso);
char* aggiorna_percorso(char* s1,char* s2);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */

