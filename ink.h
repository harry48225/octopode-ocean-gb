#include "constants.h"
#pragma once

typedef struct {
    int x;
    int y;
    int x_vel;
    int y_vel;
    int direction;
    int spriteNumber;
    int enabled;
} ink;

typedef struct {
    ink shots[INK_SHOT_AMOUNT]; // can have a maximum of INK_SHOT_AMOUNT shots at a time
} inkList;

/** destroys a given ink shot, note this modifies the in place and it should be overwritten in the array to take effect
 * @param shot the shot to destory
*/
void destroy_ink(ink * shot);

/** plays the ink shot sound
*/
void play_ink_shot_sound();

/** makes the octopus shoot an ink shot
 * @param originPosition the position the shot should originate from {x, y}
 * @param direction the direction of the shot sprite in NORTH, SOUTH, ....
 * @param x_velocity the x velocity of the shot
 * @param y_velocity the y velocity of the shot
 * @param inks the inkList to contain the ink
*/
void shoot_ink(int originPosition[], int direction, int x_velocity, int y_velocity, inkList * inks);

/** initalises the given inkList
 * @param inks the inkList to initalise
*/
void initalise_ink_list(inkList *inks);

/** draws the inks in the given ink list
 * @param inks the inkList to draw the inks from
*/
void draw_inks(inkList *inks);

/** moves the inks in the given ink list
 * @param inks the inkList to move the inks from
*/
void move_inks(inkList *inks);