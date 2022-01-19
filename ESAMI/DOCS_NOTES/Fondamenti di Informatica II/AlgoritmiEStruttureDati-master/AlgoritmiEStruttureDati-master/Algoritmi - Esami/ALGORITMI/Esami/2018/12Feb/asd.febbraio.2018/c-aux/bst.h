#ifndef BST_H
#define	BST_H

/* lunghezza max di una parola, incluso terminatore 0; modificabile */
#define MAXLEN 64

typedef struct BinNode {
    char *key;
    int cont;
    struct BinNode *left;
    struct BinNode *right;
} BinNode;

typedef struct BST {
        BinNode *root;
//        int size;
} BST;

BST * BST_new();
BinNode *BST_insert(BST *b, char *k);
int BST_find(BST * b, char *k);
void BST_print(BST * b);
char *mostFrequentString(BST *t);
int isBalanced(BST *t);

void BST_insert_aux(BinNode* nodo,BinNode* new);
int BST_find_aux(BinNode* nodo, char* k);
int isBalanced_aux(BinNode* nodo, int altezza);
char* mostFrequentString_aux(BinNode* nodo,char* max, int max_cont);

static char *toUppercase(char *s);
static BinNode *BST_node_new(char *k);
static void BST_print_aux(BinNode * t, int level, char pos);

#endif	/* BST_H */

