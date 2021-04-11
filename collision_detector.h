#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "diver.h"
#include "ink.h"

/** checks if objects one and two collide, returns 1 if collision, 0 otherwise
 *  @param object_one_x x coordinate of object one
 *  @param object_one_y y coordinate of object one
 *  @param object_one_radius the radius of object one
 *  @param object_two_x x coordinate of object two
 *  @param object_two_y y coordinate of object two
 *  @param object_two_radius the radius of object two
*/
int collided(int object_one_x, int object_one_y, int object_one_radius, int object_two_x, int object_two_y, int object_two_radius);

/** checks if any of the ink shots hit the diver, returns 1 if collision, 0 otherwise
 * @param diver the diver
 * @param inks the inkList
*/
int any_ink_shot_hits_diver(Diver * diver, inkList * inks);

#endif