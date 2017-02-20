#include <stdio.h>

int min(int a, int b) {
	// find minimum between to ints
	if (a < b) {
		return a;
	}
	return b;	
}

int show_array(long * arr, long long len, int from_begin, int from_end) {
	// prints an array such as "1 2 3 ... 9 10 11"
	
	int ellipsebound, i;
	
	ellipsebound = min(3, (int) (len - (from_end + from_begin)));

	// check boundary conditions
	if (len < from_begin + from_end) {
		return -1;
	}

	// print intitial items
	for (i=0; i < from_begin; i++) {
		printf("\t%ld", arr[i]);
	}

	// print ellipses
	printf("%s", "\t");
	for (i=0; i < ellipsebound; i++) {
		printf("%s", " .");
	}
	printf("%s", " ");

	// print final characters
	for (i=from_end; i > 0; i--) {
		printf("\t%ld", arr[len - i]);
	}

	// newline
	puts("");

	return 0;
}