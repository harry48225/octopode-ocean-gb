#define MAIN_SOURCE
#include <gb/gb.h>
#include <gb/font.h>
#include <asm/gbz80/types.h>
#include <stdio.h>

#include "metasprite.h"
#include "collision_detector.h"

#include "diver.h"
#include "ink.h"
#include "constants.h"

/* import sprites */
#include "sprites/TinyOctopus.c"
#include "sprites/InkShots.c"
#include "sprites/DiverSprites.c"

/* import tiles */
#include "sprites/BackgroundTiles.c"
#include "backgrounds/StandardBackground.c"

/* import window */
#include "ScoreMap.c"

inkList inks;

UINT8 octopusDirection = NORTH;
INT16 octopusPosition[2] = {80,72};

DiverList divers;
//Diver diver;

void move_divers_relatively(int x_vel, int y_vel) {
    for (int i = 0; i < DIVER_AMOUNT; i++) {
        Diver diver;
        diver = divers.divers[i];
        if (diver.enabled) {
            accumulate_diver_coordinates(&diver, x_vel, y_vel);
            divers.divers[i] = diver;
        }
    }
}

void simulate_divers() {
    for (int i = 0; i < DIVER_AMOUNT; i++) {
        Diver diver;
        diver = divers.divers[i];

        if (diver.enabled) {
            simulate_diver(&diver, octopusPosition[0], octopusPosition[1]);

            if (any_ink_shot_hits_diver(&diver, &inks)) {
                printf("ink hit");
            }

            divers.divers[i] = diver;
        }
    }
}

void update_octopus_position(int * octopusPosition, UINT8 joypad_state) {
    /* takes the octopus position pointer and updates it */
    if (joypad_state & J_UP) {
        octopusPosition[1] = (octopusPosition[1] - MOVEMENT_SPEED);
        move_divers_relatively(0, MOVEMENT_SPEED);
    }
    if (joypad_state & J_DOWN) {
        octopusPosition[1] = (octopusPosition[1] + MOVEMENT_SPEED);
        move_divers_relatively(0, -MOVEMENT_SPEED);
    }
    if (joypad_state & J_LEFT) {
        octopusPosition[0] = (octopusPosition[0] - MOVEMENT_SPEED);
        move_divers_relatively(MOVEMENT_SPEED, 0);
    }
    if (joypad_state & J_RIGHT) {
        octopusPosition[0] = (octopusPosition[0] + MOVEMENT_SPEED);
        move_divers_relatively(-MOVEMENT_SPEED, 0);
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
    } else if (joypad_state == J_DOWN) {
        octopus_sprite_number = 1;
        octopusDirection = SOUTH;
    } else if (joypad_state == J_LEFT) {
        octopus_sprite_number = 2;
        octopusDirection = WEST;
    } else if (joypad_state == J_RIGHT) {
        octopus_sprite_number = 3;
        octopusDirection = EAST;
    } else if (joypad_state == (J_UP | J_LEFT)) {
        octopus_sprite_number = 4;
        octopusDirection = NORTH_WEST;
    } else if (joypad_state == (J_UP | J_RIGHT)) {
        octopus_sprite_number = 5;
        octopusDirection = NORTH_EAST;

    } else if (joypad_state == (J_DOWN | J_LEFT)) {
        octopus_sprite_number = 6;
        octopusDirection = SOUTH_WEST;
    } else if (joypad_state == (J_DOWN | J_RIGHT)) {
        octopus_sprite_number = 7;
        octopusDirection = SOUTH_EAST;
    }
        
    set_sprite_tile(OCTOPUS_SPRITE_NUMBER, octopus_sprite_number);
}

void scroll_background(UINT8 joypad_state) {
    if (joypad_state == J_UP) {
        scroll_bkg(0, -SCROLL_SPEED);
    } else if (joypad_state == J_DOWN) {
        scroll_bkg(0, +SCROLL_SPEED);
    } else if (joypad_state == J_LEFT) {
        scroll_bkg(-SCROLL_SPEED, 0);
    } else if (joypad_state == J_RIGHT) {
        scroll_bkg(SCROLL_SPEED, 0);
    } else if (joypad_state == (J_UP | J_LEFT)) {
        scroll_bkg(-SCROLL_SPEED, -SCROLL_SPEED);
    } else if (joypad_state == (J_UP | J_RIGHT)) {
        scroll_bkg(SCROLL_SPEED, -SCROLL_SPEED);
    } else if (joypad_state == (J_DOWN | J_LEFT)) {
        scroll_bkg(-SCROLL_SPEED, SCROLL_SPEED);
    } else if (joypad_state == (J_DOWN | J_RIGHT)) {
        scroll_bkg(SCROLL_SPEED, SCROLL_SPEED);
    }
}

