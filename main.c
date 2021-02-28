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

void main() {

    UINT8 currentSpriteIndex = 0;
    UINT8 current_delay = 100;
    
    /* setup */
    
    set_sprite_data(0, 4, TinyOctopus); /* starting from tile 0 read in 4 tiles from TinyOctopus into VRAM */
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

        switch(joypad()) {
            case J_LEFT:
                octopusDirection = WEST;
                break;
            case J_RIGHT:
                octopusDirection = EAST;
                break;
            case J_UP:
                octopusDirection = NORTH;
                break;
            case J_DOWN:
                octopusDirection = SOUTH;
                break;
            default:
                move = 0;
                current_delay = DEFAULT_DELAY;        
        }

        /* if a movement button was pressed */
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

        /* select the correct octopus sprite */
        set_sprite_tile(OCTOPUS_SPRITE, octopusDirection);

        move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]);

        if (DEBUG) {
            printf("\r\n x: %d, y: %d", octopusPosition[0], octopusPosition[1]);
        }
        delay(current_delay);
    }
}