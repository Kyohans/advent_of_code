#ifndef _AOC_H
#define _AOC_H

#define SESSION_KEY "./.aocrc"
#define BUFFER_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get_session(void);
FILE * fetch_input(const char *, const char *);

#endif
