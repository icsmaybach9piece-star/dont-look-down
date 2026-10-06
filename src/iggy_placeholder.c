#include "sprites.h"

/* Palette: 0=transparent, 1=black outline, 2=red (body), 3=white (face) */
const u16 iggy_palette[16] = {
    0x0000,  /* 0 transparent */
    0x0000,  /* 1 black */
    0x001F,  /* 2 red */
    0x7FFF,  /* 3 white */
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000
};

/* ---- IDLE FRAME — 16x32 = 8 tiles (2 wide x 4 tall) ----
   Each tile is 8x8 @ 4bpp = 8 u32 words.
   Order: left-top, right-top, left-upper, right-upper,
          left-lower, right-lower, left-bottom, right-bottom */

const u32 iggy_idle_tiles[64] = {
    /* Tile 0: head top-left (x0-7, y0-7) */
    0x00111100, 0x00133110, 0x00133110, 0x00133110,
    0x00133310, 0x00011100, 0x00133110, 0x00133110,

    /* Tile 1: head top-right (x8-15, y0-7) */
    0x00111100, 0x01133100, 0x01133100, 0x01133100,
    0x01333300, 0x00111000, 0x01133100, 0x01133100,

    /* Tile 2: upper torso left (y8-15) */
    0x00111100, 0x00122110, 0x00122110, 0x00122110,
    0x00122110, 0x00122110, 0x01122110, 0x11222111,

    /* Tile 3: upper torso right (y8-15) */
    0x00111100, 0x01122100, 0x01122100, 0x01122100,
    0x01122100, 0x01122100, 0x01122110, 0x11122111,

    /* Tile 4: lower torso left (y16-23) */
    0x11222211, 0x11222211, 0x01122210, 0x00122210,
    0x00122210, 0x00122210, 0x00122210, 0x00111100,

    /* Tile 5: lower torso right (y16-23) */
    0x11222211, 0x11222211, 0x01222110, 0x01222100,
    0x01222100, 0x01222100, 0x01222100, 0x00111100,

    /* Tile 6: legs left (y24-31) */
    0x00111100, 0x00122110, 0x00122110, 0x00122110,
    0x00111100, 0x00000000, 0x00000000, 0x00000000,

    /* Tile 7: legs right (y24-31) */
    0x00111100, 0x01122100, 0x01122100, 0x01122100,
    0x00111100, 0x00000000, 0x00000000, 0x00000000
};

/* ---- WALK FRAME — same shape, legs shifted for animation ---- */
const u32 iggy_walk_tiles[64] = {
    /* Tile 0: head top-left — same */
    0x00111100, 0x00133110, 0x00133110, 0x00133110,
    0x00133310, 0x00011100, 0x00133110, 0x00133110,

    /* Tile 1: head top-right — same */
    0x00111100, 0x01133100, 0x01133100, 0x01133100,
    0x01333300, 0x00111000, 0x01133100, 0x01133100,

    /* Tile 2: torso left — same */
    0x00111100, 0x00122110, 0x00122110, 0x00122110,
    0x00122110, 0x00122110, 0x01122110, 0x11222111,

    /* Tile 3: torso right — same */
    0x00111100, 0x01122100, 0x01122100, 0x01122100,
    0x01122100, 0x01122100, 0x01122110, 0x11122111,

    /* Tile 4: lower torso left — same */
    0x11222211, 0x11222211, 0x01122210, 0x00122210,
    0x00122210, 0x00122210, 0x00122210, 0x00111100,

    /* Tile 5: lower torso right — same */
    0x11222211, 0x11222211, 0x01222110, 0x01222100,
    0x01222100, 0x01222100, 0x01222100, 0x00111100,

    /* Tile 6: legs left — SHIFTED for walk */
    0x00111100, 0x00122110, 0x00122110, 0x00122110,
    0x00122110, 0x00111100, 0x00000000, 0x00000000,

    /* Tile 7: legs right — SHIFTED for walk */
    0x00111100, 0x01122100, 0x01122100, 0x01122100,
    0x01122100, 0x00111100, 0x00000000, 0x00000000
};
