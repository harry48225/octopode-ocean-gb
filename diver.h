#ifndef DIVER_H
#define DIVER_H

#include "constants.h"
#include "metasprite.h"

enum diver_states {
    DIVER_ROAMING,
    DIVER_COOLDOWN,
    DIVER_CHASING
};

enum diver_directions {
    DIVER_NORTH, DIVER_SOUTH, DIVER_WEST, DIVER_EAST,
    DIVER_NORTH_WEST, DIVER_NORTH_EAST, DIVER_SOUTH_WEST, DIVER_SOUTH_EAST
};

typedef struct {
    MetaSprite sprite;
    int x;
    int y;
    enum diver_directions direction;
    int direction_number;
    int direction_counter;
    int enabled;
    enum diver_states state;
} Diver;

typedef struct {
    Diver divers[DIVER_AMOUNT];
} DiverList;

/** spawns a Diver at the given location
 * @param x
 * @param y
 * @param divers the diver list to spawn the diver in
*/
void spawn_diver_at(int x, int y, DiverList *divers);

/** initalises the given DiverList with disabled divers
 * 
*/
void initalise_diver_list(DiverList * divers);


/** moves a diver sprite to x and y
 
 *  @param diver pointer to diver to move
 *  @param x x-coordinate to move to
 *  @param y y-coordinate to move to

*/
void move_diver(Diver * diver, int x, int y);

/** draws a driver */
void draw_diver(Diver * diver);

/** draws all divers in a list */
void draw_divers(DiverList * divers);

/** runs a frame's simulation for a single diver
 * @param diver the diver to move
 * @param octopus_x the x-coordinate of the octopus
 * @param octopus_y the y-coordinate of the octopus
*/
void simulate_diver(Diver * diver, int octopus_x, int octopus_y);

/**
 * returns the drivers sprite for the direction it's moving in
 * @param buffer the array to fill with the sprite locations
 * @param diver the diver to change the sprite of
*/
void get_diver_sprite_from_direction(int * buffer, Diver * diver);

/**
 * takes a vector and returns the corresponding diver_direction
*/
enum diver_directions direction_from_vector(int x, int y);

/**
 * adds x and y to the coordinates of the diver
 * 
*/
void accumulate_diver_coordinates(Diver * diver, int x, int y);
#endif