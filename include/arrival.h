// R1: add header guards

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// The interevent times in a Poisson process form an iid sequence of exponential
// RV with mean 1/λ.
double get_arrival_time(double lambda);
