#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
	double seed;
	double lambda;
} poissonProcess;

poissonProcess init_poissonProcess (double seed, double lambda);

// The interevent times in a Poisson process form an iid sequence of exponential RV with mean 1/λ.
double get_arrival_time(poissonProcess* p);