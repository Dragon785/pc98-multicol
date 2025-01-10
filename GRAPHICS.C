#include "graphics.h"
#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <assert.h>

void setGraphMode(unsigned char md)
{
	union REGS regs;

	regs.h.ch = md;
	regs.h.ah = 0x42;

#if defined(__386__)&&defined(__DOS__)
	int386(0x18, &regs, &regs);
#else
	int86(0x18, &regs, &regs);
#endif
}

void enableGraph(int enbl)
{
	union REGS regs;

	regs.h.ch = 0;
	regs.h.ah = ((enbl) ? 0x40 : 0x41);

#if defined(__386__)&&defined(__DOS__)
	int386(0x18, &regs, &regs);
#else
	int86(0x18, &regs, &regs);
#endif

}

void enableText(int enbl)
{
	union REGS regs;

	regs.h.ah = ((enbl) ? (0x0c) : (0x0d));

#if defined(__386__)&&defined(__DOS__)
	int386(0x18, &regs, &regs);
#else
	int86(0x18, &regs, &regs);
#endif

}

void enable16Col(int enbl)
{
	outp(0x6a, (enbl) ? 0x1 : 0x0);
}

void setPalette(unsigned char pal, unsigned char r, unsigned char g, unsigned char b)
{
	outp(0xa8, pal & 0xf);
	outp(0xaa, g & 0xf);
	outp(0xac, r & 0xf);
	outp(0xae, b & 0xf);
}

void setBorderColor(int col)
{
	outp(0x6c,(col<<4));
}
