#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

/* Iggy placeholder — 16x32, 4bpp, 2 frames.
   8 tiles per frame (2 wide x 4 tall), 8 u32 words per tile = 64 words. */
extern const u16 iggy_palette[16];
extern const u32 iggy_idle_tiles[64];
extern const u32 iggy_walk_tiles[64];

#endif
