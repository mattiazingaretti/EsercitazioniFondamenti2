#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"



node_tree * new_node_tree(char* etichetta) {
	node * n = malloc(sizeof(node));
	n->etichetta=etichetta;
	n->right=NULL;
	n->left = NULL;

	return (node_tree *) n;
}

res* new_res(char* percorsoMax,char* percorsoMin){
    res* t=malloc(sizeof(res));
    t->per_max=percorsoMax;
    t->per_min=percorsoMin;

}

char* get_node_info(node_tree * n) {
	return ((node *) n)->etichetta;
}

void set_right_child(node_tree * n, node_tree * right) {
	((node *) n)->right= right;
}

node_tree * get_right_child(node_tree * n) {
	return ((node *) n)->right;
}

void set_left_child(node_tree * n, node_tree * left) {
	((node *) n)->left = left;
}

node_tree * get_left_child(node_tree * n) {
	return ((node *) n)->left;
}

void delete_tree(node_tree * nt) {

	if (nt == NULL)
		return;

	node * n = (node *) nt;

	// printf("Deleting node: %d\n", n->value);

	delete_tree(n->right);
	delete_tree(n->left);
	free(n);
}

void print_tree(node_tree*n){
    if(n==NULL){
        return;
    }
    node* nodo=n;
    res* ris=verifica(nodo,"");
    printf("Percorso max [%s] e Percorso min [%s]\n", ris->per_max,ris->per_min);



}

res* verifica(node* nodo,char* buff){
    res* perc_sx;
    res* perc_dx;

    if(nodo==NULL){
        return new_res("","");
    }
    char* buffer=aggiorna_percorso(buff,nodo->etichetta);

    perc_sx=verifica(nodo->left,buffer);            // perc_max fatto da max e min
    perc_dx=verifica(nodo->right,buffer);


    if(strlen(perc_sx->per_max)==0 && strlen(perc_dx->per_max)!=0){
        return new_res(perc_dx->per_max,perc_dx->per_min);
    }
    if(strlen(perc_sx->per_max)!=0 && strlen(perc_dx->per_max)==0){
        return new_res(perc_sx->per_max,perc_sx->per_min);
    }

    if(strlen(perc_sx->per_max)==0 && strlen(perc_dx->per_max)==0){
        return new_res(buffer,buffer);
    }
    if(strlen(perc_sx->per_max)>=strlen(perc_dx->per_max)){
        if(strlen(perc_dx->per_min)<= strlen(perc_sx->per_min)){
            return new_res(perc_sx->per_max, perc_dx->per_min);
        }
        else{

            return new_res(perc_sx->per_max, perc_sx->per_min);
        }
    }
    else{
        if(strlen(perc_dx->per_min)<= strlen(perc_sx->per_min)){
            return new_res(perc_dx->per_max, perc_dx->per_min);
        }
        else{

            return new_res(perc_dx->per_max, perc_sx->per_min);
        }


    }

}

char* aggiorna_percorso(char* s1, char* s2){
    char* res=malloc(sizeof(strlen(s1)+strlen(s2)+2));
    res=strcat(res,s1);
    res=strcat(res,"/");
    res=strcat(res,s2);
    return res;
}


