#ifndef BST_H
#define	BST_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct BinNode {
    int coordinates[2];
    struct BinNode * left;
    struct BinNode * right;
} BinNode;

typedef struct BST {
        BinNode * root;
        int size;
} BST;

BST * BST_new();
BinNode * BST_insert(BST * b, int x, int y);
BinNode* BST_insert_aux(BinNode* nodo, int x,int y);
int aligned_aux(BinNode* nodo, int x,int cont);
int rangeQ_aux(BinNode* nodo, int x1,int y1,int x2,int y2,int cont);


void BST_delete(BST * h);
void BST_print(BST * h);

int aligned(BST * b, int x);
int rangeQ(BST * b, int x1, int y1, int x2, int y2);


#ifdef	__cplusplus
}
#endif

#endif	/* BST_H */

