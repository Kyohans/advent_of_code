#include <runner.h>
#include <aocfunc.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>

size_t get_year_index(const char *);

void run_day(const char * year, const char * day) {
    char filename[BUFFER_SIZE];

    if(!TESTING) {
        if(fetch_input(year, day) != 0) {
            fprintf(stderr, "Fetch input failed");
            exit(EXIT_FAILURE);
        }

        sprintf(filename, "/tmp/year%s_%s.input", year, day);
    } else {
        sprintf(filename, "using test file...");
    }
    
    size_t year_idx = get_year_index(year);
    size_t day_idx = atoi(day);
    if(day_idx <= 0 || day_idx > 25) {
        fprintf(stderr, "Invalid day. Day should be in the range [1,25]");
        exit(EXIT_FAILURE);
    }

    if(year_idx >= NUM_YEARS) {
        fprintf(stderr, "Invalid year. Year must be between 2021-2023");
        exit(EXIT_FAILURE);
    }

    functions[year_idx][day_idx - 1](filename);
    cleanup_file(filename);
}

void run_year(const char * year) {
    int year_idx = get_year_index(year);
    for(size_t i = 1; i <= 25; i++) {
        char day[BUFFER_SIZE];
        sprintf(day, "%lu", i);
        run_day(year, day);
    }
}

void run_all(void) {
    printf("Running all Advent Of Code years\n");
    for(int y = 0; y < NUM_YEARS; y++) {
        char curr[BUFFER_SIZE/6];
        sprintf(curr, "%d", STARTING_YEAR + y);
        printf("-- AOC Year %s\n", curr);
        run_year(curr);
    }
}

size_t get_year_index(const char * year) {
    return atoi(year) % STARTING_YEAR;
}
