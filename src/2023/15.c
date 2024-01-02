#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <years/year2023.h>
#include <util.h>

#define MUL 17
#define DIV 256
#define DELIM " ,\n"
#define DELIM2 "-="
#define BUFSIZ15 65535
#define BOXSIZE 256

#define TESTFILE "../src/2023/test/day15"

struct _node {
    char * label;
    int fval;
    struct _node * prev;
    struct _node * next;
};

typedef struct _node node;

int part1_152023(FILE *);
int part2_152023(FILE *);
int hash(char *);
void move(node *, char *, int, bool);
void printbox(node *);

void day15_2023(const char * filename) {
    printf("-- Day 15:\n");

    FILE * p1 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 1: %d\n", part1_152023(p1));
    fclose(p1);

    FILE * p2 = fopen((TESTING) ? TESTFILE : filename, "r");
    printf("Part 2: %d\n", part2_152023(p2));
    fclose(p2);
}

int part1_152023(FILE * fp) {
    char seq[BUFSIZ15];
    if(fgets(seq, sizeof(seq), fp) == 0) exit(EXIT_FAILURE);

    int result = 0;
    char * token = strtok(seq, DELIM);
    while(token) {
        result += hash(token);
        token = strtok(NULL, DELIM);
    }

    return result;
}

int part2_152023(FILE * fp) {
    char seq[BUFSIZ15];
    if(fgets(seq, sizeof(seq), fp) == 0) exit(EXIT_FAILURE);

    node ** boxes = (node **)malloc(sizeof(node *) * BOXSIZE);
    for(int i = 0; i < BOXSIZE; i++) boxes[i] = NULL;

    char * lens = strtok(seq, DELIM);
    while(lens) {
        char token[strlen(lens) + 1];
        memcpy(token, lens, strlen(lens));
        token[strlen(lens)] = '\0';
        if(strchr(token, '-') != NULL) {
            char * chunk = strtok(token, DELIM2);
            char * label = token;
            int boxi = hash(token);
            move(boxes[boxi], label, -1, false);
        } else {
            char * chunk = strtok(token, DELIM2);
            char * label = token;
            int boxi = hash(token);
            chunk = strtok(NULL, DELIM2);
            int fval = atoi(token);
            move(boxes[boxi], label, fval, true);
        }
        lens = strtok(NULL, DELIM);
    }

    for(int i = 0; i < BOXSIZE; i++) {
        if(boxes[i] != NULL) {
            printf("Box %d: ", i);
            printbox(boxes[i]);
            printf("\n");
        }
    }

    return 0;
}

void move(node * box, char * label, int fval, bool add) {
    node * head = box;
    node * last = head;
    while(head) {
        if(strcmp(head->label, label) == 0) {
            if(add) {
                head->fval = fval;
                return;
            } else {
                node * prev = head->prev;
                prev->next = head->next;
                free(head->label);
                free(head);
                return;
            }
        }

        if(head != NULL) last = head;
        head = head->next;
    }

    if(add) {
        node * new = (node *)malloc(sizeof(node));
        if(new == NULL) exit(EXIT_FAILURE);
        new->label = label;
        new->fval = fval;
        new->prev = last;
        new->next = NULL;
    }
}

int hash(char * s) {
    size_t len = strlen(s);
    int curr = 0;
    for(size_t i = 0; i < len; i++) {
        curr += s[i] - '\0';
        curr *= MUL;
        curr %= DIV;
    }

    return curr;
}

void printbox(node * box) {
    node * curr = box;
    while(curr) {
        printf(" [ %s %d ] ", curr->label, curr->fval);
        curr = curr->next;
    }
}
