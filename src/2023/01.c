#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util.h>
#include <ctype.h>
#include <string.h>

#include <years/year2023.h>

#if TESTING
#define TESTFILEP1 "../src/2023/test/day01"
#define TESTFILEP2 "../src/2023/test/day01_2"
#else
#define TESTFILEP1 NULL
#define TESTFILEP2 NULL
#endif

#define NUMSSIZE 9
#define MAXNUMLEN 5

#define MAX(a, b) (a > b) ? a : b;
#define MIN(a, b) (a < b && a >= 0 && b >= 0) ? a : b;

static char * nums[NUMSSIZE] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int part1_012023(FILE *);
int part2_012023(FILE *);
void strrev(char *);
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

        while(!isdigit(line[left])) left++;
        while(!isdigit(line[right])) right--;

        int num = (0 * 10 + (line[left] - '0'));
        num = (num * 10 + (line[right] - '0'));

        sum += num;
    }

    return sum;
}

int part2_012023(FILE * fp) {
    char line[BUFFER_SIZE];

    int sum = 0;
    while(fgets(line, sizeof(line), fp) != 0) {
        int len = strlen(line);
        int inums[NUMSSIZE];
        for(int i = 0; i < NUMSSIZE; i++) inums[i] = -1;

        for(int n = 0; n < NUMSSIZE; n++) {
            const char * found = strstr(line, nums[n]);
            if(found != NULL) {
                inums[n] = found - line;
            }
            printf("n: %d -- %s -- %d\n", n+1, nums[n], inums[n]);
        }

        char rev[BUFFER_SIZE];
        strncpy(rev, line, sizeof(rev));
        strrev(rev);
        printf("Reverse string: %s\n", rev);

        char * lptr = strpbrk(line, "123456789");
        char * rptr = strpbrk(rev, "123456789");
        if(lptr) printf("Left digit found: %s\n", lptr);
        else printf("Left digit not found\n");

        if(rptr) printf("Right digit found: %s\n", rptr);
        else printf("Right digit not found\n");

        int lefti = -1, righti = -1;
        for(int i = 0; i < NUMSSIZE; i++) {
            if(lefti == -1 || lefti > inums[i]) {
                lefti = (inums[i] == -1) ? -1 : i;
                righti = (inums[i] == -1) ? -1 : i;
            } else {
                righti = (inums[i] == -1) ? -1 : i;
            }
        }

        int lnum = 0;
        int rnum = 0;

        if(lptr != NULL) {
            printf("Left pointer should be at index: %lu\n", lptr - line);
            lnum = (lptr - line < lefti) ? lptr[0] - '0' : inums[lefti];
        } else {
            lnum = inums[lefti];
            printf("%d, %s\n", inums[lefti], nums[lefti]);
        }

        if(rptr != NULL) {
            printf("Right pointer should be at index: %lu\n", (len - (rptr - rev)));
            rnum = (len - (rptr - rev) > righti) ? rptr[0] - '0' : inums[righti];
        } else {
            printf("%d: %d, %s\n", righti, inums[righti], nums[righti]);
            rnum = inums[righti];
        }

        printf("Line: %s\nLeft: %d, Right: %d\n", line, lnum, rnum);

        int num = lnum * 10 + rnum;
        sum += num;
    }

    return sum;
}

// From GFG
void strrev(char * str) {
    if (!str) {
        return;
    }

    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
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
                if(strcmp(buf, nums[n]) == 0) idx[n] = num_left;

                num_left++;
                num_right++;
            }
        }

        i += incdec;
    }
}
