#ifndef LINK_H
#define LINK_H

#include <stdint.h>

/* A link object */
struct link_t {
  double link_length;        // length of link
  double material_factor;    // factor of the speed of the light in material
  uint64_t calculated_delay; // calculated delay per link
  double data_rate;          // date rate of link in Mbps (i.e. bandwidth)
};

#define SPEED_OF_LIGHT 299792458 // in meters/seconds

/*
Function: get_link_delay

@discussion calculates the link delay per link with the formula: (length of
Link) / (factor of speed of light * speed of light)

@params double link_length: length of each link (assuming each is the
same length) in meters double material_factor_speedOfLight: factor of speed of
light of material

@returns struct link *: link object with characteristics of link and delay
*/
struct link_t *link_init(double link_length,
                         double material_factor_speedOfLight);

void link_free(struct link_t *pl);

#endif /* LINK_H */
