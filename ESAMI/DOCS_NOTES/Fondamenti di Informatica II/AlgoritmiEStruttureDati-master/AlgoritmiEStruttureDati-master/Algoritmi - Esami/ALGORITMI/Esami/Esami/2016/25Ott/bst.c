#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

bst * bst_new(int k, void * v) {
    bst* b=malloc(sizeof(bst));
    b->root=bst_new_node(k,v);
	return b;
}

bst_node* bst_new_node(int k, void* v){
    bst_node* nodo=malloc(sizeof(bst_node));
    nodo->value=v;
    nodo->key=k;
    nodo->left=NULL;
    nodo->right=NULL;
    return nodo;
}

void bst_insert(bst * b, int k, void * v) {
    if(b==NULL) return;

    bst_insert_aux(b->root,k,v);
    return;
}

void bst_insert_aux(bst_node* nodo,int k, void* v){
    if(k==nodo->key){
        nodo->value=v;
    }
    bst_node* new=bst_new_node(k,v);
    if(k<nodo->key){
        if(nodo->left==NULL){
            nodo->left=new;
        }
        else{
            bst_insert_aux(nodo->left,k,v);
        }
    }
    else{
        if(nodo->right==NULL){
            nodo->right=new;
        }
        else{
            bst_insert_aux(nodo->right,k,v);
        }
    }
}

void * bst_find(bst * b, int k) {
    if (b==NULL) return NULL;
    return bst_find_aux(b->root,k);
}

void* bst_find_aux(bst_node* nodo,int k){
    if (nodo==NULL) return NULL;
    if(k==nodo->key){
        return nodo->value;
    }
    else if(k<nodo->key){
        return bst_find_aux(nodo->left,k);
    }
    else{
        return bst_find_aux(nodo->right,k);
    }
}

int bst_find_min(bst * b) {
    if(b==NULL) return -1;
	return bst_find_min_aux(b->root);
}

int bst_find_min_aux(bst_node* nodo){
    if(nodo->left==NULL){
        return nodo->key;
    }
    return bst_find_min_aux(nodo->left);
}

void bst_remove_min(bst * b) {
    if(b==NULL)return;
	b->root=bst_remove_min_aux(b->root);
}

bst_node* bst_remove_min_aux(bst_node* nodo){
    printf("ciao %d\n", nodo->key);
    if(nodo->left==NULL){
        bst_node* tmp=nodo->right;
        free(nodo);
        return tmp;
    }
    nodo->left=bst_remove_min_aux(nodo->left);
    return nodo;

}

void bst_remove(bst * b, int k) {
    if(b==NULL) return;
    b->root=bst_remove_aux(b->root,k);
	return;
}

bst_node* bst_remove_aux(bst_node* nodo, int k){
    if(k==nodo->key){
        if(nodo->left==NULL){
            bst_node* tmp=nodo->right;
            free(nodo);
            return tmp;
        }
        else if(nodo->right==NULL){
            bst_node* tmp=nodo->left;
            free(nodo);
            return tmp;
        }
        else{
            bst_node* tmp=nodo;
            nodo=find_min_node(tmp->right);

            bst_node* new=bst_new_node(nodo->key,nodo->value);
            new->left=tmp->left;
            new->right=bst_remove_min_aux(tmp->right);
            free(tmp);
            nodo=new;


        }
    }
    else{
        if(k<nodo->key){
            nodo->left=bst_remove_aux(nodo->left,k);
        }
        else if(k>nodo->key){
            nodo->right=bst_remove_aux(nodo->right,k);
        }
    }
    return nodo;

}

bst_node* find_min_node(bst_node* nodo){
    if(nodo->left==NULL){
        return nodo;
    }
    return find_min_node(nodo->left);
}

void bst_delete(bst * b) {
    if(b==NULL) return;
    bst_delete_aux(b->root);
    free(b);
	return;
}

void bst_delete_aux(bst_node* nodo){
    if(nodo==NULL) return;
    bst_delete_aux(nodo->left);
    bst_delete_aux(nodo->right);
    free(nodo);
}

void bst_print(bst * b){
    if(b==NULL) return;
    bst_print_aux(b->root,0);
	return;
}

void bst_print_aux(bst_node* nodo, int altezza){
    if(nodo==NULL) return;

    int i;
    for (i=0; i<altezza; i++){
        printf("-");
    }
    printf("%d\n",nodo->key);
    bst_print_aux(nodo->left,altezza+1);
    bst_print_aux(nodo->right,altezza+1);
}

int bst_predecessor(bst * b, int k) {
    if(b==NULL) return -1;
    bst_node* pred=bst_predecessor_aux(b->root,k);
    return pred->key;
}

bst_node* bst_predecessor_aux(bst_node* nodo, int k){
    if(nodo==NULL) return NULL;
    if(k<=nodo->key){
         return bst_predecessor_aux(nodo->left,k);
    }
    bst_node* n=bst_predecessor_aux(nodo->right,k);
    if(n==NULL){
        return nodo;
    }
    else{
        return n;
    }
}

list* new_list(int key){
    list* l=malloc(sizeof(list));
    l->key=key;
    l->next=NULL;
    return l;
}

void list_insert(list* l,int key){
    list* tmp=l;
    list* prec=NULL;
    list* new=new_list(key);
    while(tmp!=NULL && tmp->key<key){
        prec=tmp;
        tmp=tmp->next;
    }
    if(prec!=NULL){    //se tmp è null caso coda altrimenti inserimento in mezzo
        prec->next=new;
        new->next=tmp;
    }
    else{               //caso testa
        new->next=l;
        l=new;
    }
}

void list_print(list* l){
    if(l==NULL) return;
    list* tmp=l;
    while(tmp->next!=NULL){
        printf("%d ",tmp->next->key);
        tmp=tmp->next;
    }
    printf("\n");
}

list* intersezione_bst(bst* b1,bst* b2){
    list* l=malloc(sizeof(list));
    int n1=num_nodi(b1->root);
    int n2=num_nodi(b2->root);
    int array1[n1];
    int array2[n2];
    aggiungi_bst(b1->root,array1,0);
    aggiungi_bst(b2->root,array2,0);
    int i=0;
    int j=0;
    while(i< n1 && j< n2){
        if(array1[i]==array2[j]){
            list_insert(l,array1[i]);
            i++;
            j++;
        }
        else if(array1[i]<array2[j]){
            i++;
        }
        else{
            j++;
        }
    }
    return l;
}

int num_nodi(bst_node* nodo){
    if(nodo==NULL) return 0;
    return 1+num_nodi(nodo->left)+num_nodi(nodo->right);
}

int aggiungi_bst(bst_node* nodo, int* array,int i){
    if(nodo==NULL) return i;

    i=aggiungi_bst(nodo->left,array,i);
    array[i]=nodo->key;
    i++;
    i=aggiungi_bst(nodo->right,array,i);
    return i;

}


