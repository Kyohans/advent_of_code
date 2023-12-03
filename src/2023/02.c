#include <stdlib.h>
#include <stdio.h>

#include <util.h>
#include <years/year2023.h>

#define DELIM ",;:\n "

#if TESTING
#define TESTFILE "../src/2023/test_input/day02"
#else
#define TESTFILE NULL
#endif

#define MAXRED 12
#define MAXGREEN 13
#define MAXBLUE 14
#define MAX(a, b) (a >= b) ? a : b

typedef struct {
    int id;
    int red;
    int blue;
    int green;
} game;

int part1_022023(FILE *);
int part2_022023(FILE *);
int parse_game_p1(char *);
int parse_game_p2(char *);

void day02_2023(const char * filename) {
    printf("-- Day 2 --\n");
    FILE * p1, * p2;

    if(TESTFILE) p1 = fopen(TESTFILE, "r");
    else p1 = fopen(filename, "r");
    printf("Part 1: %d\n", part1_022023(p1));
    fclose(p1);

    if(TESTFILE) p2 = fopen(TESTFILE, "r");
    else p2 = fopen(filename, "r");
    printf("Part 2: %d\n", part2_022023(p2));
    fclose(p2);
}

int part1_022023(FILE * fp) {
    int possible_games = 0;

    char line[BUFFER_SIZE];
    while(fgets(line, BUFFER_SIZE, fp) != 0) {
        possible_games += parse_game_p1(line);
    }

    return possible_games;
}

int part2_022023(FILE * fp) {
    int powers = 0;

    char line[BUFFER_SIZE];
    while(fgets(line, BUFFER_SIZE, fp) != 0) {
        powers += parse_game_p2(line);
    }

    return powers;
}

int parse_game_p1(char * data) {
    char * token = strtok(data, DELIM);
    game * results = (game *)malloc(sizeof(game));

    token = strtok(NULL, DELIM);
    results->id = atoi(token);

    while(token) {
        token = strtok(NULL, DELIM);
        if(token) {
            int num = atoi(token);
            
            token = strtok(NULL, DELIM);
            if(strcmp(token, "red") == 0) results->red = num;
            else if(strcmp(token, "green") == 0) results->green = num;
            else if(strcmp(token, "blue") == 0) results->blue = num;

            if(results->red > MAXRED || results->green > MAXGREEN || results->blue > MAXBLUE) return 0;
        }
    }

    return results->id;
}

int parse_game_p2(char * data) {
    char * token = strtok(data, DELIM);
    int red = 0, blue = 0, green = 0;

    token = strtok(NULL, DELIM);
    while(token) {
        token = strtok(NULL, DELIM);
        if(token) {
            int num = atoi(token);

            token = strtok(NULL, DELIM);
            if(strcmp(token, "red") == 0) red = MAX(red, num);
            else if(strcmp(token, "green") == 0) green = MAX(green, num);
            else if(strcmp(token, "blue") == 0) blue = MAX(blue, num);
        }
    }

    return red * green * blue;
}
