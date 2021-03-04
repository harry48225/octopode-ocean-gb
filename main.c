#include <gb/gb.h>
#include <gb/font.h>
#include <asm/gbz80/types.h>
#include <stdio.h>

/* import sprites */
#include "sprites/TinyOctopus.c"
#include "sprites/InkShots.c"

/* import tiles */
#include "sprites/BackgroundTiles.c"
#include "backgrounds/StandardBackground.c"

/* import window */
#include "ScoreMap.c"

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 144

#define DEBUG 0

typedef struct {
    int x;
    int y;
    int x_vel;
    int y_vel;
    int direction;
    int spriteNumber;
} ink;

typedef struct {
    ink shots[40];
    int endIndex;
} inkList;

const enum directions{NORTH, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST};

inkList inks;

const UINT8 OCTOPUS_SPRITE = 0;
UINT8 octopusDirection = NORTH;
INT16 octopusPosition[2] = {80,72};

const UINT8 MOVEMENT_SPEED = 2;
const UINT8 DEFAULT_DELAY = 1;
const UINT8 MOVEMENT_DELAY = 16;

const UINT8 SCROLL_SPEED = 1;



void update_octopus_position(int * octopusPosition, UINT8 joypad_state) {
    /* takes the octopus position pointer and updates it */

    if (joypad_state & J_UP) {
        octopusPosition[1] = (octopusPosition[1] - MOVEMENT_SPEED);
    }
    if (joypad_state & J_DOWN) {
        octopusPosition[1] = (octopusPosition[1] + MOVEMENT_SPEED);
    }
    if (joypad_state & J_LEFT) {
        octopusPosition[0] = (octopusPosition[0] - MOVEMENT_SPEED);
    }
    if (joypad_state & J_RIGHT) {
        octopusPosition[0] = (octopusPosition[0] + MOVEMENT_SPEED);
    }

    while (octopusPosition[0] < 0) {
        octopusPosition[0] += DISPLAY_WIDTH;
    }
    while (octopusPosition[0] > DISPLAY_WIDTH + 4) {
        octopusPosition[0] -= DISPLAY_WIDTH;
    }
    while (octopusPosition[1] < 12) {
        octopusPosition[1] += DISPLAY_HEIGHT;
    }
    // 12 was the magic number before adding the text to the bottom
    // this will need to be readded when moving to an interrupt based approach
    // to turning the background and sprites on an off on a per scanline basis
    while (octopusPosition[1] > DISPLAY_HEIGHT) {
        octopusPosition[1] -= DISPLAY_HEIGHT;
    }
}

void update_octopus_sprite(UINT8 joypad_state) {
    
    int octopus_sprite_number = 0;
    
    joypad_state = joypad_state & (J_UP | J_DOWN | J_LEFT | J_RIGHT);

    if (joypad_state == J_UP) {
        octopus_sprite_number = 0;
        octopusDirection = NORTH;
    }
    else if (joypad_state == J_DOWN) {
        octopus_sprite_number = 1;
        octopusDirection = SOUTH;
    }
    else if (joypad_state == J_LEFT) {
        octopus_sprite_number = 2;
        octopusDirection = WEST;
    }
    else if (joypad_state == J_RIGHT) {
        octopus_sprite_number = 3;
        octopusDirection = EAST;
    }
    else if (joypad_state == (J_UP | J_LEFT)) {
        octopus_sprite_number = 4;
        octopusDirection = NORTH_WEST;
    }
    else if (joypad_state == (J_UP | J_RIGHT)) {
        octopus_sprite_number = 5;
        octopusDirection = NORTH_EAST;

    }
    else if (joypad_state == (J_DOWN | J_LEFT)) {
        octopus_sprite_number = 6;
        octopusDirection = SOUTH_WEST;
    }
    else if (joypad_state == (J_DOWN | J_RIGHT)) {
        octopus_sprite_number = 7;
        octopusDirection = SOUTH_EAST;
    }
        


    set_sprite_tile(OCTOPUS_SPRITE, octopus_sprite_number);
}

