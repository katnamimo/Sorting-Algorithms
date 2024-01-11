#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS   "abshqn:p:r:H"
#define SEED      13371453
#define ARRAYSIZE 100
#define ELEMENTS  100
#define ARRAY     100

void random_array(uint32_t *A, uint32_t n);
void display_array(uint32_t *A, int size, int array);
void display_stats(Stats *s, uint32_t size, const char algorithm[]);
void help(void);

typedef enum { BATCHER, HEAP, SHELL, QUICK } sorts;
const char *names[] = { "Batcher Sort", "Heap Sort", "Shell Sort", "Quick Sort" };

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t size = ARRAYSIZE;
    uint32_t seed = SEED;
    uint32_t array = ARRAY;
    Set s = set_empty();
    Stats stats;
    stats.moves = 0;
    stats.compares = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            s = set_insert(s, BATCHER);
            s = set_insert(s, SHELL);
            s = set_insert(s, HEAP);
            s = set_insert(s, QUICK);
            break;
        case 'b': s = set_insert(s, BATCHER); break;
        case 's': s = set_insert(s, SHELL); break;
        case 'h': s = set_insert(s, HEAP); break;
        case 'q': s = set_insert(s, QUICK); break;
        case 'n': size = strtol(optarg, NULL, 10); break;
        case 'p': array = strtol(optarg, NULL, 10); break;
        case 'r': seed = strtol(optarg, NULL, 10); break;
        case 'H': help(); break;
        }
    }
    uint32_t *A = (uint32_t *) calloc(size, sizeof(uint32_t));
    int sort_called = 0;
    for (sorts x = BATCHER; x <= QUICK; x++) {
        srandom(seed);

        if (set_member(s, x)) {
            sort_called++;
            random_array(A, size);

            switch (x) {
            case BATCHER: batcher_sort(&stats, A, size); break;
            case HEAP: heap_sort(&stats, A, size); break;
            case SHELL: shell_sort(&stats, A, size); break;
            case QUICK: quick_sort(&stats, A, size); break;
            }

            display_stats(&stats, size, names[x]);
            display_array(A, size, array);
            reset(&stats);
        }
    }

    if (sort_called == 0) {
        help();
    }

    free(A);
    return 0;
}
void random_array(uint32_t *A, uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        A[i] = random() & 0x3FFFFFFF;
    }
    return;
}

void display_array(uint32_t *A, int size, int array) {
    if (size < array) {
        array = size;
    }

    int x = 0;
    for (int i = 0; i < array; i++, x++) {
        printf("%13" PRIu32 " ", A[i]);
        if (((i + 1) % 5) == 0) {
            printf("\n");
        }
    }

    if (x % 5 != 0) {
        printf("\n");
    }
    return;
}

void display_stats(Stats *s, uint32_t size, const char algorithm[]) {
    printf("%s, %" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", algorithm, size,
        s->moves, s->compares);
    return;
}

void help(void) {
    puts("Command Line Options");
    puts("    -a:          employs all sorting algorithms");
    puts("    -b:          enables Batcher Sort");
    puts("    -h:          enables Heap Sort");
    puts("    -s:          enables Shell Sort");
    puts("    -q:          enables Quick Sort");
    puts("    -r seed:     set the random seed to seed, default = 13371453");
    puts("    -n size:     set the array size to size, default = 100");
    puts("    -p elements: print out elements number of elements from the array, default = 100");
    puts("    -H:    	   print out help message, (what you're reading !)");

    return;
}
