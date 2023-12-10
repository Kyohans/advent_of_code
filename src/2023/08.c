#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <util.h>
#include <years/year2023.h>

#define TESTFILE "../src/2023/test/day08_2"
#define DELIM " =(),"

#define MAPSIZE BUFFER_SIZE * 2
#define NODELEN 3

#define HASH(k) (k[0] + k[1] + k[2]) % MAPSIZE

typedef struct {
    char * key;
    char * left;
    char * right;
} keypair;

int part1_082023(FILE *);
int traverse_path(char *, size_t, size_t, keypair **, char *, char *, char *);

void day08_2023(const char * filename) {
    printf("-- Day 8: %s\n", filename);

    FILE * p1 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 1: %d\n", part1_082023(p1));
    fclose(p1);
}

int part1_082023(FILE * fp) {
    char line[BUFFER_SIZE + (BUFFER_SIZE / 2)];
    char directions[BUFFER_SIZE + (BUFFER_SIZE / 2)];
    keypair * map[MAPSIZE] = {0};

    if(fgets(line, sizeof(line), fp) == 0) exit(EXIT_FAILURE);
    strncpy(directions, line, strlen(line) - 1);

    if(fseek(fp, 1, SEEK_CUR) != 0) exit(EXIT_FAILURE);
    while(fgets(line, sizeof(line), fp) != 0) {
        char * key = strtok(line, DELIM);
        char * left = strtok(NULL, DELIM);
        char * right = strtok(NULL, DELIM);

        int hidx = HASH(key);
        map[hidx] = (keypair *)malloc(sizeof(keypair));
        map[hidx]->key = (char *)malloc(sizeof(key));
        map[hidx]->left = (char *)malloc(sizeof(left));
        map[hidx]->right = (char *)malloc(sizeof(right));

        strcpy(map[hidx]->key, key);
        strcpy(map[hidx]->left, left);
        strcpy(map[hidx]->right, right);
    }

    char * start = "AAA";
    char * end = "ZZZ";

    return traverse_path(directions, strlen(directions), 0, map, NULL, start, end);
}

int traverse_path(char * directions, size_t dlen, size_t i, keypair ** map, char * prev, char * curr, char * end) {
    int hidx = HASH(curr);
    printf("idx: %d, key: %s\n", hidx, map[hidx]->key);
    if((prev && strcmp(map[hidx]->key, prev) == 0) || strcmp(map[hidx]->key, end) == 0) return 0;

    char dir = directions[i];
    return 1 + traverse_path(directions, dlen, (i + 1 < dlen) ? i + 1 : 0, map, curr, (dir == 'L') ? map[hidx]->left : map[hidx]->right, end);
}


