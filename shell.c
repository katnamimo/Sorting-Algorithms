#include "shell.h"

#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    // Calculate the gap sequence for the shell sort
    uint32_t gap_sequence = log(3 + 2 * n) / log(3);

    // Iterate over each gap in the gap sequence
    for (uint32_t gap = gap_sequence; gap > 0; gap /= 3) {
        // Sort the array using the current gap
        for (uint32_t i = gap; i < n; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, A[i]);
            while (j >= gap && cmp(stats, temp, A[j - gap]) == -1) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = move(stats, temp);
        }
    }
    return;
}
