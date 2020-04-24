#include <stdio.h>

#include "link_delay.h"

double get_link_delay(double link_length, double material_factor_speedOfLight){
	extern const double SPEED_OF_LIGHT; // speed of light in meters/seconds
	double speed_in_material = SPEED_OF_LIGHT * material_factor_speedOfLight;
	double link_delay = link_length / speed_in_material;
	return link_delay * 1000;
}

// int main(){
// 	printf("%f\n", get_link_delay(10, 0.9));
// }