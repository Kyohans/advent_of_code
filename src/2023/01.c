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
        int ileftnums[NUMSSIZE];
        int irightnums[NUMSSIZE];
        for(int i = 0; i < NUMSSIZE; i++) ileftnums[i] = -1, irightnums[i] = -1;

        char temp[len + 1];
        strncpy(temp, line, len);
        temp[len] = '\0';

        for(int n = 0; n < NUMSSIZE; n++) {
            const char * found = strstr(temp, nums[n]);
            if(found != NULL) {
                ileftnums[n] = found - temp;
            }
        }

        for(int n = 0; n < NUMSSIZE; n++) {
            int left = 0, right = strlen(nums[n]);
            int i = len - 1;

            while(i >= 0) {
                char buf[len];
                substr(buf, temp, left + i, right);
                char * found = strstr(buf, nums[n]);
                if(found != NULL) irightnums[n] = i;
                i--;
            }
        }

        char rev[len];
        strcpy(rev, line);
        strrev(rev);

        char * lptr = strpbrk(line, "123456789");
        char * rptr = strpbrk(rev, "123456789");

        int lnum = 0;
        int rnum = 0;
        if(lptr != NULL) lnum = lptr[0] - '0';
        if(rptr != NULL) rnum = rptr[0] - '0';

        int lmin = INT_MAX, rmax = -1;
        for(int n = 0; n < NUMSSIZE; n++) {
            if(!lptr || (ileftnums[n] != -1 && ileftnums[n] < lptr - line)) lnum = n + 1;
            else lnum = (lmin < ileftnums[n]) ? lnum : n + 1;
            if(!rptr || (irightnums[n] != -1 && irightnums[n] < rptr - rev)) rnum = n + 1;
            else rnum = (rmax > irightnums[n]) ? rnum : n + 1;

            lmin = MIN(lmin, ileftnums[n]);
            rmax = MAX(rmax, irightnums[n]);
        }


        int num = 0 * 10 + lnum;
        num = num * 10 + rnum;
        sum += num;

        printf("Left: %d, Right: %d, Num: %d, Sum: %d\n", lnum, rnum, num, sum);
    }

    return sum;
}

/* TODO: Still need to complete solution */
// int part2_012023(FILE * fp) {
//     char line[BUFFER_SIZE];
//
//     int sum = 0;
//     int lnum = -1, rnum = -1;
//     while(fgets(line, sizeof(line), fp) != 0) {
//         int start_idx[NUMSSIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
//         int end_idx[NUMSSIZE] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
//         int len = strlen(line);
//
//         search_for_num(line, start_idx, true);
//         search_for_num(line, end_idx, false);
//
//         int ldigit = -1;
//         for(int i = 0; i < len; i++) {
//             if(ischrdigit(line[i])) {
//                 ldigit = i;
//                 break;
//             }
//         }
//
//         int rdigit = -1;
//         for(int i = len - 1; i >= 0; i--) {
//             if(ischrdigit(line[i])) {
//                 rdigit = i;
//                 break;
//             }
//         }
//
//         int min_start = INT_MAX, min_end = INT_MAX;
//         int starti = -1, endi = -1;
//         for(int i = 0; i < NUMSSIZE; i++) {
//             if(min_start > start_idx[i]) {
//                 min_start = start_idx[i];
//                 starti = i;
//             }
//
//             if(min_end > end_idx[i]) {
//                 min_end = end_idx[i];
//                 endi = i;
//             }
//         }
//
//         if(ldigit >= 0 && ldigit < min_start) lnum = line[ldigit] - '0';
//         else lnum = starti + 1;
//
//         if(rdigit >= 0 && rdigit < min_end) rnum = line[rdigit] - '0';
//         else rnum = endi + 1;
//
//         sum = sum * 10 + lnum;
//         sum = sum * 10 + rnum;
//     }
//     return sum;
// }

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
