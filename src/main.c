#include "gba.h"
#include "sprites.h"

/* Simple OAM attribute helpers */
static inline u16 obj_attr0(int y, int shape, int mode) {
    return (y & 0xFF) | (mode << 8) | (shape << 14);
}
static inline u16 obj_attr1(int x, int size) {
    return (x & 0x1FF) | (size << 14);
}
static inline u16 obj_attr2(int tile, int pal) {
    return (tile & 0x3FF) | (pal << 12);
}

/* Copy palette + tiles into GBA memory */
static void load_sprite(void) {
    /* Palette: object palette starts at index 256 of PAL RAM.
       We put ours at object palette 0 → offset 256. */
    for (int i = 0; i < 16; i++) {
        MEM_PALETTE[256 + i] = iggy_palette[i];
    }
    /* Tile data: object VRAM starts at 0x06010000.
       Copy 8 words (32 bytes) = one 4bpp tile. */
    u32* obj_vram = (u32*)0x06010000;
    for (int i = 0; i < 8; i++) {
        obj_vram[i] = iggy_idle_tiles[i];
    }
}

int main(void) {
    /* Mode 0 + sprites on + 1D sprite mapping */
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D;

    /* Fill background with a dark blue so Iggy stands out */
    for (int i = 0; i < 240 * 160; i++) {
        MEM_VRAM[i] = 0x7C00; /* dark blue in BGR555 */
    }

    load_sprite();

    /* Iggy starts near the middle */
    int iggy_x = 116;   /* 240/2 - 4 */
    int iggy_y = 76;    /* 160/2 - 4 */

    /* Sprite 0: 8x8 square, shape=0 (square), size=0 (8x8) */
    OAM[0].attr0 = obj_attr0(iggy_y, 0, 0);
    OAM[0].attr1 = obj_attr1(iggy_x, 0);
    OAM[0].attr2 = obj_attr2(0, 0);

    while (1) {
        wait_vblank();

        u16 keys = ~REG_KEYINPUT & KEY_ANY;

        if (keys & KEY_LEFT)  iggy_x -= 2;
        if (keys & KEY_RIGHT) iggy_x += 2;
        if (keys & KEY_UP)    iggy_y -= 2;
        if (keys & KEY_DOWN)  iggy_y += 2;

        /* Clamp to screen (8x8 sprite) */
        if (iggy_x < 0)   iggy_x = 0;
        if (iggy_x > 232) iggy_x = 232;
        if (iggy_y < 0)   iggy_y = 0;
        if (iggy_y > 152) iggy_y = 152;

        OAM[0].attr0 = obj_attr0(iggy_y, 0, 0);
        OAM[0].attr1 = obj_attr1(iggy_x, 0);
    }

    return 0;
}
