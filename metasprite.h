#ifndef METASPRITE_H
#define METASPRITE_H



typedef struct {
    int spriteNumbers[4];
} MetaSprite;

/** move MetaSprite to x and y

*/
void move_metasprite(MetaSprite * sprite, int x, int y);


/** sets the metasprites tiles
 * @param sprite the metasprite to set the tiles of
 * @param sprite_numbers the numbers of the sprites to use int array of length 4
*/
void set_metasprite_tiles(MetaSprite * sprite,  int sprite_numbers[4]);

/** draws a given metasprite at the given x and y with the given sprite numbers
 * @param x the x-coordinate of the sprite
 * @param y the y-coordinate of the sprite
 * @param sprite_numbers an array of length 4 containing the sprite numbers
*/
void draw_metasprite(MetaSprite * sprite, int x, int y, int sprite_numbers[4]);

#endif