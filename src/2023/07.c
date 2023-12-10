#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <util.h>
#include <years/year2023.h>

#define HANDSIZE 5
#define DELIM " \n"
#define TESTFILE "../src/2023/test/day07"
#define CARDSETSIZE 'Z' - '0'

typedef enum {
    FIVEOAK = 1,
    FOUROAK,
    FULL,
    THREEOAK,
    TWO,
    ONE,
    HIGH
} hand_type;

typedef struct {
    char hand[HANDSIZE];
    int bid;
    int rank;
    hand_type type;
} hand_t;

uint64_t part1_072023(FILE *);
hand_type detype(char *);

void day07_2023(const char * filename) {
    printf("-- Day 7: %s\n", filename);

    FILE * p1;
    if(TESTING) p1 = fopen(TESTFILE, "r");
    else p1 = fopen(filename, "r");
    part1_072023(p1);
    fclose(p1);
}

uint64_t part1_072023(FILE * fp) {
    size_t numcards = 0;
    char line[BUFFER_SIZE/4];
    while(fgets(line, sizeof(line), fp) != 0) numcards++;

    if(fseek(fp, 0, SEEK_SET) != 0) exit(EXIT_FAILURE);

    size_t i = 0;
    hand_t ** cards = (hand_t **)malloc(sizeof(hand_t *) * numcards);
    while(fgets(line, sizeof(line), fp) != 0) {
        char * hand = strtok(line, DELIM);
        char * bid = strtok(NULL, DELIM);

        cards[i] = (hand_t *)malloc(sizeof(hand_t));
        strcpy(cards[i]->hand, hand);
        cards[i]->bid = atoi(bid);
        cards[i]->rank = 0;
        cards[i]->type = 0;

        i++;
    }

    for(size_t i = 0; i < numcards; i++) {
        printf("Hand %lu: %s -- %d\n", i + 1, cards[i]->hand, cards[i]->bid);
        detype(cards[i]->hand);
    }

    return 0;
}

hand_type detype(char * hand) {
    int count[CARDSETSIZE] = {0};

    for(size_t i = 0; i < HANDSIZE; i++) {
        count[hand[i] - '2']++;
    }

    for(int i = 0; i < CARDSETSIZE; i++) {
        if(count[i] > 0) {
            char h = (char)(i + '2');
            printf("Card %c: %d\n", h, count[i]);
        }
    }

    return FIVEOAK;
}
