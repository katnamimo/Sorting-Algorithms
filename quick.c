#include "quick.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Divide the list into two parts: the smaller values on the left and the larger values on the right.
uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    // i is the index of the last number in the left partition
    uint32_t i = lo - 1;

    // Loop through the list and compare each number with the pivot.
    for (uint32_t j = lo; j < hi; j++) {
        // If the current number is smaller than the pivot, add it to the left partition.
        if (cmp(stats, A[j - 1], A[hi - 1]) < 0) {
            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }

    // Swap the pivot with the first number in the right partition.
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

// Recursively sort the partitions until the list is sorted.
void quick_sorter(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {
    // If there is more than one element in the partition, continue sorting.
    if (lo < hi) {
        // Get the pivot index.
        uint8_t p = partition(stats, A, lo, hi);
        // Sort the left partition.
        quick_sorter(stats, A, lo, p - 1);
        // Sort the right partition.
        quick_sorter(stats, A, p + 1, hi);
    }
    return;
}

// Start the sorting process by calling quick_sorter on the entire list.
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
    return;
}
