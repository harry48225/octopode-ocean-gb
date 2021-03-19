#include "metasprite.h"
#include "diver.h"


const int DIVER_DIRECTION_COUNTER_LIMIT = 10;
const int directions_x[] = {1,1,0,-1,-1,-1,0,1};
const int directions_y[] = {0,1,1,1,0,-1,-1,-1};

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

void simulate_diver(Diver * diver) {

    if (diver->state == DIVER_ROAMING) {
        
        diver->direction_counter += 1;

        if (diver->direction_counter >= DIVER_DIRECTION_COUNTER_LIMIT) {
            // turn the diver

            diver->direction_number = (diver->direction_number + 1) % 8;

            diver->direction_counter = 0;
        }

        // move the diver in the direction of the angle

        diver->x += directions_x[diver->direction_number];
        diver->y += directions_y[diver->direction_number];

    }
}