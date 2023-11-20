#include <stdio.h>
#include <string.h>
#include <util.h>
#include <runner.h>

#define PROJECT_NAME "advent-of-code"

int main(int argc, char **argv) {
    if(argc == 1) {
        run_all();
    } else {
        char year[BUFFER_SIZE];
        char day[BUFFER_SIZE];
        for(int i = 0; i < argc; i++) {
            if(i % 2 != 0) {
                if(strcmp(argv[i], "-y") == 0 || strcmp(argv[i], "--year") == 0) {
                    strncpy(year, argv[i + 1], sizeof(year) - 1);
                } else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--day") == 0) {
                    strncpy(day, argv[i + 1], sizeof(day) - 1);
                }
            }
        }

        if(year[0] == '\0') {
            printf("Need to specify a year");
            return 1;
        }

        if(day[0] == '\0') {
            run_year(year);
        } else {
            run_day(year, day);
        }
    }
}
