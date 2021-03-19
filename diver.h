#ifndef DIVER_H
#define DIVER_H

#include "metasprite.h"

enum diver_states {
    DIVER_ROAMING,
    DIVER_COOLDOWN
};

enum diver_directions {
    DIVER_NORTH, DIVER_SOUTH, DIVER_WEST, DIVER_EAST,
    DIVER_NORTH_WEST, DIVER_NORTH_EAST, DIVER_SOUTH_WEST, DIVER_SOUTH_EAST
};

typedef struct {

    MetaSprite sprite;
    int x;
    int y;
    int direction_number;
    int direction_counter;
    int spriteNumbers[4];
    int enabled;
    enum diver_states state;

} Diver;

/** moves a diver sprite to x and y
 
 *  @param diver pointer to diver to move
 *  @param x x-coordinate to move to
 *  @param y y-coordinate to move to

*/
void move_diver(Diver * diver, int x, int y);

/** sets the drives sprites
*/
void set_driver_sprites(Diver * driver, int sprite_numbers[]);

/** draws a driver
 * 
*/
void draw_diver(Diver * diver);

/** runs a frame's simulation for a single diver
 * @param diver the diver to move
*/
void simulate_diver(Diver * diver);

/**
 * sets the drivers sprite to be the the one for the direction it's moving in
 * @param diver the diver to change the sprite of
*/
void update_diver_sprite_from_direction(Diver * diver);

#endif