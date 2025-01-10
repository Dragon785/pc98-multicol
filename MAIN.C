#include <i86.h>
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graphics.h"

int checkKeyBuf(void)
{
	union REGS regs;

	regs.h.ah=0x01; // Check Key Buffer

#if defined(__386__)&&defined(__DOS__)
	int386(0x18,&regs,&regs);
#else
	int86(0x18,&regs,&regs);
#endif
	return (regs.h.bh!=0);
}

static void drawTestPattern()
{
	volatile unsigned char* b=(unsigned char*)(0x000a8000);
	volatile unsigned char* r=(unsigned char*)(0x000b0000);
	volatile unsigned char* g=(unsigned char*)(0x000b8000);
	volatile unsigned char* e=(unsigned char*)(0x000e0000);

	for (int y=0;y<400;++y)
	{
		int chk=(y%57);
		// skip near border
		int mustSkip=((chk==0)||(chk==1)||(chk==55)||(chk==56));
		
		for (int x=0;x<16;++x)
		{
			for (int i=0;i<5;++i)
			{
				if (mustSkip)
				{
					*b++=0;*r++=0;*g++=0;*e++=0;
				}
				else
				{
					*b++=(x&1) ? 0xff : 0x00;
					*r++=(x&2) ? 0xff : 0x00;
					*g++=(x&4) ? 0xff : 0x00;
					*e++=(x&8) ? 0xff : 0x00;
				}
			}
		}
	}
}

// multicolor palette data
unsigned char pal[7][16][3]={0};

// パレットを16色まとめてセットする
static inline void setPals(int palNo)
{
	palNo%=7;
	for (int i=0;i<16;i++)
	{
		setPalette(i,pal[palNo][i][0],
					     pal[palNo][i][1],
					     pal[palNo][i][2]);
	}
}

int main(void)
{
	setGraphMode(0xc0);

	enableGraph(1);
	enableText(0);
	enable16Col(1);
	
	drawTestPattern();
	// set default palette
	for (unsigned char p=0;p<16;++p)
	{
		setPalette(p,p,p,p);
	}
	// caliculate palette table
	{
		for (int i=0;i<7;++i)
		{
			int digiCol=(i+1);
			for (int p=0;p<16;++p)
			{
				pal[i][p][0]=(digiCol&2) ? p:0;
				pal[i][p][1]=(digiCol&4) ? p:0;
				pal[i][p][2]=(digiCol&1) ? p:0;
			}
		}
	}

	while (!(inp(0xa0)&0x20)); /* Wait VBlank */
	while (inp(0xa0)&0x20); /* Wait End VBlank */

	int mustStop=0;
	while(!mustStop)
	{
		// VBLANK待ち
		while (!(inp(0xa0)&0x20));
		// VBLANK内処理(キー入力監視と0ライン目パレットセット)
		if (checkKeyBuf()) // check quit
		{
			mustStop=1;
		}
		int usePal=0;
		setPals(usePal);
		
		// VBLANK Out Wait
		while (inp(0xa0)&0x20);
		// HBLANK突入待機
		int chgCnt=57; // パレット読み直しカウンタ
		for (int line=1;line<400;++line)
		{
			while (!(inp(0xa0)&0x40));
			// HBLANK内処理
			if ((--chgCnt)==0)
			{
				chgCnt=57;
				
				setPals(++usePal);
			}
			// HBLANK抜け待機
			while (inp(0xa0)&0x40);
		}
	}

	enableGraph(0);
	enableText(1);
	enable16Col(0);

	return 0;
}
