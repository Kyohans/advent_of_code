#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <runner.h>

#define PROJECT_NAME "advent-of-code"

void usage(void);

int main(int argc, char **argv) {
    if(argc == 1) {
        run_all();
    } else {
        char year[BUFFER_SIZE];
        char day[BUFFER_SIZE];
        year[0] = '\0';
        day[0] = '\0';
        for(int i = 0; i < argc; i++) {
            if(i % 2 != 0) {
                if(strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "--year") == 0) {
                    strncpy(year, argv[i + 1], sizeof(year) - 1);
                } else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--day") == 0) {
                    strncpy(day, argv[i + 1], sizeof(day) - 1);
                } else {
                    usage();
                    return 1;
                }
            }
        }

        if(day[0] != '\0' && year[0] == '\0') {
            fprintf(stderr, "Need to specify a year to run a specific day");
            exit(EXIT_FAILURE);
        }

        if(day[0] == '\0') {
            run_year(year);
        } else {
            run_day(year, day);
        }
    }
}

void usage(void) {
    char day_desc[] = "-d(--day) d: Runs solution for day that is specified. Need to specify a year to do this";
    char year_desc[] = "-y(--year) y: Runs solution for specified year. Will run all of my AOC solutions for each year if no year is specified";
    fprintf(stderr, 
            "usage: advent_of_code [options]\noptions:\n\t%s\n\t%s",
            day_desc, year_desc);
    exit(EXIT_FAILURE);
}
