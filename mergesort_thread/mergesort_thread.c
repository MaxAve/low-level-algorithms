#include "mergesort_thread.h"

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

void sort(int* buf, int len, int max_thread_depth) {
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
	
	if(max_thread_depth > 0) {
		pthread_t t1;
		pthread_t t2;

		SortArgs args1;
		SortArgs args2;

		args1.buf = left;
		args2.buf = right;
		args1.len = ll;
		args2.len = lr;
		args1.depth = max_thread_depth - 1;
		args2.depth = max_thread_depth - 1;

		if(pthread_create(&t1, NULL, psort, &args1) != 0) {
        	printf("[ERROR] mergesort_thread: Failed to create thread (left)");
        	return;
    	}
		
		if(pthread_create(&t2, NULL, psort, &args2) != 0) {
        	printf("[ERROR] mergesort_thread: Failed to create thread (right)");
        	return;
    	}

		if(pthread_join(t1, NULL) != 0) {
        	printf("[ERROR] mergesort_thread: Failed to join thread (left)");
        	return;
    	}
		
		if(pthread_join(t2, NULL) != 0) {
        	printf("[ERROR] mergesort_thread: Failed to join thread (right)");
        	return;
    	}
	} else {
    	sort(left, ll, max_thread_depth - 1);
    	sort(right, lr, max_thread_depth - 1);
	}
    
	merge(left, ll, right, lr, buf);
	
	// free mah boys they did nothin' wrong!
	free(left);
	free(right);
}

void* psort(void* args) {
	int* buf = (*((SortArgs*)args)).buf;
	int len = (*((SortArgs*)args)).len;
	int depth = (*((SortArgs*)args)).depth;
	sort(buf, len, depth);
	return NULL;
}

int main() {
    srand(time(NULL));
   
	double times[12];

	const int length = 100000000;
	int* buf = (int*)malloc(sizeof(int) * length);
   
	for(int i = 0; i < 12; i++) {
		printf("Populating array...\n");

		for(int i = 0; i < length; i++) {
			buf[i] = length - i;
		}
			
		printf("Sorting...\n");
		   
		struct timespec start, end;
			
		clock_gettime(CLOCK_MONOTONIC, &start);	
			
		sort(buf, length, i);
			
		clock_gettime(CLOCK_MONOTONIC, &end);
			
		double t = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

		times[i] = t;

		printf("Sort %i items: %fs\n", length, t);
		printf("Checking...\n");

		bool sorted = is_sorted(buf, length, true);
			
		printf("Sorted: %i\n", sorted);
	}

	free(buf);
	buf = NULL;
	
	printf("\nTimes:\n");
	for(int i = 0; i < 10; i++) {
		printf("%f ", times[i]);
	}
	printf("\n");
	   
	return 0;
}
