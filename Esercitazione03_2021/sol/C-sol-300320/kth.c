#include <stdlib.h>

#include "heap.h"
#include "kth.h"
#include "_heap.h"

typedef struct _kth {
	_heap * min_heap;
	_heap * max_heap;
	int k;
} _kth;

kth * kth_new(int k) {

	_kth * d = malloc(sizeof(_kth));
	d->min_heap = heap_new(MIN_HEAP, k);
	d->max_heap = heap_new(MAX_HEAP, k);
	d->k = k;

	return d;
}

void kth_print(kth * dd) {

	_kth * d = dd;
	heap_print(d->max_heap);
	heap_print(d->min_heap);

}


void kth_insert(kth * dd, int key) {

	_kth * d = dd;
	//printf("inserting %d...\n", key);
	
	if (heap_size(d->max_heap) < d->k) {
		
		heap_add(d->max_heap, key);
		
	} else if (key >= heap_peek(d->max_heap)) {

		heap_add(d->min_heap, key);

	} else {

		int old = heap_poll(d->max_heap);
		heap_add(d->max_heap, key);
		heap_add(d->min_heap, old);

	}

	//kth_print(dd);
}

int kth_get(kth * dd) {
	_kth * d = dd;
	return heap_peek(d->max_heap);
}

void kth_remove(kth * dd) {

	//printf("deleting %d...\n", kth_get(dd));

	_kth * d = dd;
	if (heap_size(d->min_heap) == 0) {
		
		heap_poll(d->max_heap);
		
	} else {

		int key = heap_poll(d->min_heap);
		heap_poll(d->max_heap);
		heap_add(d->max_heap, key);

	}

	//kth_print(dd);
}

void kth_delete(kth * dd) {

	_kth * d = dd;
	heap_delete(d->max_heap);
	heap_delete(d->min_heap);
	free(d);

}