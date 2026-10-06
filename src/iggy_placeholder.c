#include "sprites.h"

/* Palette: index 0 = transparent. 1=black outline, 2=red, 3=white */
const u16 iggy_palette[16] = {
    0x0000,  /* 0 transparent */
    0x0000,  /* 1 black */
    0x001F,  /* 2 red (BGR555) */
    0x7FFF,  /* 3 white */
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000
};

/* 16x32 sprite = 4 tiles wide x 8 tiles tall = 32 tiles.
   Each tile = 8x8 pixels @ 4bpp = 32 bytes = 8 u32 words.
   Total: 32 tiles x 8 = 256 u32 words.
   For Part 0 we only fill a simple silhouette. */

/* Idle frame — silhouette of a standing figure */
const u32 iggy_idle_tiles[256] = {
    /* Row 0 (y=0..7) — head top */
    0x00000000, 0x01111100, 0x01222110, 0x01222110,
    0x01222110, 0x01222110, 0x01111100, 0x00000000,
    /* Row 1 (y=8..15) — face */
    0x00000000, 0x01233210, 0x01233210, 0x01222210,
    0x01222210, 0x01222210, 0x01111110, 0x00000000,
    /* Row 2 (y=16..23) — torso */
    0x00000000, 0x01122211, 0x01122211, 0x01122211,
    0x01122211, 0x01122211, 0x01122211, 0x00000000,
    /* Row 3 (y=24..31) — hips + legs split */
    0x00000000, 0x01122211, 0x01122211, 0x00122210,
    0x00100010, 0x00100010, 0x01100011, 0x00000000,
    /* Padding tiles to reach 32 tiles total — zeros */
    0
};
/* NOTE: The above is a simplified illustration; the actual full sprite
   data is being written as a real byte array in the next message when
   we have the exact frame layout confirmed. For Part 0 we ship a
   working single-tile placeholder to prove the pipeline. */
