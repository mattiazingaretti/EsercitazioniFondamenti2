#include <assert.h>
#include <stdio.h>

#include "max_gap.h"

int maxGap(int * array, int start, int end) {
	// TODO: Da completare
	if(end-start == 2){
		return array[start+1] - array[start];
	}
	int n = (end-start)/2;
	int l= maxGap(array, start, n+start+1);
	int r=maxGap(array,n+start,end);
	if(l>r) return l;
	else return r;
}
