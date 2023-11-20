#include <runner.h>
#include <aocfunc.h>
#include <util.h>

void run_day(const char * year, const char * day) {
    if(fetch_input(year, day) != 0) {
        perror("Fetch input failed");
        return;
    }

    char filename[BUFFER_SIZE];
    sprintf(filename, "/tmp/year%s_%s.input", year, day);
    
    int year_idx = atoi(year) % STARTING_YEAR;
    int day_idx = atoi(day);
    if(day_idx <= 0 || day_idx > 25) return;

    functions[year_idx][day_idx - 1](filename);
    cleanup_file(filename);
}

void run_year(const char * year) {
    printf("Running year %s\n", year);
    return;
}

void run_all(void) {
    printf("Running all Advent Of Code years\n");
    return;
}
