#ifndef LINK_H
#define LINK_H

#include <stdint.h>

/**
 * A link object, with data about the length of the link,
 * the speed that can runs through the link (as a factor of the speed of light
 * in the material) the calculated delay per link, and the data rate (bandwidth)
 * of the link in Mbps
 */
struct link_t {
  double link_length;      // length of link
  double material_factor;  // factor of the speed of the light in material
  double calculated_delay; // calculated delay per link
  double data_rate;        // data rate of link in Mbps (i.e. bandwidth)
};

#define SPEED_OF_LIGHT 299792458 // in meters/seconds

/**
*calculates the link delay per link with the formula: (length of link) /
* (factor of speed of light * speed of light)

* params:
*
* - link_length: length of each link (assuming each is the same length) in
meters
* - double material_factor_speedOfLight: factor of speed of light of material

* returns struct link : link object with characteristics of link and delay
*/
struct link_t *link_init(double link_length,
                         double material_factor_speedOfLight);

/**
 * free the memory utilized by the link object
 */
void link_free(struct link_t *pl);

#endif /* LINK_H */
