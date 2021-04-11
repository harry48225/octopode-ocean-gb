#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 144

#define DEBUG 0

const enum directions{NORTH, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST};

#ifdef MAIN_SOURCE
const int OCTOPUS_SPRITE = 0;

const int MOVEMENT_SPEED = 1;
const int DEFAULT_DELAY = 16;
const int MOVEMENT_DELAY = 16;
const int SHOT_SPEED_MULTIPLIER = 2;
const int SCROLL_SPEED = 1;
#else
extern int OCTOPUS_SPRITE;
extern int MOVEMENT_SPEED;
extern int DEFAULT_DELAY;
extern int MOVEMENT_DELAY;
extern int SHOT_SPEED_MULTIPLIER;
extern int SCROLL_SPEED;
#endif

#endif