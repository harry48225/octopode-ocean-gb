#ifndef INK_H
#define INK_H

#define INK_RADIUS 8
#define INK_SHOT_AMOUNT 4

#define DESPAWN_X 200
#define DESPAWN_Y 200

typedef struct {
    int x;
    int y;
    int x_vel;
    int y_vel;
    int direction;
    int spriteNumber;
    int enabled;
} ink;

typedef struct {
    ink shots[INK_SHOT_AMOUNT]; // can have a maximum of INK_SHOT_AMOUNT shots at a time
} inkList;

/** destroys a given ink shot, note this modifies the in place and it should be overwritten in the array to take effect
 * @param shot the shot to destory
*/
void destroy_ink(ink * shot);

#endif