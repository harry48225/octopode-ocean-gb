#ifndef DIVER_H
#define DIVER_H

#include "metasprite.h"

const enum diver_states {
    DIVER_ROAMING,
    DIVER_COOLDOWN
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

#endif