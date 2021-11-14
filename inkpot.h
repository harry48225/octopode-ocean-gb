#include "constants.h"
#pragma once

typedef struct inkPot {
  int x;
  int y;
  int enabled;
  int spriteNumber;
} inkPot;

typedef struct inkPotList {
  inkPot pots[INK_POT_AMOUNT];
} inkPotList;

/** destroys a given ink pot, note this modifies the in place and it should be overwritten in the array to take effect
 * @param shot the pot to destory
*/
void destroy_ink_pot(inkPot * pot);

/** plays the collect inkPot sound
*/
void play_collect_ink_pot_sound();

/**
 * @brief spawns an ink pot at the given location
 * 
 * @param x 
 * @param y 
 * @param pots the inkPot list to use to store the pot
*/
void spawn_ink_pot(int x, int y, inkPotList * pots);

/** initalises the given ink pot list
 * @param pots
*/
void initalise_ink_pot_list(inkPotList * pots);

/**
 * @brief draws the ink pots in the given list
 * 
 * @param pots 
 */
void draw_ink_pots(inkPotList * pots);