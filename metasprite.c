#include <gb/gb.h>
#include "metasprite.h"

void move_metasprite(MetaSprite * sprite, int x, int y) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            move_sprite(sprite->sprite_ids[2*i + j], x + 8*i, y + 8*j);
        }    
    }
}

void set_metasprite_tiles(MetaSprite * sprite,  int sprite_numbers[4]) {
    for (int i = 0; i < 4; i++) {
        set_sprite_tile(sprite->sprite_ids[i], sprite_numbers[i]);
    }
}

void draw_metasprite(MetaSprite * sprite, int x, int y, int sprite_numbers[4]) {
    set_metasprite_tiles(sprite, sprite_numbers);
    move_metasprite(sprite, x,y);
}