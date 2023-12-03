#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util.h>
#include <ctype.h>
#include <string.h>

#include <years/year2023.h>

#if TESTING
#define TESTFILEP1 "../src/2023/test_input/day01"
#define TESTFILEP2 "../src/2023/test_input/day01_2"
#else
#define TESTFILEP1 NULL
#define TESTFILEP2 NULL
#endif

#define NUMSSIZE 9
#define MAXNUMLEN 5

static char * nums[NUMSSIZE] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int part1_012023(FILE *);
int part2_012023(FILE *);
int ischrdigit(char);
void substr(char *, char *, int, int);
void search_for_num(char *, int *, bool);

void day01_2023(const char * filename) {
    printf("-- Day 01 - 2023 --\n");

    FILE * p1, * p2;
    if(TESTFILEP1) p1 = fopen(TESTFILEP1, "r");
    else p1 = fopen(filename, "r");

    if(p1 == NULL) exit(EXIT_FAILURE);
    printf("Part 1: %d\n", part1_012023(p1));
    fclose(p1);

    if(TESTFILEP2) p2 = fopen(TESTFILEP2, "r");
    else p2 = fopen(filename, "r");

    if(p2 == NULL) exit(EXIT_FAILURE);
    printf("Part 2: %d\n", part2_012023(p2));
    fclose(p2);
}

int part1_012023(FILE * fp) {
    char line[BUFFER_SIZE];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != 0) {
        int left = 0;
        int right = strlen(line) - 1;

        while(ischrdigit(line[left]) == -1) left++;
        while(ischrdigit(line[right]) == -1) right--;

        int num = (0 * 10 + (line[left] - '0'));
        num = (num * 10 + (line[right] - '0'));

        sum += num;
    }

    return sum;
}

/* TODO: Still need to complete solution */
int part2_012023(FILE * fp) {
    char line[BUFFER_SIZE];

    int sum = 0;
    int lnum = -1, rnum = -1;
    while(fgets(line, sizeof(line), fp) != 0) {
        int start_idx[NUMSSIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        int end_idx[NUMSSIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        int len = strlen(line);

        search_for_num(line, start_idx, true);
        search_for_num(line, end_idx, false);

        int ldigit = -1;
        for(int i = 0; i < len; i++) {
            if(ischrdigit(line[i])) {
                ldigit = i;
                break;
            }
        }

        int rdigit = -1;
        for(int i = len - 1; i >= 0; i--) {
            if(ischrdigit(line[i])) {
                rdigit = i;
                break;
            }
        }

        int min_start = INT_MAX, min_end = INT_MAX;
        int starti = -1, endi = -1;
        for(int i = 0; i < NUMSSIZE; i++) {
            if(min_start > start_idx[i]) {
                min_start = start_idx[i];
                starti = i;
            }

            if(min_end > end_idx[i]) {
                min_end = end_idx[i];
                endi = i;
            }
        }

        if(ldigit >= 0 && ldigit < min_start) lnum = line[ldigit] - '0';
        else lnum = starti + 1;

        if(rdigit >= 0 && rdigit < min_end) rnum = line[rdigit] - '0';
        else rnum = endi + 1;

        sum = sum * 10 + lnum;
        sum = sum * 10 + rnum;
    }
    return sum;
}

int ischrdigit(char ch) {
    int digit = ch - '0';
    return (digit >= 0 && digit <= 9) ? digit : -1;
}

void substr(char * dest, char * src, int offset, int len) {
    strncpy(dest, src+offset, len);
}

void search_for_num(char * line, int idx[], bool at_start) {
    int incdec = (at_start) ? 1 : -1;

    int len = strlen(line);
    int i = (at_start) ? 0 : len - 1;
    while(i >= 0 && i < len) {
        for(int n = 0; n < NUMSSIZE; n++) {
            int num_left = 0;
            int num_right = strlen(nums[n]) - 1;

            while(num_right < len) {
                char buf[strlen(nums[n])];
                substr(buf, line, num_left, num_right - num_left + 1);
                if(strcmp(buf, nums[n]) == 0) idx[n] = num_left;

                num_left++;
                num_right++;
            }
        }

        i += incdec;
    }
}
