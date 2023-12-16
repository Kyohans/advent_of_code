#ifndef _AOC_FUNC_H
#define _AOC_FUNC_H

#include <stdlib.h>

#include <years/year2023.h>

#define STARTING_YEAR 2023
#define NUM_YEARS 1

static void (**functions[])(const char *) = {
  year2023_solutions
};

#endif
