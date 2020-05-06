#include "link.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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
                         double material_factor_speedOfLight) {
  double speed_in_material = SPEED_OF_LIGHT * material_factor_speedOfLight;
  double link_delay = (link_length / speed_in_material) * 1000000;

  struct link_t *new_link = malloc(sizeof(struct link_t));
  assert(new_link != NULL);

  new_link->link_length = link_length;
  new_link->material_factor = material_factor_speedOfLight;
  new_link->calculated_delay = link_delay;

  return new_link;
}

/**
 * free the memory utilized by the link object
 */
void link_free(struct link_t *pl) {
  assert(pl != NULL);
  free(pl);
}
