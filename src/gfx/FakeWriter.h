#pragma once

#include "gfx/GXReimplementation.h"
#define FONT_WIDTH 8
#define FONT_HEIGHT 16
#define MAX_EFB_WIDTH 640
#define MAX_EFB_HEIGHT 528

#define GLYPH_XPOS(x) (x << 3)
#define GLYPH_YPOS(y) (y << 4)

extern "C"
{
	extern unsigned char console_font_8x16[];
}

namespace gfx
{
	class FakeWriter
	{
		unsigned short x, y;
		GXColor fore_color;
		GXColor back_color;
		
	public:
		FakeWriter()
		{
			x = 0;
			y = 0;
			back_color.r = 0;
			back_color.g = 0;
			back_color.b = 0;
			back_color.a = 0;
			
			fore_color.r = 255;
			fore_color.g = 255;
			fore_color.b = 255;
			fore_color.a = 255;
		}
	
		void setPosition(unsigned short _x, unsigned short _y);
		
		void setForegroundColor(unsigned long set);
		void setBackgroundColor(unsigned long set);
		
		void printCharacter(char c);
		void printString(const char *string);
	};
}