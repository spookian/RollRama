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
		unsigned short screen_x, screen_y;
		unsigned short cursor_x, cursor_y;
		
		GXColor fore_color;
		GXColor back_color;
		
	public:
		FakeWriter();
	
		void setPosition(unsigned short _x, unsigned short _y);
		void setCursor(unsigned char x, unsigned char y);
		
		void setForegroundColor(unsigned long set);
		void setBackgroundColor(unsigned long set);
		
		void printCharacter(char c);
		void printString(const char *string);
	};
}