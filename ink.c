#include <gb/gb.h>
#include "ink.h"
#include "constants.h"

void destroy_ink(ink * shot) {

    /* put the shot off of the screen so that 
    the next time it's considered to be drawn it's moved 
    off screen and deactivated */

    shot->enabled = 0;
}

void play_ink_shot_sound() {

    NR41_REG = 0x26;
    NR42_REG = 0xA1;
    NR43_REG = 0x31;
    NR44_REG = 0x80;

}

void shoot_ink(int originPosition[], int direction, int x_velocity, int y_velocity, inkList * inks) {
// Shoots an ink shot originating from the the origin position in the given direction


    for (int i = 0; i < INK_SHOT_AMOUNT; i++) {

        ink shot;
        shot = inks->shots[i];

        if (!shot.enabled) {
            shot.x = originPosition[0];
            shot.y = originPosition[1];
            shot.direction = direction;
            shot.x_vel = x_velocity;
            shot.y_vel = y_velocity;
            shot.enabled = TRUE;
            shot.spriteNumber = OCTOPUS_SPRITE + 1 + i; // need to implement some sort of dynamic sprite numbering system

            inks->shots[i] = shot;

            play_ink_shot_sound();
            break;
        }
    }

}

void initalise_ink_list(inkList *inks) {

    for (int i = 0; i < INK_SHOT_AMOUNT; i++) {
        ink new_ink;

        new_ink.enabled = 0;

        inks->shots[i] = new_ink;
    }

}

void draw_inks(inkList *inks) {
    for (int i = 0; i < INK_SHOT_AMOUNT; i++) {
        // This works because the order the sprites are in VRAM are the same as in the order of the directions in the enum
        // 8 is the offset to avoid the octopus sprites in memory
        ink shot;
        shot = inks->shots[i];
        set_sprite_tile(shot.spriteNumber, 8 + shot.direction); 
        if (shot.enabled) {
            move_sprite(shot.spriteNumber, shot.x, shot.y);
        }

        else if (!shot.enabled) {
            // move the sprite off screen
            move_sprite(shot.spriteNumber, DISPLAY_WIDTH + 24, DISPLAY_HEIGHT + 24);
        }
    }
}

void move_inks(inkList *inks) {
    for (int i = 0; i < INK_SHOT_AMOUNT; i++) {
        ink shot;
        shot = inks->shots[i];

        if (shot.enabled) {
            shot.x += shot.x_vel;
            shot.y += shot.y_vel;

            // Despawn the shot if it's off screen, with some tolerance to ensure that they're fully off

            if ((shot.x > DISPLAY_WIDTH + 24) || (shot.x < -24) || (shot.y > DISPLAY_HEIGHT + 24) || (shot.y < -24)) {
                shot.enabled = FALSE;
            }

            inks->shots[i] = shot;
        }
        
    }
}