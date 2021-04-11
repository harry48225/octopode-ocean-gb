#include "ink.h"

void destroy_ink(ink * shot) {

    /* put the shot off of the screen so that 
    the next time it's considered to be drawn it's moved 
    off screen and deactivated */

    shot->enabled = 0;
}