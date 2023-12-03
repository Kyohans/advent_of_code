#ifndef _AOC_FUNC_H
#define _AOC_FUNC_H

#include <years/year2023.h>
#include <stdlib.h>

#define STARTING_YEAR 2023
#define NUM_YEARS 1

// 2023: 1
const size_t NUM_DAYS_BY_YEAR[NUM_YEARS] = {2};

static void (**functions[])(const char *) = {
  year2023_solutions
};

#endif
