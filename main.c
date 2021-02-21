#include <gb/gb.h>
#include <stdio.h>

/* import sprites */
#include "sprites/TinyOctopus.c"

void main() {
    UINT8 currentSpriteIndex = 0;
    UINT8 current_delay = 100;
    set_sprite_data(0, 2, TinyOctopus); /* starting from tile 0 read in 2 tiles from TinyOctopus into VRAM */
    set_sprite_tile(0,0); /* set sprite 0 to tile 0 from memory */
    move_sprite(0, 88, 78); /* move sprite 0 to 88, 78 */
    SHOW_SPRITES;

    /* game loop */
    while (1) {

        current_delay = 100;
        switch(joypad()) {
            case J_LEFT:
                scroll_sprite(0, -10, 0);
                break;
            case J_RIGHT:
                scroll_sprite(0, 10, 0);
                break;
            case J_UP:
                scroll_sprite(0, 0, -10);
                break;
            case J_DOWN:
                scroll_sprite(0, 0, 10);
                break;
            default:
                current_delay = 5;

            

        }
        
        /* animate tiny-octopus */
        currentSpriteIndex = (currentSpriteIndex + 1) % 2;

        set_sprite_tile(0,currentSpriteIndex); /* set sprite 0 to tile 0 from memory */

        delay(current_delay);
    }
}