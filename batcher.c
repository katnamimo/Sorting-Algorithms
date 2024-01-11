#include "batcher.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void comparator(Stats *stats, uint32_t *A, int x, int y) {
    stats->compares++;
    // Keep track of the number of comparisons made
    if (A[x] > A[y]) {
        // Check if the number at the first index is larger than the number at the second index
        int temp = A[x];
        A[x] = A[y];
        A[y] = temp;
        stats->moves += 3;
    }
}
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0)
        return;

    int t = log2(n);
    // Start sorting with the largest possible gap, p, and reduce it by half each time
    for (int p = 1 << (t - 1); p > 0; p >>= 1) {
        // Start sorting with the largest gap and reduce it by d each time
        for (int d = p; d > 0; d = (d == p) ? 0 : p - d) {
            for (uint32_t i = d; i < n - d; i++) {
                if ((i & p) == 0)
                    // Compare the current number with the number d positions ahead of it
                    comparator(stats, A, i, i + d);
            }
        }
    }
}
