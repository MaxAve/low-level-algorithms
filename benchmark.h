/*
 * Note:
 * benchmark.h is used for testing and benchmarking algorithms.
 * This file contains functions such as checking execution time, checking if a 
 * buffer is properly sorted, etc.
 */

#include <stdbool.h>
#include <time.h>

// Returns true if the given array is sorted, otherwise false
bool is_sorted(int* buf, int len, bool ascending) {
	for(int i = 0; i < len - 1; i++) {
		if(ascending) {
			if(buf[i] > buf[i + 1]) {
				return false;
			}
		} else {
			if(buf[i] < buf[i + 1]) {
				return false;
			}
		}
	}
	return true;
}

// Returns execution time [s] of a sorting algorithm
double get_exec_time_sort(void (*sort)(int*, int), int* buf, int len) {
	clock_t start = clock();
	sort(buf, len);
	clock_t end = clock();
	return (double)(end - start) / CLOCKS_PER_SEC;
}
