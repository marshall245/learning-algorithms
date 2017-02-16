/*
*  A set of heap algorithms as described in Introduction to Algorithms 3rd Ed.
*/

#include <stdlib.h>

long long parent(long long ix) {
	return ix / 2; // floor division
}

long long left_ix(long long ix) {
	return 2 * ix;
}

long long right_ix(long long ix) {
	return 2 * ix + 1;
}

void max_heapify(long * arr, long long ix, long long arrlen) {
	long long l, r, largest;
	l = left_ix(ix);
	r = right_ix(ix);
	if ((l < arrlen) && (arr[l] > arr[ix])) {
		largest = l;
	} else {
		largest = ix;
	}

	if ((r < arrlen) && (arr[r] > arr[largest])) {
		largest = r;
	}

	if (largest != ix) {
		long tmp = arr[ix];
		arr[ix] = arr[largest];
		arr[largest] = tmp;

		max_heapify(arr, largest, arrlen);
	}
}

void build_max_heap(long *arr, long long arrlen) {
	long long i;
	for (i = arrlen / 2; i >= 0; i--) {
		max_heapify(arr, i, arrlen);
	}
}

// additional heap algorithms, beyond sorting
long heapmax(long * arr) {
	return arr[0];
}

long heap_extract_max(long * arr, long long len) {
	long maxval;

	if (len < 1) {
		puts("!!!! heap underflow !!!!");
	}

	maxval = arr[0];
	arr[0] = arr[len - 1];
	max_heapify(arr, 0, len - 1);
	return maxval;
}

void heap_increase_key(long * arr, long long ix, long key) {
	if (key < arr[ix]) {
		puts("!!!! key is smaller than current value !!!!");
		exit(1);
	}
	long tmp;

	arr[ix] = key;
	while ((ix > 1) && (arr[parent(ix)] < arr[ix])) {
		tmp = arr[ix];
		arr[ix] = arr[parent(ix)];
		arr[parent(ix)] = tmp;
		ix = parent(ix);
	}
}
