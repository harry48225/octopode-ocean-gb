#include <gb/gb.h>
#include <gb/font.h>
#include <asm/gbz80/types.h>
#include <stdio.h>

#include "metasprite.h"

#include "diver.h"


/* import sprites */
#include "sprites/TinyOctopus.c"
#include "sprites/InkShots.c"
#include "sprites/DiverSprites.c"

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
    int enabled;
} ink;

#define SHOT_AMOUNT 4

typedef struct {
    ink shots[SHOT_AMOUNT]; // can have a maximum of SHOT_AMOUNT shots at a time
} inkList;



const enum directions{NORTH, SOUTH, WEST, EAST, NORTH_WEST, NORTH_EAST, SOUTH_WEST, SOUTH_EAST};

inkList inks;

const UINT8 OCTOPUS_SPRITE = 0;
UINT8 octopusDirection = NORTH;
INT16 octopusPosition[2] = {80,72};

const UINT8 MOVEMENT_SPEED = 1;
const UINT8 DEFAULT_DELAY = 16;
const UINT8 MOVEMENT_DELAY = 16;
const UINT8 SHOT_SPEED_MULTIPLIER = 2;

const UINT8 SCROLL_SPEED = 1;

Diver diver;


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


    for (int i = 0; i < SHOT_AMOUNT; i++) {

        ink shot;
        shot = inks.shots[i];

        if (!shot.enabled) {
            shot.x = originPosition[0];
            shot.y = originPosition[1];
            shot.direction = direction;
            shot.x_vel = x_velocity;
            shot.y_vel = y_velocity;
            shot.enabled = TRUE;
            shot.spriteNumber = OCTOPUS_SPRITE + 1 + i; // need to implement some sort of dynamic sprite numbering system

            inks.shots[i] = shot;

            play_ink_shot_sound();
            break;
        }
    }

    
}

void draw_inks() {
    for (int i = 0; i < SHOT_AMOUNT; i++) {
        // This works because the order the sprites are in VRAM are the same as in the order of the directions in the enum
        // 8 is the offset to avoid the octopus sprites in memory
        ink shot;
        shot = inks.shots[i];

        if (shot.enabled) {
            set_sprite_tile(shot.spriteNumber, 8 + shot.direction); 

            move_sprite(shot.spriteNumber, shot.x, shot.y);
        }
    }
}

void move_inks() {
    for (int i = 0; i < SHOT_AMOUNT; i++) {
        ink shot;
        shot = inks.shots[i];

        if (shot.enabled) {
            shot.x += shot.x_vel;
            shot.y += shot.y_vel;

            // Despawn the shot if it's off screen, with some tolerance to ensure that they're fully off

            if ((shot.x > DISPLAY_WIDTH + 24) || (shot.x < -24) || (shot.y > DISPLAY_HEIGHT + 24) || (shot.y < -24)) {
                shot.enabled = FALSE;
            }

            inks.shots[i] = shot;
        }
        
    }
}

int direction_to_x_component(int direction) {


    if ((direction == EAST)  || (direction == NORTH_EAST) || (direction == SOUTH_EAST)) {
        return 1;
    }
    else if ((direction == WEST)  || (direction == NORTH_WEST) || (direction == SOUTH_WEST)) {
        return -1;
    }

    return 0;

}

int direction_to_y_component(int direction) {


    if ((direction == NORTH)  || (direction == NORTH_EAST) || (direction == NORTH_WEST)) {
        return -1;
    }
    else if ((direction == SOUTH)  || (direction == SOUTH_EAST) || (direction == SOUTH_WEST)) {
        return 1;
    }

    return 0;

}


void initalise_ink_list() {

    for (int i = 0; i < SHOT_AMOUNT; i++) {
        ink new_ink;

        new_ink.enabled = 0;

        inks.shots[i] = new_ink;
    }

}

void setup() {

    /* font setup */
    font_t min_font;

    font_init();
    min_font = font_load(font_min);
    font_set(min_font);

    /* logic setup */

    initalise_ink_list();
    

    /* visual setup */
    
    /* setup sprites */
    set_sprite_data(0, 8, TinyOctopus); /* starting from tile 0 read in 4 tiles from TinyOctopus into VRAM */
    set_sprite_tile(OCTOPUS_SPRITE, 0); /* set sprite 0 to tile 0 from memory */
    move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]); /* move sprite 0 to 88, 78 */

    // ink shot tiles
    set_sprite_data(8, 8, InkShots); // Starting from tile 8 (because the first 8 tiles are tiny octopus) read 8 tiles into VRAM

    // diver tiles
    set_sprite_data(16, 32, DiverSprites); // Load in the diver sprites
    diver.x = 50;
    diver.y = 50;
    diver.direction = 1;
    diver.spriteNumbers[0] = 16;
    diver.spriteNumbers[1] = 17;
    diver.spriteNumbers[2] = 18;
    diver.spriteNumbers[3] = 19;

    diver.sprite.sprite_ids[0] = OCTOPUS_SPRITE + SHOT_AMOUNT + 1;
    diver.sprite.sprite_ids[1] = OCTOPUS_SPRITE + SHOT_AMOUNT + 2;
    diver.sprite.sprite_ids[2] = OCTOPUS_SPRITE + SHOT_AMOUNT + 3;
    diver.sprite.sprite_ids[3] = OCTOPUS_SPRITE + SHOT_AMOUNT + 4;
    diver.enabled = TRUE;

    //draw_diver(&diver);

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

void setup_sound() {
    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
}

void play_ink_shot_sound() {

    NR41_REG = 0x26;
    NR42_REG = 0xA1;
    NR43_REG = 0x31;
    NR44_REG = 0x80;

}

void main() {

    UINT8 current_delay = DEFAULT_DELAY;

    int ink_latch = FALSE;
    setup();

    /* game loop */
    while (1) {

        //current_delay = MOVEMENT_DELAY;


        /* handle input */
        UINT8 move = 1;

        UINT8 joypad_state = joypad();

        if (joypad_state & (J_LEFT | J_RIGHT | J_DOWN | J_UP)) {
            update_octopus_position(octopusPosition, joypad_state);
            update_octopus_sprite(joypad_state);
            scroll_background(joypad_state & (J_LEFT | J_RIGHT | J_DOWN | J_UP));
        }
        else {
            move = 0;
            //current_delay = DEFAULT_DELAY;      
        }

        if (joypad_state & (J_A)) {

            if (!ink_latch) {
                shoot_ink(octopusPosition, octopusDirection, SHOT_SPEED_MULTIPLIER*MOVEMENT_SPEED*direction_to_x_component(octopusDirection), SHOT_SPEED_MULTIPLIER*MOVEMENT_SPEED*direction_to_y_component(octopusDirection));
                ink_latch = TRUE;
            }
        }

        else {
            ink_latch = FALSE;
        }

        move_sprite(OCTOPUS_SPRITE, octopusPosition[0], octopusPosition[1]);
        move_inks();
        draw_inks();
        draw_diver(&diver);


        if (DEBUG) {
            printf("\r\n x: %d, y: %d", octopusPosition[0], octopusPosition[1]);
        }
        delay(current_delay);
    }
}