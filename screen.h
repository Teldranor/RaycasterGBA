#ifndef SCREEN_H
#define SCREEN_H

#define RGB16(r,g,b)	((r)+(g<<5)+(b<<10))
#define WIN_WIDTH	240
#define WIN_HEIGHT	160

static unsigned short* Screen = (unsigned short*)0x6000000;
static unsigned short* ScreenBack = (unsigned short*)0x6009600; 
static unsigned short* Palette = (unsigned short*)0x5000000; 

#endif
