#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <util.h>
#include <years/year2023.h>

#if TESTING
#define TESTFILE "../src/2023/test/day03"
#else
#define TESTFILE NULL
#endif

#define DELIM ".#%$*/@=-+\n"
#define VALIDCHARS "#%$*/@=-+"

int part1_032023(FILE *);
bool ispart(char **, int, int, int, int, int);
bool isadj(char);

void day03_2023(const char * filename) {
    printf("-- Day 3:\n");
    FILE * p1;
    
    if(TESTFILE) p1 = fopen(TESTFILE, "r");
    else p1 = fopen(filename, "r");
    printf("Part 1: %d\n", part1_032023(p1));
    
    return;
}

int part1_032023(FILE * fp) {
    int rows = 0;
    int cols = 0;
    int sum = 0;

    char line[BUFFER_SIZE];
    if(fgets(line, sizeof(line), fp) != 0) cols = strlen(line), rows++;
    while(fgets(line, sizeof(line), fp) != 0) rows++;

    if(fseek(fp, 0, SEEK_SET) != 0) exit(EXIT_FAILURE);

    char ** grid = (char **)malloc(sizeof(char *) * rows);
    for(int i = 0; i < rows; i++) {
        grid[i] = (char *)calloc(cols, sizeof(char));
        fgets(grid[i], cols + 1, fp);
    }
    if(fp) fclose(fp);
    
    for(int r = 0; r < rows; r++) {
        char row[strlen(grid[r])];
        strcpy(row, grid[r]);

        char * t = strtok(row, DELIM);
        int c = 0;
        while(c < cols) {
            if(isdigit(grid[r][c])) {
                int to_add = atoi(t);
                int start = c;
                int end = strlen(t) + start + 1;

                if(ispart(grid, r, start, end, rows, cols)) {
                    sum += to_add;
                    if(t) t = strtok(NULL, DELIM);
                }
                
                c = end + 1;
            } else {
                c++;
            }
        }
    }

    return sum;
}

bool ispart(char ** grid, int row, int start, int end, int numrows, int numcols) {
    char top[strlen(grid[row])];
    char bottom[strlen(grid[row])];
    if(row - 1 >= 0) strncpy(top, grid[row - 1] + (start - 1), (end - start + 1));
    if(row + 1 < numrows) strncpy(bottom, grid[row + 1] + (start - 1), (end - start + 1));

    if(strpbrk(top, VALIDCHARS) || strpbrk(bottom, VALIDCHARS)) return true;
    if((start - 1 >= 0 && isadj(grid[row][start - 1])) || (end + 1 < numcols && isadj(grid[row][end + 1]))) return true;

    return false;
}

// bool ispart(char ** grid, int row, int start, int end, int numrows, int numcols) {
//     char topleft = '\0', left = '\0', bottomleft = '\0';
//     if(row - 1 >= 0 && start - 1 >= 0) topleft = grid[row - 1][start - 1];
//     if(row + 1 <= numrows && start - 1 >= 0) bottomleft = grid[row + 1][start - 1];
//     if(start - 1 >= 0) left = grid[row][start - 1];
//
//     if(isadj(topleft) || isadj(left) || isadj(bottomleft)) return true;
//
//     char topright = '\0', right = '\0', bottomright = '\0';
//     if(row - 1 >= 0 && end + 1 <= numcols) topright = grid[row - 1][end + 1];
//     if(row + 1 <= numrows && end + 1 <= numcols) bottomright = grid[row + 1][end + 1];
//     if(end + 1 <= numcols) right = grid[row][end + 1];
//
//     if(isadj(topright) || isadj(right) || isadj(bottomright)) return true;
//     
//     while(start <= end) {
//         char top = '\0', bottom = '\0';
//         if(row - 1 >= 0) top = grid[row - 1][start];
//         if(row + 1 <= numrows) bottom = grid[row + 1][start];
//
//         if(isadj(top) || isadj(bottom)) return true;
//
//         start++;
//     }
//
//     return false;
// }
//
bool isadj(char chr) {
    return chr != '.' && chr != '\0' && !isdigit(chr);
}
