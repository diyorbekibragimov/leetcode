#include <stdlib.h>
#include <stdio.h>

void merge(int* A, int lo, int mid, int hi) {
    int i = lo;
    int j = mid;
    int* B = calloc(hi - lo, sizeof(int));
    int k = 0;
    
    while (i < mid && j < hi) {
        if (A[i] >= A[j]) {
            B[k] = A[i];
            i++;
        } else {
            // A[i] < A[j]
            B[k] = A[j];
            j++;
        }
        k++;
    }

    while (i < mid) {
        B[k] = A[i];
        k++;
        i++;
    }

    while (j < hi) {
        B[k] = A[j];
        k++;
        j++;
    }

    for(k = 0; k < hi - lo; k++) {
        A[lo+k] = B[k];
    }
}

void sort(int* A, int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    sort(A, lo, mid);
    sort(A, mid, hi);
    merge(A, lo, mid, hi);
}

long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
    sort(happiness, 0, happinessSize);
    long long sum = 0;
    int deduct = 0;
    for (int i = 0; i < k; i++) {
        int x = happiness[i] - deduct;
        deduct += 1;
        if (x < 0) break;
        sum += x;
    }
    return sum;
}