#ifndef GBA_H
#define GBA_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    s8;
typedef signed short   s16;
typedef signed int     s32;

#define REG_DISPCNT  (*(volatile u16*)0x04000000)
#define REG_VCOUNT   (*(volatile u16*)0x04000006)
#define REG_KEYINPUT (*(volatile u16*)0x04000130)

#define MEM_PALETTE  ((u16*)0x05000000)
#define MEM_VRAM     ((u16*)0x06000000)
#define MEM_OAM      ((u16*)0x07000000)

#define DCNT_MODE0   0x0000
#define DCNT_OBJ     0x1000
#define DCNT_OBJ_1D  0x0040
#define DCNT_BG0     0x0100

#define KEY_A      0x0001
#define KEY_B      0x0002
#define KEY_SELECT 0x0004
#define KEY_START  0x0008
#define KEY_RIGHT  0x0010
#define KEY_LEFT   0x0020
#define KEY_UP     0x0040
#define KEY_DOWN   0x0080
#define KEY_R      0x0100
#define KEY_L      0x0200

#define KEY_ANY    0x03FF

/* OAM entry helpers */
typedef struct {
    u16 attr0;
    u16 attr1;
    u16 attr2;
    u16 pad;
} OBJATTR;

#define OAM  ((OBJATTR*)0x07000000)

static inline void wait_vblank(void) {
    while (REG_VCOUNT >= 160);
    while (REG_VCOUNT < 160);
}

#endif
