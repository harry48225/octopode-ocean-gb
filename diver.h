#ifndef DIVER_H
#define DIVER_H

#include "metasprite.h"

typedef struct {

    MetaSprite sprite;
    int x;
    int y;
    int direction;
    int spriteNumbers[4];
    int enabled;

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

#endif