#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <string.h>

#define NUM_ELEMENTS 10000

int* generate_random_array(int n);
int* duplicate_array(int const * src, size_t len);
void benchmark(int *a, int n, int thread_count);

void quicksort(int*, int);
int partition(int*, int, int);

int main(int argc, char* argv[]) {

    int *a = generate_random_array(NUM_ELEMENTS);
    int n = NUM_ELEMENTS;

    int threads_to_test = 6;
    for (int i = 1; i <= threads_to_test; i++) {
        int *b = duplicate_array(a, n);
        benchmark(b, n, i);
        free(b);
    }
    free(a);
    return 0;
}

int* generate_random_array(int n) {
    int *a = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        a[i] = rand();
    return a;
}

int* duplicate_array(int const * src, size_t len) {
    int * p = malloc(len * sizeof(int));
    memcpy(p, src, len * sizeof(int));
    return p;
}

void benchmark(int *a, int n, int thread_count) {
    omp_set_num_threads(thread_count);
    double start_time = omp_get_wtime();
    quicksort(a, n);
    double end_time = omp_get_wtime();

    for (int i = 1; i < n; i++)
        if (a[i] < a[i-1])
            printf("\nNot in order!");
    printf("\nNum threads: %d\tPerformance: %f", thread_count, end_time - start_time);

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