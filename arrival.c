
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

#include "arrival.h"

poissonProcess init_poissonProcess (double seed, double lambda){
	poissonProcess p={.seed = seed, .lambda=lambda};
	return p;
}

// The interevent times in a Poisson process form an iid sequence of exponential RV with mean 1/λ.
double get_arrival_time(poissonProcess* p){
	srand(p->seed);
	double u = (double) rand() / (double)(RAND_MAX); //uniform from [0,1]
	double mean = 1 / p->lambda; //mean of the exponential dist
	double arrival_time = -log(u)*mean; //next arrival
	return arrival_time;
}


