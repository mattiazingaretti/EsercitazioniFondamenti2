#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "queue.h"
#include "max_level.h"

int max_level(node_tree * n) {
    if( n == NULL) return -1;
    queue* coda = new_queue();
    int livello = 0;
    int somma = 0;
    int sommamax = get_node_info(n);
    queue_enqueue(coda, n);
    while(get_first_child(n) != NULL){
        queue* coda2 = new_queue();
        node_tree* nodo = n;
        while(nodo != NULL){
            somma += aggiunginodiacoda(coda2, get_first_child(nodo));
            printf("somma %d\n", somma);
            nodo = get_next_sibling(nodo);
        }
        if(somma > sommamax){
            sommamax = somma;
            livello ++;
            printf("%d\n" , livello);
            coda = coda2;
        }
        somma = 0;
        free(coda2);
        n = get_first_child(n);
    }
	return livello;
}

int aggiunginodiacoda(queue* coda, node_tree* n){
    if( n == NULL) return 0;
    int somma = 0;
    while(n != NULL){
        somma += get_node_info(n);
        printf("somma nell'aggiungi coda %d\n", somma);
        queue_enqueue(coda, n);
        n = get_next_sibling(n);
    }
    printf("somma tot nell'aggiungi coda %d\n", somma);
    return somma;
}
