#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util.h>
#include <ctype.h>
#include <string.h>

#include <years/year2023.h>

#define TESTFILEP1 "../src/2023/test/day01"
#define TESTFILEP2 "../src/2023/test/day01_2"

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

    FILE * p1 = fopen((TESTING) ? TESTFILEP1 : filename, "r");
    if(p1 == NULL) exit(EXIT_FAILURE);
    printf("Part 1: %d\n", part1_012023(p1));
    fclose(p1);

    FILE * p2 = fopen((TESTING) ? TESTFILEP2 : filename, "r");
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
        int lnums[NUMSSIZE];
        for(int i = 0; i < NUMSSIZE; i++) lnums[i] = -1;

        for(int n = 0; n < NUMSSIZE; n++) {
            const char * found = strstr(line, nums[n]);
            if(found != NULL) {
                lnums[n] = found - line;
            }
        }

        int rnums[NUMSSIZE];
        for(int i = 0; i < NUMSSIZE; i++) rnums[i] = -1;

        for(int n = 0; n < NUMSSIZE; n++) {
            const char * found = strstr(line, nums[n]);
            int i = (found != NULL) ? found - line : -1;
            while(found) {
                found = strstr(found + 1, nums[n]);
                i = (found != NULL) ? found - line : i;
            }

            rnums[n] = i;
        }

        int lefti = -1, righti = -1;
        int min = INT_MAX, max = -1;
        for(int i = 0; i < NUMSSIZE; i++) {
            if(lnums[i] <= min && lnums[i] != -1) {
                min = lnums[i];
                lefti = i;
            }

            if(rnums[i] >= max && rnums[i] != -1) {
                max = rnums[i];
                righti = i;
            }
        }

        int lnum = 0;
        int rnum = 0;

        char * lptr = strpbrk(line, "123456789");
        if(lptr != NULL) {
            lnum = (lptr - line < min) ? lptr[0] - '0' : lefti + 1;
        } else {
            lnum = lefti + 1;
        }

        char * rptr = strpbrk(line, "123456789");
        int r = (rptr) ? rptr - line : -1;
        while(rptr) {
            rptr = strpbrk(rptr + 1, "123456789");
            r = (rptr) ? rptr - line : r;
        }

        if(r >= 0) {
            rnum = (r > max) ? line[r] - '0' : righti + 1;
        } else {
            rnum = righti + 1;
        }

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
