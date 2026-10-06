#include "gba.h"

int main(void) {
    /* Mode 3: bitmap, direct color writes */
    REG_DISPCNT = 0x0003;

    /* Fill with bright red (BGR555: 0x001F) */
    volatile u16* vram = (volatile u16*)0x06000000;
    for (int i = 0; i < 240 * 160; i++) {
        vram[i] = 0x001F;
    }

    while (1) {
        wait_vblank();
    }
    return 0;
}
