#include <gb/gb.h>
#include <stdio.h>

/* import sprites */
#include "sprites/TinyOctopus.c"

void main() {
    UINT8 currentSpriteIndex = 0;

    set_sprite_data(0, 2, TinyOctopus); /* starting from tile 0 read in 2 tiles from TinyOctopus into VRAM */
    set_sprite_tile(0,0); /* set sprite 0 to tile 0 from memory */
    move_sprite(0, 88, 78); /* move sprite 0 to 88, 78 */
    SHOW_SPRITES;

    /* game loop */
    while (1) {
        
        currentSpriteIndex = (currentSpriteIndex + 1) % 2;

        set_sprite_tile(0,currentSpriteIndex); /* set sprite 0 to tile 0 from memory */

        delay(1000);

        scroll_sprite(0, 10, 0);
    }
}