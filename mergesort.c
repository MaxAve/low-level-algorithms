#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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
    int left[ll];
    int right[lr];
    for(int i = 0; i < ll; i++)
        left[i] = buf[i];
    for(int i = 0; i < lr; i++)
        right[i] = buf[i + ll];
    sort(left, ll);
    sort(right, lr);
    merge(left, ll, right, lr, buf);
}

int main() {
    srand(time(NULL));
    const int length = 20;
    int buf[length];
    for(int i = 0; i < length; i++) {
        buf[i] = rand() % 100;
    }
    printf("Before: ");
    for(int i = 0; i < length; i++) {
        printf("%i ", buf[i]);
    }
    sort(buf, length);
    printf("\nAfter:  ");
    for(int i = 0; i < length; i++) {
        printf("%i ", buf[i]);
    }
    printf("\n");
    return 0;
}
