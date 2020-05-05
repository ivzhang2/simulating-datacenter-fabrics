
#include "arrival.h"
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

/**
 * The interevent times in a Poisson process form an iid sequence of exponential
 * RV with mean 1/λ.
 */
double get_arrival_time(double lambda, unsigned int *pseed) {
  double u = (double)rand() / (double)(RAND_MAX); // uniform from [0,1]
  double mean = 1 / lambda;             // mean of the exponential dist
  double arrival_time = -log(u) * mean; // next arrival
  return arrival_time;
}
