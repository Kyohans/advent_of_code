#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <years/year2023.h>
#include <util.h>

#if TESTING
#define TESTFILE "../src/2023/test/day05"
#else
#define TESTFILE NULL
#endif

#define MAXSEEDS 100
#define MAPROWS 100
#define NUMMAPS 7
#define DELIM " \n"

#define MIN(a, b) (a < b) ? a : b

int part1_052023(FILE *);
int matchstr(char *);

void day05_2023(const char * filename) {
    FILE * p1;
    if(TESTFILE) p1 = fopen(TESTFILE, "r");
    else p1 = fopen(filename, "r");
    printf("Part 1: %d\n", part1_052023(p1));
    fclose(p1);
}

int part1_052023(FILE * fp) {
    int seeds[MAXSEEDS];
    size_t seedlen = 0;

    char seedstr[BUFFER_SIZE/2];
    if(fgets(seedstr, sizeof(seedstr), fp) == 0) exit(EXIT_FAILURE);
    char * token = strtok(seedstr, DELIM);
    token = strtok(NULL, DELIM);
    while(token) {
        seeds[seedlen] = atoi(token);
        token = strtok(NULL, DELIM);
        seedlen++;
    }

    char line[BUFFER_SIZE];
    int map[NUMMAPS][MAPROWS][3] = {0};
    int numrows[NUMMAPS] = {0};
    int i = -1;

    int j = 0;
    while(fgets(line, sizeof(line), fp) != 0) {
        numrows[i] = j + 1;

        if(isdigit(line[0])) {
            char * dest = strtok(line, DELIM);
            char * src = strtok(NULL, DELIM);
            char * range = strtok(NULL, DELIM);

            if(dest) map[i][j][0] = atoi(dest);
            if(src) map[i][j][1] = atoi(src);
            if(range) map[i][j][2] = atoi(range);
            
            j++;
        } else if(line[0] != '\n') {
            i++;
            j = 0;
        }
    }
    numrows[NUMMAPS-1]++;

    for(size_t i = 0; i < seedlen; i++) {
        printf("%d\n", seeds[i]);
    }

    int min_location = INT_MAX;
    return 0;

}

// int find_location(int * map[][], int seed, int map) {
//     return 0;
// }
