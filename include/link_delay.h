#include <stdio.h>
#include <stdlib.h>

/* A link object */
struct link {
  double link_length; // length of link
  double material_factor; // factor of the speed of the light in material
  double calculated_delay; // calculated delay per link
  double data_rate; // date rate of link in Mbps (i.e. bandwidth)
};


static const double SPEED_OF_LIGHT = 299792458; // in meters/seconds


/*
	Function: get_link_delay	
 	---------------------------------------------------------------------------------------
	@discussion
		calculates the link delay per link with the formula:
			(length of Link) / (factor of speed of light * speed of light)
	
	@params
		double link_length: length of each link (assuming each is the same length) in meters
		double material_factor_speedOfLight: factor of speed of light of material

	@returns
		struct link *: link object with characteristics of link and delay


 */
struct link *get_link_delay(double link_length, double material_factor_speedOfLight);
