#ifndef _AOC_FUNC_H
#define _AOC_FUNC_H

#include <year2021.h>

#define STARTING_YEAR 2021

static void (*year2021[])(const char *) = {
  day01_2021
};

static void (**functions[])(const char *) = {
  year2021
};

#endif
