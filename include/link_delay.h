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
		double link_delay: delay per link (in milliseconds) based on given inputs


 */
double get_link_delay(double link_length, double material_factor_speedOfLight);