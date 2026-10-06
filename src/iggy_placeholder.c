#include "sprites.h"

/* Palette: 0=transparent, 1=black, 2=red, 3=white */
const u16 iggy_palette[16] = {
    0x0000, 0x0000, 0x001F, 0x7FFF,
    0,0,0,0, 0,0,0,0, 0,0,0,0
};

/* 8x8 tile @ 4bpp = 32 bytes = 8 u32 words.
   A red square with a black border: */
const u32 iggy_idle_tiles[8] = {
    0x11111111,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x11111111
};

/* Same for walk frame for now — we'll differentiate in Part 0b */
const u32 iggy_walk_tiles[8] = {
    0x11111111,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x12222221,
    0x11111111
};