int direction_to_x_component(int direction) {
    if ((direction == EAST)  || (direction == NORTH_EAST) || (direction == SOUTH_EAST)) {
        return 1;
    } else if ((direction == WEST)  || (direction == NORTH_WEST) || (direction == SOUTH_WEST)) {
        return -1;
    }

    return 0;
}

int direction_to_y_component(int direction) {
    if ((direction == NORTH)  || (direction == NORTH_EAST) || (direction == NORTH_WEST)) {
        return -1;
    } else if ((direction == SOUTH)  || (direction == SOUTH_EAST) || (direction == SOUTH_WEST)) {
        return 1;
    }

    return 0;
}

void setup_sound() {
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}

void setup() {
    /* font setup */
    font_t min_font;

    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    /* logic setup */

    initalise_ink_list(&inks);
    
    /* visual setup */
    /* setup sprites */
    set_sprite_data(0, 8, TinyOctopus); /* starting from tile 0 read in 4 tiles from TinyOctopus into VRAM */
    set_sprite_tile(OCTOPUS_SPRITE_NUMBER, 0); /* set sprite 0 to tile 0 from memory */
    move_sprite(OCTOPUS_SPRITE_NUMBER, octopusPosition[0], octopusPosition[1]); /* move sprite 0 to 88, 78 */

    // ink shot tiles
    set_sprite_data(8, 8, InkShots); // Starting from tile 8 (because the first 8 tiles are tiny octopus) read 8 tiles into VRAM

    // diver tiles
    set_sprite_data(16, 32, DiverSprites); // Load in the diver sprites
    
    /*
        maybe some sort of function to automatically do this?
    */

    initalise_diver_list(&divers);
    spawn_diver_at(50, 50, &divers);

    /* setup background */
    set_bkg_data(37, 11, BackgroundTiles); // load starting at 37 so that they're loading after the fonts
    set_bkg_tiles(0,0, 32, 32, StandardBackground); // set the background data starting from (0,0) doing 32 across, 32 down -- this is the size of the map in StandardBackground -- and also the maximum possible map size

    /* setup window (the top layer) */
    set_win_tiles(0,0, 5, 1, ScoreMap); // start (0,0), 5 wide, 1 high
    move_win(8,136); // put the window at the bottom because otherwise it would cover the background as it's not transparent 

    setup_sound();

    SHOW_BKG;
    SHOW_WIN;
    SHOW_SPRITES;
    DISPLAY_ON;
}

void main() {
    UINT8 current_delay = DEFAULT_DELAY;

    int ink_latch = FALSE;
    setup();

    /* game loop */
    while (1) {
        /* handle input */
        UINT8 move = 1;

        UINT8 joypad_state = joypad();

        if (joypad_state & (J_LEFT | J_RIGHT | J_DOWN | J_UP)) {
            update_octopus_position(octopusPosition, joypad_state);
            update_octopus_sprite(joypad_state);
            scroll_background(joypad_state & (J_LEFT | J_RIGHT | J_DOWN | J_UP));
        } else {
            move = 0;
            //current_delay = DEFAULT_DELAY;      
        }

        if (joypad_state & (J_A)) {
            if (!ink_latch) {
                shoot_ink(octopusPosition, octopusDirection, SHOT_SPEED_MULTIPLIER*MOVEMENT_SPEED*direction_to_x_component(octopusDirection), SHOT_SPEED_MULTIPLIER*MOVEMENT_SPEED*direction_to_y_component(octopusDirection), &inks);
                ink_latch = TRUE;
            }
        } else {
            ink_latch = FALSE;
        }

        move_sprite(OCTOPUS_SPRITE_NUMBER, octopusPosition[0], octopusPosition[1]);
        move_inks(&inks);
        draw_inks(&inks);
        
        simulate_divers();
        draw_divers(&divers);

        if (DEBUG) {
            printf("\r\n x: %d, y: %d", octopusPosition[0], octopusPosition[1]);
        }
        delay(current_delay);
    }
}