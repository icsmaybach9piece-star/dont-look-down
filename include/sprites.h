#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

/* Iggy placeholder sprite — 16 wide x 32 tall, 4bpp, 16 palette indices.
   Two frames: idle + walk. Hand-coded for Part 0. */
extern const u16 iggy_palette[16];
extern const u32 iggy_idle_tiles[64];   /* 16x32 @ 4bpp = 64 u32 words */
extern const u32 iggy_walk_tiles[64];

#endif
