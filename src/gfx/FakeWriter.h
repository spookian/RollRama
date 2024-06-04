#include "gfx/GXReimplementation.h"
#define FONT_WIDTH 8
#define FONT_HEIGHT 16
#define MAX_EFB_WIDTH 640
#define MAX_EFB_HEIGHT 528

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
		void setForegroundColor(GXColor set)
		{
			*reinterpret_cast<unsigned long*>(&fore_color) = *reinterpret_cast<unsigned long*>(&set);
		}
		void setBackgroundColor(GXColor set)
		{
			*reinterpret_cast<unsigned long*>(&back_color) = *reinterpret_cast<unsigned long*>(&set);
		}
		
		void printCharacter(char c)
		{
			if (this->x >= MAX_EFB_WIDTH) return;
			if (this->y >= MAX_EFB_HEIGHT) return;
			
			unsigned char* cur_char = &console_font_8x16[c * FONT_HEIGHT];
			for (int i = 0; i < FONT_HEIGHT; i++)
			{
				for (int j = 0; j < FONT_WIDTH; j++)
				{
					unsigned short pixelX = this->x + j;
					if (pixelX >= MAX_EFB_WIDTH) continue;
					
					unsigned short pixelY = this->y + i;
					if (pixelY >= MAX_EFB_HEIGHT) continue;
					
					char bitmask = (128 >> j);
					
					if (cur_char[i] & bitmask) GXPokeARGB(pixelX, pixelY, fore_color);
					else GXPokeARGB(pixelX, pixelY, back_color);
				}
			}
		}
		
		void printString(const char *string)
		{
			short old_x = x;
			short old_y = y;
			int idx = 0;
			while (true)
			{
				// OH BOY I LOVE POTENTIAL CRASHES
				if (string[idx] == 0) break;

				if (string[idx] != '\n') 
				{
					printCharacter(string[idx]);
					this->x += FONT_WIDTH;
				}
				else this->y += FONT_HEIGHT;
				
				idx++;
			}
			x = old_x;
			y = old_y;
			return;
		}
	};
}