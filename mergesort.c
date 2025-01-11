#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "benchmark.h"

void merge(const int *a, int len_a, const int *b, int len_b, int *c) {
    int i=0,j=0;
    while(i < len_a || j < len_b) {
        if(i == len_a) {
            c[i + j] = b[j];
            j++;
        } else if(j == len_b) {
            c[i + j] = a[i];
            i++;
        } else if(a[i] <= b[j]) {
            c[i + j] = a[i];
            i++;
        } else {
            c[i + j] = b[j];
            j++;
        }
    }
}

void sort(int *buf, int len) {
    if(len <= 1)
        return;
    int ll = len / 2; // length left
    int lr = len - ll; // length right
    int* left = (int*)malloc(sizeof(int) * ll);
    int* right = (int*)malloc(sizeof(int) * lr);
	for(int i = 0; i < ll; i++)
        left[i] = buf[i];
    for(int i = 0; i < lr; i++)
        right[i] = buf[i + ll];
    sort(left, ll);
    sort(right, lr);
    merge(left, ll, right, lr, buf);
	// free mah boys they did nothin' wrong!
	free(left);
	free(right);
}

int main() {
    srand(time(NULL));
    
	const int length = 50000000;
   
	printf("Creating array...\n");

	int* buf = (int*)malloc(sizeof(int) * length);

	for(int i = 0; i < length; i++) {
        buf[i] = rand() % length;
    }
	
	printf("Sorting...\n");
   
	double t = get_exec_time_sort(sort, buf, length);
	
	printf("Sort %i items: %fs\n", length, t);

	printf("Checking...\n");

	bool sorted = is_sorted(buf, length, true);
	
	free(buf);
	buf = NULL;
	
	printf("Sorted: %i\n", sorted);
	   
	return 0;
}

