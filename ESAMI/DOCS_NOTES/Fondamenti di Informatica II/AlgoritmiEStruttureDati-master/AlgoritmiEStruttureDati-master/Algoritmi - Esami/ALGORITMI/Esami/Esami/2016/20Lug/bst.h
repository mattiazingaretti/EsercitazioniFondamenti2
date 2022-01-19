#ifndef BST_H
#define	BST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct bst bst;

typedef struct bst_node{
    int key;
    void* value;
    struct bst_node* left;
    struct bst_node* right;
}bst_node;

typedef struct bst{
    struct bst_node* root;
}bst;

typedef struct list{
    int key;
    struct list* next;
}list;

bst * bst_new(int k, void * v);
void bst_insert(bst * t, int k, void * v);
void * bst_find(bst * t, int k);
void bst_remove(bst * t, int k);
int bst_find_min(bst * n);
void bst_remove_min(bst * n);

bst_node* bst_remove_min_aux(bst_node* nodo);
bst_node* bst_remove_aux(bst_node* nodo, int k);
int bst_find_min_aux(bst_node* nodo);
void* bst_find_aux(bst_node* nodo,int k);
void bst_insert_aux(bst_node* nodo,int k, void* v);
bst_node* bst_new_node(int k, void* v);
bst_node* find_min_node(bst_node* nodo);
void bst_delete_aux(bst_node* nodo);
void bst_print_aux(bst_node* nodo, int altezza);
bst_node* bst_predecessor_aux(bst_node* nodo, int k);

void sottoinsieme(bst* a,bst*b);
int num_nodi(bst_node* nodo);
int aggiungi_bst(bst_node* nodo, int* array,int size);

void bst_delete(bst * h);
void bst_print(bst * h);

int bst_predecessor(bst * t, int k);

#ifdef	__cplusplus
}
#endif

#endif	/* BST_H */

