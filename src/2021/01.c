#include <util.h>
#include <year2021.h>

#define WINDOW_SIZE 3

int part1(FILE *);
int part2(FILE *);
int window_sum(int *);

void day01_2021(const char * filename) {
    printf("Day 1\n");
    FILE * p1 = fopen(filename, "r");
    printf("\tPart 1: %d\n", part1(p1));
    fclose(p1);

    FILE * p2 = fopen(filename, "r");
    printf("\tPart 2: %d\n", part2(p2));
    fclose(p2);
}

int part1(FILE * input) {
    int count = 0;
    int current = 0;
    char line[BUFFER_SIZE];

    while(fgets(line, BUFFER_SIZE, input) != 0) {
        int measurement = atoi(line);
        if(measurement > current && current != 0) count++;
        current = measurement;
    }
    
    return count;
}

int part2(FILE * input) {
    int count = 0;
    int i = 0;
    int current_sum = 0;

    int * window = calloc(WINDOW_SIZE, sizeof(int));
    char line[BUFFER_SIZE];
    while(fgets(line, BUFFER_SIZE, input) != 0) {
        int n = atoi(line);
        window[i % WINDOW_SIZE] = n;

        int sum = 0;
        for(int i = 0; i < WINDOW_SIZE; i++) sum += window[i];
        if(sum > current_sum) {
            count++;
            current_sum = sum;
        }
        i++;
    }

    free(window);
    return count;
}

int window_sum(int * window) {
    int sum = 0;
    for(int i = 0; i < WINDOW_SIZE; i++) sum += window[i];
    return sum;
}
