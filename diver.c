#include "metasprite.h"
#include "diver.h"
#include "stdio.h"
#include "stdlib.h"


const int DIVER_DIRECTION_COUNTER_LIMIT = 10;
const int directions_x[] = {1,1,0,-1,-1,-1,0,1};
const int directions_y[] = {0,1,1,1,0,-1,-1,-1};

int NORTH_SPRITES[4] = {16, 17, 18, 19};
int SOUTH_SPRITES[4] = {20, 21, 22, 23};
int WEST_SPRITES[4] = {24, 25, 26, 27};
int EAST_SPRITES[4] = {28, 29, 30, 31};
int NORTH_WEST_SPRITES[4] = {32, 33, 34, 35};
int NORTH_EAST_SPRITES[4] = {36, 37, 38, 39};
int SOUTH_WEST_SPRITES[4] = {40, 41, 42, 43};
int SOUTH_EAST_SPRITES[4] = {44, 45, 46, 47};


// Maps the direction_numbers to the actual direction the driver is moving
const enum diver_directions direction_lookup[8] = {
    DIVER_EAST, DIVER_SOUTH_EAST, DIVER_SOUTH, DIVER_SOUTH_WEST,
    DIVER_WEST, DIVER_NORTH_WEST, DIVER_NORTH, DIVER_NORTH_EAST
};

enum diver_directions direction_from_vector(int x, int y) {

    if (x == 1 && y == 0) {
        return DIVER_EAST;
    } else if (x == 1 && y == 1) {
        return DIVER_SOUTH_EAST;
    } else if (x == 1 && y == -1) {
        return DIVER_NORTH_EAST;
    } else if (x == 0 && y == 1) {
        return  DIVER_SOUTH;
    } else if (x == 0 && y == -1) {
        return DIVER_NORTH;
    } else if (x == -1 && y == 0) {
        return DIVER_WEST;
    } else if (x == -1 && y == 1) {
        return DIVER_SOUTH_WEST;
    } else if (x == -1 && y == -1) {
        return DIVER_NORTH_WEST;
    } else {
        return DIVER_NORTH;
    }

}

void move_diver(Diver * diver, int x, int y) {

    diver->x = x;
    diver->y = y;

}

void draw_diver(Diver * diver) {

    update_diver_sprite_from_direction(diver);
    draw_metasprite(&diver->sprite, diver->x, diver->y, diver->spriteNumbers);

}

void set_driver_sprites(Diver * diver, int sprite_numbers[]) {
    for (int i = 0; i < 4; i++) {
        diver->spriteNumbers[i] = sprite_numbers[i];
    }
}

void update_diver_sprite_from_direction(Diver * diver) {
    
    if (diver->direction == DIVER_NORTH) {
        set_driver_sprites(diver, NORTH_SPRITES);
    }
    else if (diver->direction == DIVER_SOUTH) {
        set_driver_sprites(diver, SOUTH_SPRITES);
    }
    else if (diver->direction == DIVER_EAST) {
        set_driver_sprites(diver, EAST_SPRITES);
    }
    else if (diver->direction == DIVER_WEST) {
        set_driver_sprites(diver, WEST_SPRITES);
    }
    else if (diver->direction == DIVER_NORTH_EAST) {
        set_driver_sprites(diver, NORTH_EAST_SPRITES);
    }
    else if (diver->direction == DIVER_NORTH_WEST) {
        set_driver_sprites(diver, NORTH_WEST_SPRITES);
    }
    else if (diver->direction == DIVER_SOUTH_EAST) {
        set_driver_sprites(diver, SOUTH_EAST_SPRITES);
    }
    else if (diver->direction == DIVER_SOUTH_WEST) {
        set_driver_sprites(diver, SOUTH_WEST_SPRITES);
    }


    
}

void simulate_diver(Diver * diver, int octopus_x, int octopus_y) {

    int distance_to_player = abs(diver->x - octopus_x) + abs(diver->y - octopus_y);

    if (distance_to_player <= ACTIVATION_RANGE) {
        diver->state = DIVER_CHASING;
    }

    // if the octopus has moved far enough away, stop chasing
    if (distance_to_player > ACTIVATION_RANGE && diver->state == DIVER_CHASING) {
        diver->state = DIVER_ROAMING;
    }

    // point towards the octopus and move towards them
    if (diver->state == DIVER_CHASING) {

        int relative_x = diver->x - octopus_x;
        int relative_y = diver->y - octopus_y;
        int TOLERANCE = 20;
        
        int movement_x = 0;
        int movement_y = 0;

        if (relative_x >= TOLERANCE) {
            movement_x = -1;
        } else if (relative_x <= -TOLERANCE) {
            movement_x = 1;
        }

        if (relative_y >= TOLERANCE) {
            movement_y = -1;
        } else if (relative_y <= -TOLERANCE) {
            movement_y = 1;
        }


        diver->x += movement_x;
        diver->y += movement_y;

        diver->direction = direction_from_vector(movement_x, movement_y);
    } 
    
    else if (diver->state == DIVER_ROAMING) {
        
        diver->direction_counter += 1;

        if (diver->direction_counter >= DIVER_DIRECTION_COUNTER_LIMIT) {
            // turn the diver

            diver->direction_number = (diver->direction_number + 1) % 8;

            diver->direction_counter = 0;
        }

        // move the diver in the direction of the angle
        diver->direction = direction_lookup[diver->direction_number];
        diver->x += directions_x[diver->direction_number];
        diver->y += directions_y[diver->direction_number];

    }
}