#include "collision_detector.h"
#include "stdio.h"
int collided(int object_one_x, int object_one_y, int object_one_radius, int object_two_x, int object_two_y, int object_two_radius) {
    // work out the distance between the objects, taxi-cab distance
    int distance = abs(object_one_x - object_two_x) + abs(object_one_y - object_two_y);

    if (distance <= (object_one_radius + object_two_radius)) {
        return 1;
    }
    return 0;
}

int any_ink_shot_hits_diver(Diver * diver, inkList * inks) {
    for (int i = 0; i < INK_SHOT_AMOUNT; i++) {
        ink shot;
        shot = inks->shots[i];

        if (shot.enabled) {
           if (collided(shot.x, shot.y, INK_RADIUS, diver->x, diver->y, DIVER_RADIUS)) {
               // disable the shot
               destroy_ink(&shot);

               inks->shots[i] = shot;

               return 1;
           } 
        }
    }
    return 0;
}