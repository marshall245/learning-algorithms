#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "test_utils.h"
#include "sorts.h"
#include "heaps.h"

void test_sort(void (*foo)(long *, long long)) {
	// declare test vars
	int truth = 1;
	long long len = 10, k;
	long arr[10] = {6, 11, 0, 3, 42, 6, 5, 7, 1, 2};
	long sorted[10] = {0, 1, 2, 3, 5, 6, 6, 7, 11, 42};

	// show, sort, then show again
	show_array(arr, len, 3, 3);
	foo(arr, len);
	show_array(arr, len, 3, 3);


	for (k=0; k < len; k++) {
		truth *= (arr[k] == sorted[k]);
	}

	if (truth) {
		puts("sorted");
	} else {
		puts("unsorted");
	}
}

clock_t gettime() {
	time_t current_time;

	/* Obtain current time. */
	return 1000000 * clock() / CLOCKS_PER_SEC;
}

void show_time(double diffed_time) {
	printf("The algorthm ran in %.29f seconds\n", diffed_time);
}

void test_time(void (*foo)(long *, long long), long * arr, long long len) {
    // boorowed heavily from https://en.wikipedia.org/wiki/C_date_and_time_functions
    int i;
    clock_t start;
    double diff;

    start = gettime();
    foo(arr, len);
    diff = ((double) (gettime() - start)) / 1000000;
    show_time(diff);
}

void timed_sort(long long arrlen, void (*foo)(long *, long long)) {

	long long i;

	long * testarr = (long *) malloc(sizeof(long) * arrlen);
	for (i=0; i < arrlen; i++) {
		testarr[i] = (long) rand();
	}

	test_time(foo, testarr, arrlen);

	free(testarr);
}

int main() {
	long long bubble_len, insert_len, merge_len, merge_w_ins_len, i;
	
	srand(time(NULL));

	test_sort(bubble_sort);

	test_sort(insertion_sort);

	test_sort(merge_sort);

	test_sort(merge_w_instn_sort);

	test_sort(heap_sort);

	test_sort(quicksort);

	timed_sort(100000, bubble_sort); // bubble_sort, 100,000

	timed_sort(100000, insertion_sort); // insertion_sort, 100,000

    timed_sort(100000, merge_sort); // merge_sort 100,000

	timed_sort(100000, merge_w_instn_sort); // merge_w_instn_sort 100,000

	timed_sort(100000, heap_sort); // heap_sort 100,000

	timed_sort(100000, quicksort); // quicksort 100,000

	// trace out the merge_sort growth
	printf("%s\n", "trace out the growth pattern for merge_sort");

	long long n, bound;
	bound = 100000000;  // 100,000,000
	for(n=100; n <= bound; n *= 10) {
		printf("For n = %lld\n", n);
		timed_sort(n, merge_sort);
	}

	// trace out the heap_sort growth
	printf("%s\n", "trace out the growth pattern for heap_sort");

	long long n2, bound2;
	bound2 = 100000000;  // 100,000,000
	for(n2=100; n2 <= bound2; n2 *= 10) {
		printf("For n = %lld\n", n2);
		timed_sort(n2, heap_sort);
	}

	// trace out the heap_sort growth
	printf("%s\n", "trace out the growth pattern for quicksort");

	long long n3, bound3;
	bound3 = 100000000;  // 100,000,000
	for(n3=100; n3 <= bound3; n3 *= 10) {
		printf("For n = %lld\n", n3);
		timed_sort(n3, quicksort);
	}

	return 0;
}
