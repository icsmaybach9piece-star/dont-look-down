#include "gba.h"
#include "sprites.h"

/* OAM attribute helpers ---------------------------------------------- */
/* attr0: y(0-7) | unused(8) | mode(10-11) | mosaic(12) | color(13) | shape(14-15) */
static inline u16 obj_attr0(int y, int shape) {
    return (y & 0xFF) | (shape << 14);
}
/* attr1: x(0-8) | unused(9-13) | size(14-15) */
static inline u16 obj_attr1(int x, int size) {
    return (x & 0x1FF) | (size << 14);
}
/* attr2: tile(0-9) | priority(10-11) | pal(12-15) */
static inline u16 obj_attr2(int tile, int pal) {
    return (tile & 0x3FF) | (pal << 12);
}

/* Copy palette + tiles into GBA memory ------------------------------- */
static void load_sprite(void) {
    /* Object palette 0 lives at PAL RAM index 256 */
    for (int i = 0; i < 16; i++) {
        MEM_PALETTE[256 + i] = iggy_palette[i];
    }
    /* Object tile VRAM starts at 0x06010000.
       Copy 64 u32 words = 8 tiles = one 16x32 frame. */
    u32* obj_vram = (u32*)0x06010000;
    for (int i = 0; i < 64; i++) {
        obj_vram[i] = iggy_idle_tiles[i];
    }
}

int main(void) {
    /* Mode 0 + sprites on + 1D tile mapping */
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;

    /* Fill background with dark blue (BGR555: 0x7C00) */
    for (int i = 0; i < 240 * 160; i++) {
        MEM_VRAM[i] = 0x7C00;
    }

    load_sprite();

    /* Iggy starts centered. Sprite is 16x32. */
    int iggy_x = 112;   /* (240-16)/2 */
    int iggy_y = 64;    /* (160-32)/2 */

    /* Sprite 0: shape=0 (square), size=2 (16x32) */
    OAM[0].attr0 = obj_attr0(iggy_y, 0);   /* shape=0 = square */
    OAM[0].attr1 = obj_attr1(iggy_x, 2);   /* size=2 + shape=0 = 16x32 */
    OAM[0].attr2 = obj_attr2(0, 0);        /* tile 0, palette 0 */

    while (1) {
        wait_vblank();

        u16 keys = ~REG_KEYINPUT & KEY_ANY;

        if (keys & KEY_LEFT)  iggy_x -= 2;
        if (keys & KEY_RIGHT) iggy_x += 2;
        if (keys & KEY_UP)    iggy_y -= 2;
        if (keys & KEY_DOWN)  iggy_y += 2;

        /* Clamp to screen (16x32 sprite) */
        if (iggy_x < 0)   iggy_x = 0;
        if (iggy_x > 224) iggy_x = 224;
        if (iggy_y < 0)   iggy_y = 0;
        if (iggy_y > 128) iggy_y = 128;

        OAM[0].attr0 = obj_attr0(iggy_y, 0);
        OAM[0].attr1 = obj_attr1(iggy_x, 2);
    }

    return 0;
}
