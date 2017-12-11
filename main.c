#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
#include <string.h>

#define REPEAT_BENCHMARK 3

int* generate_random_array(int n);
int* duplicate_array(int const * src, size_t len);
double get_benchmark(int *a, int n, int thread_count);
double** get_benchmarks(int *ns, int ns_size, int *thread_counts, int tc_size);

void quicksort(int*, int, int);
int partition(int*, int, int);

int main(int argc, char* argv[]) {

    int sizes_to_try[] = {10, 100, 1000, 10000};
    int sizes_n = sizeof(sizes_to_try) / sizeof(sizes_to_try[0]);
    int threads_to_try[] = {1, 2, 4, 8};
    int threads_n = sizeof(threads_to_try) / sizeof(threads_to_try[0]);

    double **time = get_benchmarks(sizes_to_try, sizes_n, threads_to_try, threads_n);
    deallocate_mem(time, sizes_n);

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

double** allocate_mem(int n, int m) {
    double **array = malloc(n * sizeof(double *));
    for(int i = 0; i < n; i++)
        array[i] = malloc(m * sizeof(double));
    return array;
}

void deallocate_mem(double** arr, int n){
    for (int i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
}

double** get_benchmarks(int *ns, int ns_size, int *thread_counts, int tc_size) {

    double **time = allocate_mem(ns_size, tc_size);

    for (int i = 0; i < ns_size; i++) {
        int n = ns[i];
        int *a = generate_random_array(n);
        for (int j = 0; j < tc_size; j++) {
            int tc = thread_counts[j];
            for (int k = 0; k < REPEAT_BENCHMARK; k++) {
                int *b = duplicate_array(a, n);
                if (k == 0)
                    time[i][j] = get_benchmark(b, n, tc);
                else {
                    double new_time = get_benchmark(b, n, tc);
                    if (new_time < time[i][j])
                        time[i][j] = new_time;
                }
                printf("Thread count: %d   # elements: %d   Result: %f\n", tc, n, time[i][j]);
                free(b);
            }
        }
    }
    return time;
}

double get_benchmark(int *a, int n, int thread_count) {
    omp_set_num_threads(thread_count);
    double start_time = omp_get_wtime();
    quicksort(a, n, n);
    double end_time = omp_get_wtime();

    for (int i = 1; i < n; i++)
        if (a[i] < a[i-1])
            printf("\nNot in order!");

    return end_time - start_time;
}

//Algorithm copied with minor changes from https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
void quicksort(int *a, int n, int max_n) {

    if (n < 2) return;

    int pivot = a[n / 2];

    int new_pivot = partition(a, pivot, n);

    if (n < max_n / omp_get_num_threads()) {
        quicksort(a, new_pivot, max_n);
        quicksort(a + new_pivot, n - new_pivot, max_n);
    } else {
#pragma omp parallel sections
        {
#pragma omp section
            quicksort(a, new_pivot, max_n);
#pragma omp section
            quicksort(a + new_pivot, n - new_pivot, max_n);
        };
    }
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