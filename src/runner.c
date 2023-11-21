#include <runner.h>
#include <aocfunc.h>
#include <stdio.h>
#include <stdlib.h>
#include <util.h>

size_t get_year_index(const char *);

void run_day(const char * year, const char * day) {
    if(fetch_input(year, day) != 0) {
        fprintf(stderr, "Fetch input failed");
        exit(EXIT_FAILURE);
    }

    char filename[BUFFER_SIZE];
    sprintf(filename, "/tmp/year%s_%s.input", year, day);
    
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

    if(day_idx > NUM_DAYS_BY_YEAR[year_idx]) {
        fprintf(stderr, "Solution for day %lu for year %s has not been completed yet!\n", day_idx, year);
        return;
    }

    functions[year_idx][day_idx - 1](filename);
    cleanup_file(filename);
}

void run_year(const char * year) {
    int year_idx = get_year_index(year);
    for(size_t i = 1; i <= NUM_DAYS_BY_YEAR[year_idx]; i++) {
        char day[BUFFER_SIZE];
        sprintf(day, "%lu", i);
        run_day(year, day);
    }
}

void run_all(void) {
    printf("Running all Advent Of Code years\n");
    return;
}

size_t get_year_index(const char * year) {
    return atoi(year) % STARTING_YEAR;
}
