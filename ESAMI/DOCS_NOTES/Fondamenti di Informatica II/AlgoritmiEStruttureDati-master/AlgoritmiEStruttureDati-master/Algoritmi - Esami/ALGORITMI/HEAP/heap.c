#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "_heap.h"

heap * heap_new(HEAP_TYPE is_min_heap, int capacity) {
	_heap* h = malloc(sizeof(_heap));
	h->size = capacity;
	h->used = 0;
	h->is_min_heap = is_min_heap;
	h->array = malloc(h->size*sizeof(_heap_entry*));
	return (heap*) h;
}

HEAP_TYPE heap_type(heap * hh) {
	_heap* h = hh;
	if(h->is_min_heap == 1){
		return MIN_HEAP;
	}
	return MAX_HEAP;
}

int heap_peek(heap * hh) {
	_heap * h = hh;
	return h->array[0]->key;
}

heap_entry * heap_add(heap * hh, int key) {
	_heap* h = hh;
	if( h->used >= h->size){
		h-> array = realloc(h->array, 2*h->size*sizeof(_heap_entry*));
	}
	_heap_entry* nodo = malloc(sizeof(_heap_entry));
	nodo->key = key;
	nodo->position = h->used;
	h->array[h->used]= nodo;
	h->used ++;
	int i = h->used -1 ;
	int j = (i-1)/2;
	if(h->is_min_heap == 1){
		while(h->array[i]->key < h-> array[j]->key){
			h->array[j]->position = i;
			h->array[i]->position = j;
			int val = h->array[i]->key;
			h->array[i]->key = h->array[j]->key;
			h->array[j]->key = val;
			i=j;
			j= (i-1)/2;
		}
	}
	else{
		while(h->array[i]->key > h-> array[j]->key){
			h->array[j]->position = i;
			h->array[i]->position = j;
			int val = h->array[i]->key;
			h->array[i]->key = h->array[j]->key;
			h->array[j]->key = val;
			i=j;
			j= (i-1)/2;
		}
	}

	return h->array[i];
}

int get_key_entry(heap_entry * ee) {
	_heap_entry* e = ee;
	return e ->key;
}

int heap_size(heap * hh) {
	_heap * h = hh;
	return h->used;
}
int get_min_child(_heap* h, int i){
	if(2*i +1 >= h->used){  //se non ha figli->foglia
		return -1;
	}
	if(2*i+2 == h->used){
		return 2*i +1;
	}
	if(h->array[2*i +1]->key < h->array[2*i +2]->key){
		return 2*i +1;
	}
	else{
		return 2*i + 2;
	}
}

int get_max_child(_heap* h, int i){
	if(2*i +1 >= h->used){  //se non ha figli->foglia
		return -1;
	}
	if(2*i+2 >= h->used){
		return 2+i +1;
	}
	if(h->array[2*i +1]->key > h->array[2*i +2]->key){
		return 2*i +1;
	}
	else{
		return 2*i + 2;
	}
}

int heap_poll(heap * hh) {
	_heap* h = hh;
	int key = h->array[0]->key;
	_heap_entry* e = h->array[0];
	h->array[0] = h->array[h->used-1];
	free(e);
	h->used --;
	int i =0;
	if(h->is_min_heap == 1){
		int j = get_min_child(h, 0);
		while(j != -1 && (h->array[i]->key > h->array[j]->key)){
			h->array[j]->position = i;
			h->array[i]->position = j;
			int val = h->array[i]->key;
			h->array[i]->key = h->array[j]->key;
			h->array[j]->key = val;
			i = j;
			j= get_min_child(h, i);
		}
	}
	else{
		int j = get_max_child(h, 0);
		while(j != -1 && (h->array[i]->key < h->array[j]->key)){
			h->array[j]->position = i;
			h->array[i]->position = j;
			int val = h->array[i]->key;
			h->array[i]->key = h->array[j]->key;
			h->array[j]->key = val;
			i = j;
			j= get_max_child(h, i);
		}
	}
	return key;
}

void heap_delete(heap * hh) {
	_heap* h = hh;
	int i ;
	for(i=0; i < h->size; i++){
		free(h->array[i]);
	}
	free(h->array);
	free(h);
}

heap * array2heap(int * array, int size, HEAP_TYPE is_min_heap) {
    heap* h =heap_new(is_min_heap, size);
    _heap* hh = h;

    //int j;
    //for(j=0; j< size; j++){
    //    heap_add(h,array[j]);
    //}
    return (heap*) hh;
}

void heap_print(heap * hh) {
	_heap* h = hh;
	int i;
	for(i=0; i< h->used; i++){
		printf(" %d", h->array[i]->key);
	}
	printf("\n");
}

void controllofratelli(int* array, int x){
    if(x%2==0 && (array[x] < array[x-1])){
        int val = array[x];
        array[x] = array[x-1];
        array[x-1]= val;
    }

}


void heap_sort(int * array, int size) {
    int i;
    for(i = size-1; i > 0 ; i--){
        int j = (i-1)/2;
        int x =i;
        printf("figlio %d, %d\n", i, array[i]);
        printf("padre %d, %d\n", j, array[j]);
        while(array[x] < array[j]){
            int val = array[x];
            array[x] = array[j];
            array[j] = val;
            x =j;
            j = (x-1)/2;
        }
        controllofratelli(array, x);
    }
	return;
}

void heap_update_key(heap * hh, heap_entry * ee, int key) {
    int i;
    _heap* h= hh;
    _heap_entry* e= ee;
    int j;
    for(i=0; i< h->used; i++){
        if(h->array[i] == e){
            h->array[i]->key = key;
            j=(h->array[i]->position) -1;
        }
    }
    if(h->is_min_heap == 1){
        int x = get_min_child(h,j);
        while(x != -1 && (h->array[j]->key > h-> array[x]->key)){
			h->array[x]->position = j;
			h->array[j]->position = x;
			int val = h->array[x]->key;
			h->array[x]->key = h->array[j]->key;
			h->array[j]->key = val;
			j=x;
			x= get_min_child(h,j);
            printf("%d\n", x);
		}
        //da completare il caso che bisogni scambiare verso l'alto
    }
    //da completare il caso di max heap sia scambi verso l'alto che verso il basso
	return;
}

