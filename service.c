#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// get the delay time given lambda (average time between processing)
double get_service_delay(double lambda){
	if (lambda ==0){
		printf("lambda cannot be 0");
		exit(0);
	}
	double u = (double) rand() / (double)(RAND_MAX); //uniform from [0,1]
	double wait_time = -log(u)/lambda; 
	return wait_time;
}

