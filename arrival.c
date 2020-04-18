
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// R5: the local header should always be the first one included to avoid hiding
// dependencies
#include "arrival.h"

// R6: let's ensure srand gets changed at a higher level e.g at one place at the
// start of the simulation. Don't worry about it in individual functions. (You
// can remove the parameter "seed" and line 2 here, we really just need lambda)
poissonProcess init_poissonProcess(double seed, double lambda) {
  poissonProcess p = {.seed = seed, .lambda = lambda};
  srand(p.seed);
  return p;
}

// The interevent times in a Poisson process form an iid sequence of exponential
// RV with mean 1/λ.
double get_arrival_time(poissonProcess *p) {
  double u = (double)rand() / (double)(RAND_MAX); // uniform from [0,1]
  double mean = 1 / p->lambda;          // mean of the exponential dist
  double arrival_time = -log(u) * mean; // next arrival
  return arrival_time;
}