void scroll_background(UINT8 joypad_state) {

    if (joypad_state == J_UP) {
        scroll_bkg(0, -SCROLL_SPEED);
    }
    else if (joypad_state == J_DOWN) {
        scroll_bkg(0, +SCROLL_SPEED);
    }
    else if (joypad_state == J_LEFT) {
        scroll_bkg(-SCROLL_SPEED, 0);
    }
    else if (joypad_state == J_RIGHT) {
        scroll_bkg(SCROLL_SPEED, 0);
    }
    else if (joypad_state == (J_UP | J_LEFT)) {
        scroll_bkg(-SCROLL_SPEED, -SCROLL_SPEED);
    }
    else if (joypad_state == (J_UP | J_RIGHT)) {
        scroll_bkg(SCROLL_SPEED, -SCROLL_SPEED);
    }
    else if (joypad_state == (J_DOWN | J_LEFT)) {
        scroll_bkg(-SCROLL_SPEED, SCROLL_SPEED);
    }
    else if (joypad_state == (J_DOWN | J_RIGHT)) {
        scroll_bkg(SCROLL_SPEED, SCROLL_SPEED);
    }
}

void shoot_ink(int originPosition[], int direction, int x_velocity, int y_velocity) {
    // Shoots an ink shot originating from the the origin position in the given direction
    ink new_shot;
    new_shot.x = originPosition[0];
    new_shot.y = originPosition[1];

    new_shot.direction = direction;

    new_shot.x_vel = x_velocity;
    new_shot.y_vel = y_velocity;


    /*
        all of this below needs to be changed to be dynamic
    */

    new_shot.spriteNumber = 1; // need to implement some sort of dynamic sprite numbering system

    inks.shots[0] = new_shot;

    inks.endIndex = 1;

    /*
        end dynamic section
    */

    /*
        set the correct sprite
    */
    
    /* 
        increment the end index
    */

}

void draw_inks() {
    for (int i = 0; i < inks.endIndex; i++) {
        // This works because the order the sprites are in VRAM are the same as in the order of the directions in the enum
        // 8 is the offset to avoid the octopus sprites in memory
        ink shot;
        shot = inks.shots[i];

        set_sprite_tile(shot.spriteNumber, 8 + shot.direction); 

        move_sprite(shot.spriteNumber, shot.x, shot.y);
    }
}

void setup() {

    /* font setup */
    font_t min_font;

    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    /* logic setup */

    inks.endIndex = 0;

    /* visual setup */
    
    /* setup sprites */
    set_sprite_data(0, 8, TinyOctopus); /* starting from tile 0 read in 4 tiles from TinyOctopus into VRAM */
    set_sprite_tile(OCTOPUS_SPRITE, 0); /* set sprite 0 to tile 0 from memory */
    move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]); /* move sprite 0 to 88, 78 */


    set_sprite_data(8, 8, InkShots); // Starting from tile 8 (because the first 8 tiles are tiny octopus) read 8 tiles into VRAM

    /* setup background */
    set_bkg_data(37, 11, BackgroundTiles); // load starting at 37 so that they're loading after the fonts
    set_bkg_tiles(0,0, 32, 32, StandardBackground); // set the background data starting from (0,0) doing 32 across, 32 down -- this is the size of the map in StandardBackground -- and also the maximum possible map size

    /* setup window (the top layer) */
    set_win_tiles(0,0, 5, 1, ScoreMap); // start (0,0), 5 wide, 1 high
    move_win(8,136); // put the window at the bottom because otherwise it would cover the background as it's not transparent 

    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void main() {

    UINT8 current_delay = 100;
    
    setup();

    /* game loop */
    while (1) {

        current_delay = MOVEMENT_DELAY;


        /* handle input */
        UINT8 move = 1;

        UINT8 joypad_state = joypad();

        if (joypad_state & (J_LEFT | J_RIGHT | J_DOWN | J_UP)) {
            update_octopus_position(octopusPosition, joypad_state);
            update_octopus_sprite(joypad_state);
            scroll_background(joypad_state);
        }
        else {
            move = 0;
            current_delay = DEFAULT_DELAY;      
        }

        if (joypad_state & (J_A)) {
            shoot_ink(octopusPosition, octopusDirection, 1, 1);
        }

        move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]);
        draw_inks();
        if (DEBUG) {
            printf("\r\n x: %d, y: %d", octopusPosition[0], octopusPosition[1]);
        }
        delay(current_delay);
    }
}