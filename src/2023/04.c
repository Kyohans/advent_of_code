#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <util.h>
#include <years/year2023.h>

#define MAXNUM 100
#define DELIM ":|\n"

#define TESTFILE "../src/2023/test/day04"

int count_nums(int *);
int follow_rules(int *, int);
int part1_042023(FILE *);
int part2_042023(FILE *);

void day04_2023(const char * filename) {
    printf("-- Day 4\n");

    FILE * p1 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 1: %d\n", part1_042023(p1));
    fclose(p1);

    FILE * p2 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 2: %d\n", part2_042023(p2));
    fclose(p2);
}

int part1_042023(FILE * fp) {
    char line[BUFFER_SIZE];
    int total = 0;

    while(fgets(line, sizeof(line), fp) != 0) {
        int wnums[MAXNUM] = {0};

        char * token = strtok(line, DELIM);
        token = strtok(NULL, DELIM);
        char winning_numbers[BUFFER_SIZE];
        char numbers[BUFFER_SIZE];

        strcpy(winning_numbers, token);
        token = strtok(NULL, DELIM);
        strcpy(numbers, token);

        char * i = strtok(winning_numbers, " \n");
        while(i) {
            if(i) {
                wnums[atoi(i) - 1]++;
                i = strtok(NULL, " \n");
            }
        }

        int points = 0;
        char * j = strtok(numbers, " \n");
        while(j) {
            if(j) {
                if(wnums[atoi(j) - 1] > 0) {
                    if(points > 0) points *= 2;
                    else points = 1;
                }

                j = strtok(NULL, " \n");
            }
        }

        total += points;
    }

    return total;
}

int part2_042023(FILE * fp) {
    char line[BUFFER_SIZE];

    int numcards = 0;
    while(fgets(line, sizeof(line), fp) != 0) numcards++;
    fseek(fp, 0, SEEK_SET);

    if(fp == NULL) exit(EXIT_FAILURE);

    int * cards = calloc(numcards, sizeof(int));
    int idx = 0;
    while(fgets(line, sizeof(line), fp) != 0) {
        int wnums[MAXNUM] = {0};

        char * token = strtok(line, DELIM);
        token = strtok(NULL, DELIM);

        char winning_numbers[strlen(token) + 1];
        strncpy(winning_numbers, token, strlen(token));

        token = strtok(NULL, DELIM);
        char numbers[strlen(token) + 1];
        strncpy(numbers, token, strlen(token));

        char * w = strtok(winning_numbers, " \n");
        while(w) {
            if(w) {
                wnums[atoi(w) - 1] = 1;
                w = strtok(NULL, " \n");
            }
        }

        char * n = strtok(numbers, " \n");
        while(n) {
            if(n) {
                if(wnums[atoi(n) - 1] > 0) {
                    wnums[atoi(n) - 1]++;
                }

                n = strtok(NULL, " \n");
            }
        }

        if(idx < numcards) {
            cards[idx] = count_nums(wnums);
            idx++;
        }
    }

    int answer = 0;
    for(int i = 0; i < numcards; i++) {
        answer += follow_rules(cards, i);
    }

    return answer;
}

int count_nums(int * winning_nummbers) {
    int c = 0;
    for(int i = 0; i < MAXNUM; i++) c += (winning_nummbers[i] > 1) ? 1 : 0;
    return c;
}

int follow_rules(int * cards, int card) {
    if(cards[card] <= 0) return 1;

    int add = 1;
    for(int i = 1; i <= cards[card]; i++) {
        add += follow_rules(cards, card + i);
    }

    return add;
}
