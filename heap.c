#include "heap.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Finds the index of the maximum child of a node in the heap
static uint32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    // Returns the index of the greater child
    if ((right <= last) && (cmp(stats, A[right - 1], A[left - 1]) > 0)) {
        return right;
    }
    return left;
}

// Fixes a heap rooted at node "first"
static void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    int found = 0;
    uint32_t mother = first, great = max_child(stats, A, mother, last);
    while ((mother <= floor(last / 2)) && !found) {
        // If the current node is smaller than its maximum child, swap them
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = 1;
        }
    }
    return;
}

// Builds a heap from an array
static void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    // Starts from the last non-leaf node and fixes the heap
    for (uint32_t father = floor(last / 2); father > (first - 1); --father) {
        fix_heap(stats, A, father, last);
    }
    return;
}

// Sorts an array using the Heap Sort algorithm
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1, last = n;
    // Builds the heap from the array
    build_heap(stats, A, first, last);

    // Repeatedly swaps the largest element with the last element of the heap and fixes the heap
    for (uint32_t leaf = last; leaf >
