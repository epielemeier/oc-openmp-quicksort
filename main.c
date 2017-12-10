#include <stdio.h>
#include "omp.h"
#include <stdlib.h>

#define NUM_ELEMENTS 10


void quicksort(int*, int);

int main(int argc, char* argv[]) {

    int a[NUM_ELEMENTS];
    int n = sizeof a / sizeof a[0];
    for (int i = 0; i < n; i++)
        a[i] = rand();

    quicksort(a, n);

    for (int i = 0; i < n; i++)
        printf("%d\n", a[i]);
    return 0;
}

void quicksort(int *a, int n) {
}

