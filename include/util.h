#ifndef _UTIL_H
#define _UTIL_H

#define SESSION_KEY "../.aocrc"
#define BUFFER_SIZE 256
#define TESTING 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get_session(void);
int get_int(void);
int fetch_input(const char *, const char *);
int cleanup_file(const char *);

#endif
