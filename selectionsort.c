#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int *buf, int len) {
    int head = 0;
    while(head < len) {
        // find min value
        int min = __INT_MAX__;
        int swap_index = head;
        for(int j = head; j < len; j++) {
            if(buf[j] < min) {
                min = buf[j];
                swap_index = j;
            }
        }
        // swap values
        int tmp = buf[swap_index];
        buf[swap_index] = buf[head];
        buf[head] = tmp;
        head++;
    }
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