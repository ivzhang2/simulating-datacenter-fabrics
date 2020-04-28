#include <stdio.h>
#include <stdlib.h>

#include "link_delay.h"

struct link *get_link_delay(double link_length, double material_factor_speedOfLight){
	extern const double SPEED_OF_LIGHT; // speed of light in meters/seconds
	double speed_in_material = SPEED_OF_LIGHT * material_factor_speedOfLight;
	double link_delay = (link_length / speed_in_material) * 1000;

	struct link *new_link = (struct link*) malloc(sizeof(struct link));
	new_link->link_length = link_length;
	new_link->material_factor = material_factor_speedOfLight;
	new_link->calculated_delay = link_delay;

	return new_link;
}
