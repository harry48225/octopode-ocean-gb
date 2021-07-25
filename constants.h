#ifndef CONSTANTS_H
#define CONSTANTS_H

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 144

#define DESPAWN_X 200
#define DESPAWN_Y 200

#define DEBUG 0

// const int OCTOPUS_SPRITE_NUMBER = 0;

#define OCTOPUS_SPRITE_NUMBER 0
#define MOVEMENT_SPEED 1
#define DEFAULT_DELAY 16
#define MOVEMENT_DELAY 16
#define SHOT_SPEED_MULTIPLIER 2
#define SCROLL_SPEED 1
#define INK_RADIUS 8
#define INK_SHOT_AMOUNT 4
#define DIVER_AMOUNT 4
#define DIVER_ACTIVATION_RANGE 80
#define DIVER_RADIUS 16
#define DIVER_SCREEN_WIDTH 248
#define DIVER_SCREEN_HEIGHT 248
#define DIVER_ROAM_SPEED 1
#define DIVER_CHASE_SPEED 2
#define DIVER_STARTING_HEALTH 2

#define DIVER_SPAWN_INTERVAL 60

const enum directions{NORTH, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST};

// #ifdef MAIN_SOURCE
// const int OCTOPUS_SPRITE_NUMBER = 0;

// const int MOVEMENT_SPEED = 1;
// const int DEFAULT_DELAY = 16;
// const int MOVEMENT_DELAY = 16;
// const int SHOT_SPEED_MULTIPLIER = 2;
// const int SCROLL_SPEED = 1;

// const int INK_RADIUS = 8;
// const int INK_SHOT_AMOUNT = 4;
// const int DESPAWN_X = 200;
// const int DESPAWN_Y = 200;

// const int DIVER_AMOUNT = 4;
// const int DIVER_ACTIVATION_RANGE = 80;
// const int DIVER_RADIUS = 16;
// const int DIVER_SCREEN_WIDTH = 248;
// const int DIVER_SCREEN_HEIGHT = 248;
// const int DIVER_ROAM_SPEED = 1;
// const int DIVER_CHASE_SPEED = 2;

// #else
// extern const int OCTOPUS_SPRITE_NUMBER;
// extern const int MOVEMENT_SPEED;
// extern const int DEFAULT_DELAY;
// extern const int MOVEMENT_DELAY;
// extern const int SHOT_SPEED_MULTIPLIER;
// extern const int SCROLL_SPEED;

// extern const int INK_RADIUS;
// extern const int INK_SHOT_AMOUNT;
// extern const int DESPAWN_X;
// extern const int DESPAWN_Y;

// extern const int DIVER_AMOUNT;
// extern const int DIVER_ACTIVATION_RANGE;
// extern const int DIVER_RADIUS;
// extern const int DIVER_SCREEN_WIDTH;
// extern const int DIVER_SCREEN_HEIGHT;
// extern const int DIVER_ROAM_SPEED;
// extern const int DIVER_CHASE_SPEED;
// #endif

#endif