#include "gba.h"
#include "sprites.h"

/* OAM attribute helpers */
static inline u16 obj_attr0(int y, int shape) {
    return (y & 0xFF) | (shape << 14);
}
static inline u16 obj_attr1(int x, int size) {
    return (x & 0x1FF) | (size << 14);
}
static inline u16 obj_attr2(int tile, int pal) {
    return (tile & 0x3FF) | (pal << 12);
}

static void load_sprite(void) {
    /* Object palette 0 = PAL RAM index 256..271 */
    for (int i = 0; i < 16; i++) {
        MEM_PALETTE[256 + i] = iggy_palette[i];
    }
    /* Object tile VRAM at 0x06010000. Copy 64 words = 8 tiles. */
    u32* obj_vram = (u32*)0x06010000;
    for (int i = 0; i < 64; i++) {
        obj_vram[i] = iggy_idle_tiles[i];
    }
}

static void fill_bg_blue(void) {
    /* Mode 3: VRAM is a 240x160 bitmap of 15-bit BGR555 colors.
       A dark blue is roughly 0x7C00. */
    u16* vram = (u16*)0x06000000;
    for (int i = 0; i < 240 * 160; i++) {
        vram[i] = 0x7C00;
    }
}

int main(void) {
    /* Mode 3 (bitmap bg) + sprites enabled + 1D tile mapping */
    REG_DISPCNT = 0x0003 | DCNT_OBJ | DCNT_OBJ_1D;

    fill_bg_blue();
    load_sprite();

    int iggy_x = 112;   /* (240-16)/2 */
    int iggy_y = 64;    /* (160-32)/2 */

    /* shape=0 (square), size=2 (16x32) */
    OAM[0].attr0 = obj_attr0(iggy_y, 0);
    OAM[0].attr1 = obj_attr1(iggy_x, 2);
    OAM[0].attr2 = obj_attr2(0, 0);

    while (1) {
        wait_vblank();

        u16 keys = ~REG_KEYINPUT & KEY_ANY;

        if (keys & KEY_LEFT)  iggy_x -= 2;
        if (keys & KEY_RIGHT) iggy_x += 2;
        if (keys & KEY_UP)    iggy_y -= 2;
        if (keys & KEY_DOWN)  iggy_y += 2;

        if (iggy_x < 0)   iggy_x = 0;
        if (iggy_x > 224) iggy_x = 224;
        if (iggy_y < 0)   iggy_y = 0;
        if (iggy_y > 128) iggy_y = 128;

        OAM[0].attr0 = obj_attr0(iggy_y, 0);
        OAM[0].attr1 = obj_attr1(iggy_x, 2);
    }
    return 0;
}
