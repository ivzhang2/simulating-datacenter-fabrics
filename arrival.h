// R1: add header guards

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// R2: Avoid typedeffing structs to remain consistent with the C standard
// library.
typedef struct {
  double seed;
  double lambda;
  // R4: rename to poisson_process_t
} poissonProcess;

// R3: Rename to init_poisson_process to be consistent with the rest of our API.
poissonProcess init_poissonProcess(double seed, double lambda);

// The interevent times in a Poisson process form an iid sequence of exponential
// RV with mean 1/λ.
double get_arrival_time(poissonProcess *p);
