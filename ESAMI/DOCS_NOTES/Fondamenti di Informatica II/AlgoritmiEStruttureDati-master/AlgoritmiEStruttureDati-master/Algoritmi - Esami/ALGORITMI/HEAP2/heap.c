#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "_heap.h"

heap * heap_new(HEAP_TYPE is_min_heap, int capacity) {
    _heap * h = malloc(sizeof(_heap));
    h->size = 0;
    h->used = 0;
    h-> is_min_heap = is_min_heap;
    h->array = malloc(capacity*sizeof(_heap_entry*));
	return (heap*) h;
}

HEAP_TYPE heap_type(heap * hh) {
	return ((_heap*)hh)->is_min_heap;
}

int heap_peek(heap * hh) {
    _heap* h = (_heap*) hh;
	return h->array[0]->key;
}

void ordina_heap_upheap(_heap* h, int i){
    int padre = (i-1)/2;
    printf("ordino elemento %d in posizione %d con padre in posizione %d\n", h->array[i]->key,i, padre);
    if(h->is_min_heap == 1){ // è un min heap
        while(i!=0 && (h->array[i]->key < h->array[padre]->key)){
            _heap_entry* temp = h->array[i];
            h->array[i] = h->array[padre];
            h->array[padre] = temp;
            h->array[i]->position = padre;
            h->array[padre]->position =i;
            i = padre;
            padre = (i-1)/2;
        }
    }
    else{
        while(i!=0 && (h->array[i]->key > h->array[padre]->key)){
            _heap_entry* temp = h->array[i];
            h->array[i] = h->array[padre];
            h->array[padre] = temp;
            h->array[i] = padre;
            h->array[padre]->position =i;
            i = padre;
            padre = (i-1)/2;
        }
    }
}


heap_entry * heap_add(heap * hh, int key) {
    _heap* h = (_heap*) hh;
    _heap_entry* new = malloc(sizeof(_heap_entry));
    new-> key = key;
    new->position = h->used;
    printf("aggiungo nuovo elemento in posizione %d\n", new->position);
    h->used ++;
    if(h->size < h->used){
        h->array = realloc(h->array, 2*h->used*sizeof(_heap_entry*));
        h->size = 2*(h->used);
    }
    h->array[new->position] = new;
    ordina_heap_upheap(h, new->position);
    heap_print(h);
    printf("nuova posizione di new %d\n", new->position);

	return (heap_entry*) new;
}

int get_key_entry(heap_entry * ee) {
    _heap_entry* e = (_heap_entry*) ee;
	return e->key;
}

int heap_size(heap * hh) {
	return ((_heap*) hh)->used;
}

int heap_poll(heap * hh) {
    _heap* h = (_heap*) hh;
    _heap_entry* x = h->array[0];
    h->array[0] = h->array[h->used -1];
    h->array[0]->position = 0;
    h->used --;
    free(x);
    ordina_heap_downheap(h, h->array[0]);
	return h->array[0]->key;
}

int find_minfiglio(_heap* h, int i){
    if(h->used <= 2*i +2){
        return 2*i +1;
    }
    else{
        if(h->array[2*i +1]->key > h->array[2*i+2]->key){
            return 2*i+2;
        }
        else return 2*i+1;
    }
}

int find_maxfiglio(_heap* h, int i){
    if(h->used <= 2*i +2){
        return 2*i +1;
    }
    else{
        if(h->array[2*i +1]->key > h->array[2*i+2]->key){
            return 2*i+1;
        }
        else return 2*i+2;
    }
}

void ordina_heap_downheap(_heap* h, _heap_entry* e){
    int i = e->position;
    if(h->is_min_heap == 1){ // è un min heap
        int minfiglio= find_minfiglio(h, e->position);
        while((i< h->used) &&( e->key > h->array[minfiglio]->key)){
                _heap_entry* temp = e;
                h->array[i] = h->array[minfiglio];
                h->array[minfiglio] = temp;
                h->array[i]->position = minfiglio;
                h->array[minfiglio]->position =i;
                e = h->array[minfiglio];
                heap_print(h);
                if(minfiglio*2 +1 >= h->used)return;
                i = minfiglio;
                minfiglio = find_minfiglio(h,i);
            }
    }
    else{ //è un max heap
        int maxfiglio= find_maxfiglio(h, e->position);
        while((i< h->used) &&( e->key < h->array[maxfiglio]->key)){
                _heap_entry* temp = e;
                h->array[i] = h->array[maxfiglio];
                h->array[maxfiglio] = temp;
                h->array[i]->position = maxfiglio;
                h->array[maxfiglio]->position =i;
                e = h->array[maxfiglio];
                if(maxfiglio*2 + 1 >= h->used) return; //è una foglia
                i = maxfiglio;
                maxfiglio = find_maxfiglio(h,i);
            }
    }
}

void heap_delete(heap * hh) {
    _heap* h = (_heap*) hh;
    int i;
    for(i=0; i < h->size;i ++){
        free(h->array[i]);
    }
    free(h->array);
    free(h);
	return;
}

heap * array2heap(int * array, int size, HEAP_TYPE is_min_heap) {
    _heap* h= heap_new(is_min_heap, size);
    int i;
    for(i =0; i < size; i++){
        _heap_entry* nodo = malloc(sizeof(_heap_entry));
        h->array[i] = nodo;
        nodo->key = array[i];
        nodo->position = i;
        h->used++;
    }
    int padre = (h->used -2)/2;
    printf("%d\n", find_maxfiglio(h, padre));
    printf("padre %d\n",padre);
    while(padre >=0){
            ordina_heap_downheap(h, h->array[padre]);
            padre--;
    }
	return (heap*) h;
}

void heap_print(heap * hh) {
    _heap* h = (_heap*) hh;
    int i;
    for(i=0; i < h->used; i++){
        printf("%d ", h->array[i]->key);
    }
    printf("\n");
	return;
}


void heap_sort(int * array, int size) {

	_heap * h = array2heap(array, size, 0);
	heap_print(h);
	int i;
	for(i = size - 1; i > 0; i--) {

		 _heap_entry* tmp = h->array[0];
        h->array[0] = h->array[i];
        h->array[i] = tmp;
        h->array[0]->position = 0;
        h->array[i]->position = i;
        array[i] = h->array[i]->key;
		h->used -= 1;
        heap_print(h);
        if(h->used == 1) break;
		ordina_heap_downheap(h, h->array[0]);
        heap_print(h);
	}
    heap_print(h);
	array[0] = h->array[0]->key;

	h->used = size;
	heap_delete(h);
}

void heap_update_key(heap * hh, heap_entry * ee, int key) {
    _heap* h = (_heap*) hh;
    _heap_entry* e = (_heap_entry*) ee;
    int oldkey = e->key;
    e->key = key;
    heap_print(h);
    int i;
    for(i=0; i< h->used;i++){
        printf( "posizione %d ", h->array[i]->position);
    }
    printf("\n");
    printf("posizione %d, vecchia chiave %d\n", e->position, oldkey);
    if(h->is_min_heap == 1){
        if(e->position == 1) ordina_heap_downheap(h, e);
/*        else if( (e->position)*2 +1 >= h->used) ordina_heap_upheap(h,e);
        else{
            ordina_heap_downheap(h,e);
            ordina_heap_upheap(h,e);
        }*/
    }
	return;
}

