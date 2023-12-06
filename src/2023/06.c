#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <years/year2023.h>

#if TESTING
#define TESTFILE "../src/2023/test/day06"
#else
#define TESTFILE NULL
#endif

#define MAXLEN 4
#define DELIM " \n"

int part1_062023(FILE *);
int part2_062023(FILE *);
void parsems(char * line, uint64_t *);
bool beats_record(uint64_t, uint64_t, uint64_t);

void day06_2023(const char * filename) {
    printf("-- Day 6\n");

    FILE * p1, * p2;
    if(TESTFILE) p1 = fopen(TESTFILE, "r");
    else p1 = fopen(filename, "r");
    printf("Part 1: %d\n", part1_062023(p1));
    fclose(p1);

    if(TESTFILE) p2 = fopen(TESTFILE, "r");
    else p2 = fopen(filename, "r");
    printf("Part 2: %d\n", part2_062023(p2));
    fclose(p2);
}

int part1_062023(FILE * fp) {
    int time[MAXLEN] = {0};
    int dist[MAXLEN] = {0};
    int itime = 0;
    int idist = 0;

    char line[BUFFER_SIZE/4];
    if(fgets(line, sizeof(line), fp) == 0) exit(EXIT_FAILURE);
    char * ttok = strtok(line, DELIM);
    ttok = strtok(NULL, DELIM);
    while(ttok) {
        time[itime++] = atoi(ttok);
        ttok = strtok(NULL, DELIM);
    }

    if(fgets(line, sizeof(line), fp) == 0) exit(EXIT_FAILURE);
    char * dtok = strtok(line, DELIM);
    dtok = strtok(NULL, DELIM);
    while(dtok) {
        dist[idist++] = atoi(dtok);
        dtok = strtok(NULL, DELIM);
    }

    int product = 1;
    for(int i = 0; i <= itime; i++) {
        int ways = 0;
        for(int j = 0; j <= time[i]; j++) {
            int hold_time = j;
            int remaining_time = time[i] - j;
            int distance = hold_time * remaining_time;
            if(distance > dist[i]) ways++;
        }

        if(ways > 0) product *= ways;
    }

    return product;
}

int part2_062023(FILE * fp) {
    uint64_t time = 0;
    uint64_t dist = 0;

    char line[BUFFER_SIZE/4];
    if(fgets(line, sizeof(line), fp) == 0) exit(EXIT_FAILURE);
    parsems(line, &time);

    if(fgets(line, sizeof(line), fp) == 0) exit(EXIT_FAILURE);
    parsems(line, &dist);

    uint64_t left = time/2, right = left;
    while(beats_record(dist, left, time) && beats_record(dist, right, time)) {
        left--;
        right++;
    }

    return (right - 1) - (left + 1) + 1;
}

void parsems(char * line, uint64_t * num) {
    char * tok = strtok(line, DELIM);
    tok = strtok(NULL, DELIM);

    while(tok) {
        for(size_t i = 0; i < strlen(tok); i++) {
            *num = (*num) * 10 + (tok[i] - '0');
        }
        tok = strtok(NULL, DELIM);
    }
}

bool beats_record(uint64_t record, uint64_t hold_time, uint64_t time) {
    return (hold_time * (time - hold_time)) > record;
}
