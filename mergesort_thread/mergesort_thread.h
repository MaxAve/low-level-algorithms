#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>
#include "../benchmark.h"

typedef struct {
	int* buf;
	int len;
	int depth;
} SortArgs;

/* Merge two sorted arrays */
void merge(const int *a, int len_a, const int *b, int len_b, int *c); 

/* Mergesort implementation */
void sort(int* buf, int len, int max_thread_depth);

/* Same as sort but suited for running as a thread */
void* psort(void* args);
