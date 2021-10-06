#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#include "_heap.h"

heap * heap_new(HEAP_TYPE is_min_heap, int capacity) {

	_heap * h = malloc(sizeof(_heap));
	h->size = capacity;
	h->used = 0;
	h->array = malloc(sizeof(_heap_entry *) * h->size);
	h->is_min_heap = is_min_heap;

	return h;
}

HEAP_TYPE heap_type(heap * hh) {
	_heap * h = hh;
	return h->is_min_heap;
}

int heap_peek(heap * hh) {
	_heap * h = hh;
	return h->array[0]->key;
}

static void heap_grow(_heap * h) {
	h->array = realloc(h->array, sizeof(_heap_entry *) * h->size * 2);
	h->size = h->size * 2;
}

static int get_parent_index(int i) {
	return (i - 1) / 2;
}

static int is_root_index(int i) {
	return i == 0 ? 1 : 0;
} 

static int get_left_index(_heap * h, int i) {
	return 2 * i + 1;
}
	
static int get_right_index(_heap * h, int i) {
	return get_left_index(h, i) + 1;
}

static int is_leaf(_heap * h, int i) {
	return get_left_index(h, i) >= h->used;
}

static int compare(_heap * h, int i, int j) {

	if (h->is_min_heap == MIN_HEAP)
		return h->array[i]->key < h->array[j]->key;
	else
		return h->array[i]->key > h->array[j]->key;
}

static void exchange(_heap * h, int i, int j) {

	//printf("Swap element index %d (%d) with index %d (%d)\n", i, h->array[i]->key, j, h->array[j]->key);

	_heap_entry * temp = h->array[i];
	h->array[i] = h->array[j];
	h->array[j] = temp;

	h->array[i]->position = i;
	h->array[j]->position = j;
}

heap_entry * heap_add(heap * hh, int key) {
	
	_heap * h = hh;

	if(h->used >= h->size)
		heap_grow(h);

	_heap_entry * e = malloc(sizeof(_heap_entry));
	e->key = key;
	e->position = h->used;
	h->array[h->used] = e;
	
	int i = h->used;
	int j = get_parent_index(i);
	while(!is_root_index(i) && compare(h, i, j)) {
		exchange(h, i, j);
		i = j;
		j = get_parent_index(i);
	}

	h->used += 1;
	return e;
}

int get_key_entry(heap_entry * ee) {
	_heap_entry * e = ee;
	return e->key;
}

int heap_size(heap * hh) {
	_heap * h = hh;
	return h->used;
}

static int get_max_child_index(_heap * h, int k) {
	
	if(is_leaf(h, k))
		return -1;

	else {

		int l = get_left_index(h, k);
		int r = get_right_index(h, k);
		int max = l;
		if(r < h->used && compare(h, r, l))
			max = r;

		return max;
	}
}

static void heapify(_heap * h, int i) {

	//printf("Heapify on %d\n", i);

	if(is_leaf(h, i))
		return;

	else {

		int j = get_max_child_index(h, i);
		//printf("max child is %d (%d)\n", j, h->array[j]->key);
		if (j < 0)
			return;

		if(!compare(h, i, j)) {
			exchange(h, i, j);
			heapify(h, j);
		}
	}
}

int heap_poll(heap * hh) {
	
	_heap * h = hh;

	int key = -1;
	if(h->used > 0) {
		_heap_entry * e = h->array[0];
		h->array[0] = h->array[h->used - 1];
		h->used -= 1;
		heapify(h, 0);
		key = e->key;
		free(e);
	}
		
	return key;
}

void heap_delete(heap * hh) {

	_heap * h = hh;

	int i;
	for (i = 0; i < h->used; i++)
		free(h->array[i]);

	free(h->array);
	free(h);

	return;
}

heap * array2heap(int * array, int size, HEAP_TYPE is_min_heap) {

	_heap * h = heap_new(is_min_heap, size);

	//printf("Is Min Heap? %d\n", heap_is_min(h));

	int k;
	for (k = 0; k < size; k++) {

		_heap_entry * e = malloc(sizeof(_heap_entry));
		e->key = array[k];
		e->position = k;
		h->array[k] = e;

	}

	h->used = size;

	for(k = get_parent_index(size - 1); k >= 0; k--) {
		printf("iteration: %d\n", k);
		heapify(h, k);
	}

	return h;
}

void heap_print(heap * hh) {

	_heap * h = hh;
	int k;
	for (k = 0; k < h->used; k++)
		printf(" %d", h->array[k]->key);
	printf("\n\n");
}

void heap_sort(int * array, int size) {

	_heap * h = array2heap(array, size, 0);
	heap_print(h);
	int i;
	for(i = size - 1; i > 0; i--) {

		exchange(h, 0, i);
		array[i] = h->array[i]->key;
		h->used -= 1;
		heapify(h, 0);

	}

	array[0] = h->array[0]->key;

	h->used = size;
	heap_delete(h);
}

static void sift_up(_heap * h, int i){

	while (i > 0) {

		int p = get_parent_index(i);
		if (compare(h, i, p)) {
		
			exchange(h, i, p);
			i = p;

		} else 
			return;
	}
}

void heap_update_key(heap * hh, heap_entry * ee, int key) {

	_heap * h = hh;
	_heap_entry * e = ee;

	int oldKey = e->key;
	e->key = key;

	//printf("position: %d - oldKey: %d\n", e->position, oldKey);

	int keyDecrease = key < oldKey;

	if (heap_type(h) == MIN_HEAP) {

		if (keyDecrease)
			sift_up(h, e->position);
		else
			heapify(h, e->position);		
	
	} else {

		if (!keyDecrease)
			sift_up(h, e->position);
		else
			heapify(h, e->position);

	}
        
}

