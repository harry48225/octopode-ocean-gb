#ifndef INK_H
#define INK_H

#define INK_RADIUS 8
#define INK_SHOT_AMOUNT 4

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

#endif