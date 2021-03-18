#include "diver.h"

void move_diver(Diver * diver, int x, int y) {

    diver->x = x;
    diver->y = y;

}

void draw_diver(Diver * diver) {


    draw_metasprite(&diver->sprite, diver->x, diver->y, diver->spriteNumbers);

}

void set_driver_sprites(Diver * driver, int sprite_numbers[]) {
    for (int i = 0; i < 4; i++) {
        driver->spriteNumbers[i] = sprite_numbers[i];
    }
}