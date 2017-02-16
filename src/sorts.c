/*
*  A set of sorting algorithms as described in Introduction to Algorithms 3rd Ed.
*/
#include <stdlib.h>
#include <stdio.h>
#include "heaps.h"


long long INSERTION_BOUNDARY = 100;


void bubble_sort(long * arr, long long len) {
	// conducts inplace bubble sort
	long tmp;
	long long i, j;

	for (i=0; i < len; i++) {
		for (j=len - 1; j > i + 1; j--) {
			if (arr[j - 1] > arr[j]) {
				tmp = arr[j - 1];
				arr[j - 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void insertion_sort(long * arr, long long len) {
	// conducts inplace insertion sort
	int key;
	int i, j;
	for (i=1; i < len; i++) {
		key = arr[i];

		j = i - 1;
		while ((j > 0) && (arr[j] > key)) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void _merge(long * arr, long long p, long long q, long long r) {
	// the function for the merge step in merge_sort(...)
	
	// the count of items in each sub array
	long long i, j, k;
	long long n1 = q - p + 1, n2 = r - q;

	// use as duplicate sub arrays
	long * L, * R;
	L = (long *)malloc(n1 * sizeof(long));
	R = (long *)malloc(n2 * sizeof(long));
	// long L[n1];
	// long R[n2];

	// duplicate the subarrays
	for(i=0; i < n1; i++) {
		L[i] = arr[p + i];
	}
	for(i=0; i < n2; i++) {
		R[i] = arr[q + 1 + i]; 
	}

	// merge
	i = 0;
	j = 0;
	for (k=0; k < r - p + 1; k++) {
		if (L[i] < R[j]) {
			arr[p + k] = L[i];
			i++;
		} else {
			arr[p + k] = R[j];
			j++;
		}

		// short circuit when one sub array runs out of values
		if ((i >= n1) && (j < n2)){
			for (; j < n2; j++) {
				k++;
				arr[p + k] = R[j];
			}
			break;
		} else if ((j >= n2) && (i < n1)) {
			for (; i < n1; i++) {
				k++;
				arr[p + k] = L[i];
			}
			break;
		}
	}

	free(L);
	free(R);
}

void _go_mgsort(long * arr, long long p, long long r) {
	// the recursing function for merge_sort(...)
	if ((r - p) > 0) {
		int q;
		q = (p + r) / 2;  // floor division

		// recurse and merge the result
		_go_mgsort(arr, p, q);
		_go_mgsort(arr, q + 1, r);
		_merge(arr, p, q, r);
	}
}

void _go_ms_with_ins(long * arr, long long p, long long r) {
	// the recursing function for merge_sort(...) when insertion=1
	if ((r - p) > INSERTION_BOUNDARY) {
		int q;
		q = (p + r) / 2;  // floor division

		// recurse and merge the result
		_go_mgsort(arr, p, q);
		_go_mgsort(arr, q + 1, r);
		_merge(arr, p, q, r);
	} else {
		insertion_sort(arr, r - p + 1);
	}
}

void merge_sort(long * arr, long long len) {
	// conducts inplace merge sort
	_go_mgsort(arr, 0, len - 1);
}

void merge_w_instn_sort(long * arr, long long len) {
	// conducts inplace merge sort
	_go_ms_with_ins(arr, 0, len - 1);	
}

void heap_sort(long * arr, long long len) {
	long long i;
	long tmp;

	build_max_heap(arr, len);
	for (i = len - 1; i > 0; i--) {
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		max_heapify(arr, 0, i);
	}
}

long long _partition_quicksort(long * arr, long long p, long long r) {
	long tmp, x;
	long long i, j;

	x = arr[r];
	i = p - 1;

	for (j = p; j < r; j++) {
		if (arr[j] <= x) {
			i++;
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}

	tmp = arr[i + 1];
	arr[i + 1] = arr[r];
	arr[r] = tmp;
	return i + 1;
}

void _go_quicksort(long * arr, long long p, long long r) {
	if (p < r) {
		long long q;
		q = _partition_quicksort(arr, p, r);
		_go_quicksort(arr, p, q - 1);
		_go_quicksort(arr, q + 1, r);
	}
}

void quicksort(long * arr, long long len) {
	_go_quicksort(arr, 0, len - 1);
}
