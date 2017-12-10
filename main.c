#include <stdio.h>
#include "omp.h"
#include <stdlib.h>

#define NUM_ELEMENTS 10


void quicksort(int*, int);
int partition(int*, int, int);

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

//Algorithm copied with minor changes from https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quicksort(int *a, int n) {

    if (n < 2) return;

    int pivot = a[n / 2];

    int new_pivot = partition(a, pivot, n);

    quicksort(a, new_pivot);
    quicksort(a + new_pivot, n - new_pivot);
}

void swap(int *a, int i, int j) {
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(int *a, int pivot, int n) {
    int i, j;
    for (i = 0, j = n - 1; ; i++, j--) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i >= j) break;

        swap(a, i, j);

    }
    return i;
}
