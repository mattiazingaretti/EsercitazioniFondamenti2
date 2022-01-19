#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "queue.h"


int main(int argc, char** argv) {

        BST * b = BST_new();

        BST_insert(b, 3);
        BST_insert(b, 12);
        BST_insert(b, 7);
        BST_insert(b, 5);
        BST_insert(b, 1);
        BST_insert(b, 7);
        BST_insert(b, 15);
        BST_insert(b, 1);
        BST_insert(b, 8);
        BST_insert(b, 7);
        BST_insert(b, 12);

        printf("Albero: \n");
        BST_print(b);

        BST * b2 = BST_new();

        BST_insert(b2, 13);
        BST_insert(b2, 5);
        BST_insert(b2, 20);
        BST_insert(b2, 3);
        BST_insert(b2, 7);
        BST_insert(b2, 25);
        BST_print(b2);

   /*     printf("\nRicerca valore: \n");
        for (int k=0; k<20; k++){
            if (BST_find(b,k)==NULL)
                printf("Nodo con chiave %d NON trovato\n", k);
            else
                printf("Nodo con chiave %d trovato\n", k);
        }*/


        printf("\nIntersezione tra due BST\n");
            queue* l = BSTintersezione(b, b2);
            queueItem *cur = l->head;
            printf("[ ");
            while (cur != NULL) {
                BinNode* b = (BinNode*) cur->item;
                printf("%d, ", (b->key));
                    cur = cur->next;
            }
            printf("] \n");

 /*       printf("\nRicerca massimo: \n");
        for (int level=1; level<20; level++){
            int max = maxOnLevel(b,level);

            if (max == -1)
                printf("Livello %d vuoto\n", level);
            else
                printf("Valore massino nel livello %d: %d\n",level, max);
        }*/

        BST_delete(b);
}
