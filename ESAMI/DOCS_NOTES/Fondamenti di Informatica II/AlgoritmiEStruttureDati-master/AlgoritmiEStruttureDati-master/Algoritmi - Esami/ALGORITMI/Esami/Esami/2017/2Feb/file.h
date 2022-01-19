#ifndef TREE_H
#define	TREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef void node_tree;

typedef struct node{
    int size;
    int cartella;
    char* nome;
    struct node* firstChild;
    struct node* nextSibling;
}node;

node_tree * new_node_tree(int size, int cartella, char* name);

int get_node_size(node_tree * node);

void set_first_child(node_tree * node, node_tree * firstChild);
node_tree * get_first_child(node_tree * node_tree);

void set_next_sibling(node_tree * node, node_tree * set_next_sibling);
node_tree * get_next_sibling(node_tree * node_tree);

//void print_tree(node_tree * node_tree);

void delete_tree(node_tree * node_tree);

void stampa_percorsi(node_tree* root, int min);
int peso(node* nodo, int min, char* percorsoParz);
int pesoSottoCartelle(node* nodo, int min, char* percorso);
char* aggiornaPercorso(char* s1, char* s2);
int oppure(node* nodo, int min, char* percorsoParz);
void stampa_percorsi_etichette(node_tree* root, char* etichetta);
void etichette(node* nodo, char* etichetta, char* percorsoParz);

#ifdef	__cplusplus
}
#endif

#endif	/* TREE_H */


