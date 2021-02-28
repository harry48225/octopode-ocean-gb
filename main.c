#include <gb/gb.h>
#include <stdio.h>

/* import sprites */
#include "sprites/TinyOctopus.c"

/* import tiles */
#include "sprites/BackgroundTiles.c"
#include "backgrounds/StandardBackground.c"

#define DISPLAY_WIDTH 160
#define DISPLAY_HEIGHT 144

#define DEBUG 0

const enum directions{NORTH, EAST, SOUTH, WEST};

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
    while (octopusPosition[1] > DISPLAY_HEIGHT + 12) {
        octopusPosition[1] -= DISPLAY_HEIGHT;
    }
}

void update_octopus_sprite(UINT8 joypad_state) {
    
    int octopus_sprite_number = 0;
    
    if (joypad_state == J_UP) {
        octopus_sprite_number = 0;
    }
    else if (joypad_state == J_DOWN) {
        octopus_sprite_number = 1;
    }
    else if (joypad_state == J_LEFT) {
        octopus_sprite_number = 2;
    }
    else if (joypad_state == J_RIGHT) {
        octopus_sprite_number = 3;
    }
    else if (joypad_state == (J_UP | J_LEFT)) {
        octopus_sprite_number = 4;
    }
    else if (joypad_state == (J_UP | J_RIGHT)) {
        octopus_sprite_number = 5;
    }
    else if (joypad_state == (J_DOWN | J_LEFT)) {
        octopus_sprite_number = 6;
    }
    else if (joypad_state == (J_DOWN | J_RIGHT)) {
        octopus_sprite_number = 7;
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

void main() {

    UINT8 currentSpriteIndex = 0;
    UINT8 current_delay = 100;
    
    /* setup */
    
    set_sprite_data(0, 8, TinyOctopus); /* starting from tile 0 read in 4 tiles from TinyOctopus into VRAM */
    set_sprite_tile(OCTOPUS_SPRITE, 0); /* set sprite 0 to tile 0 from memory */
    move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]); /* move sprite 0 to 88, 78 */

    /* setup background */
    set_bkg_data(0, 11, BackgroundTiles);
    set_bkg_tiles(0,0, 80, 36, StandardBackground); // set the background data starting from (0,0) doing 80 across, 36 down -- this is the size of the map in StandardBackground

    
    
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

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

        /*
        //if a movement button was pressed 
        if ( move == 1 ) {
            switch(octopusDirection) {
                case NORTH:
                    octopusPosition[1] = (octopusPosition[1] - MOVEMENT_SPEED);
                    scroll_bkg(0, -SCROLL_SPEED);
                    break;
                case EAST:
                    octopusPosition[0] = (octopusPosition[0] + MOVEMENT_SPEED);
                    scroll_bkg(SCROLL_SPEED, 0);
                    break;
                case SOUTH:
                    octopusPosition[1] = (octopusPosition[1] + MOVEMENT_SPEED);
                    scroll_bkg(0, SCROLL_SPEED);
                    break;
                case WEST:
                    octopusPosition[0] = (octopusPosition[0] - MOVEMENT_SPEED);
                    scroll_bkg(-SCROLL_SPEED, 0);
                    break;
            }
            

            
        }
        */;

        move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]);

        if (DEBUG) {
            printf("\r\n x: %d, y: %d", octopusPosition[0], octopusPosition[1]);
        }
        delay(current_delay);
    }
}