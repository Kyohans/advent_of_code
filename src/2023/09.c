#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <years/year2023.h>

#define TESTFILE "../src/2023/test/day09"
#define DELIM " \n"

uint64_t solution_092023(FILE *, bool);
uint64_t findval(int *, size_t, bool);

void day09_2023(const char * filename) {
    printf("-- Day 9\n");

    FILE * p1 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 1: %lu\n", solution_092023(p1, false));
    fclose(p1);

    FILE * p2 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 2: %lu\n", solution_092023(p2, true));
    fclose(p2);
}

uint64_t solution_092023(FILE * fp, bool p2) {
    char line[BUFFER_SIZE];
    uint64_t ans = 0;
    while(fgets(line, sizeof(line), fp) != 0) {
       size_t size = 0;
       int history[BUFFER_SIZE/2] = {0};

       char * tok = strtok(line, DELIM);
       while(tok) {
           history[size++] = atoi(tok);
           tok = strtok(NULL, DELIM);
       }

       ans += findval(history, size, p2);
    }

    return ans;
}

uint64_t findval(int * history, size_t size, bool p2) {
    if(history && history[0] == 0 && history[size - 1] == 0) return 0;

    int * sequence = (int *)calloc(size - 1, sizeof(int));
    for(size_t i = 1; i < size; i++) {
        sequence[i - 1] = history[i] - history[i - 1];
    }

    return (p2) ? history[0] - findval(sequence, size - 1, p2) : history[size - 1] + findval(sequence, size - 1, p2);
}
