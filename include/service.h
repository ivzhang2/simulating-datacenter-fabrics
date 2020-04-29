#ifndef SERVICE_H
#define SERVICE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// get the delay time given lambda (average time between processing)
double get_service_delay(double lambda);

#endif /* SERVICE_H */
