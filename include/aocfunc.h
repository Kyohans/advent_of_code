#ifndef _AOC_FUNC_H
#define _AOC_FUNC_H

#include <year2021.h>

#define STARTING_YEAR 2021
#define NUM_YEARS 3

// 2021: 1, 2022: 0, 2023: 0
const size_t NUM_DAYS_BY_YEAR[NUM_YEARS] = {1, 0, 0};

static void (*year2021[])(const char *) = {
  day01_2021
};

static void (**functions[])(const char *) = {
  year2021
};

#endif
