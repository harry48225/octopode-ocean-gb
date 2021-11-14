#include <gb/gb.h>
#include "inkpot.h"
#include "constants.h"

void destroy_ink_pot(inkPot * pot) {
  /* put the shot off of the screen so that 
    the next time it's considered to be drawn it's moved 
    off screen and deactivated */
    pot->x = DESPAWN_X;
    pot->y = DESPAWN_Y;
}

void play_collect_ink_pot_sound() {
  NR10_REG = 0x7B;
  NR11_REG = 0xC2;
  NR12_REG = 0x43;
  NR13_REG = 0x73;
  NR14_REG = 0x86;
}

void spawn_ink_pot(int x, int y, inkPotList * pots) {
  for (int i = 0; i < INK_POT_AMOUNT; i++) {
    inkPot pot;
    pot = pots->pots[i];

    if (!pot.enabled) {
      pot.x = x;
      pot.y = y;
      pot.enabled = TRUE;
      break;
    }
  }
}

void initalise_ink_pot_list(inkPotList * pots) {
  for (int i = 0; i < INK_POT_AMOUNT; i++) {
    inkPot new_ink_pot;

    new_ink_pot.enabled = FALSE;
    new_ink_pot.spriteNumber = OCTOPUS_SPRITE_NUMBER + INK_SHOT_AMOUNT + i;

    pots->pots[i] = new_ink_pot;
  }
}

void draw_ink_pots(inkPotList * pots) {
  for (int i = 0; i < INK_POT_AMOUNT; i++) {
    // 16 = 8 + 8 is the offset to avoid the octopus sprites and inkshot sprites in memory
    inkPot pot;
    pot = pots->pots[i];

    if (pot.enabled) {
      set_sprite_tile(pot.spriteNumber, 17);
      move_sprite(pot.spriteNumber, pot.x, pot.y);

      if (pot.x == DESPAWN_X && pot.y == DESPAWN_Y) {
        pot.enabled = FALSE;
      }
    } else {
      // move the sprite off screen
      move_sprite(pot.spriteNumber, DESPAWN_X, DESPAWN_Y);
    }

    pots->pots[i] = pot;
  }
}