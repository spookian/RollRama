#include "gfx/GXReimplementation.h"
#include "gfx/FakeWriter.h"

namespace gfx
{
	FakeWriter::FakeWriter()
	{
		screen_x = 0;
		screen_y = 0;
		cursor_x = 0;
		cursor_y = 0;
		
		back_color.r = 0;
		back_color.g = 0;
		back_color.b = 0;
		back_color.a = 0;
		
		fore_color.r = 255;
		fore_color.g = 255;
		fore_color.b = 255;
		fore_color.a = 255;
	}
	
	void FakeWriter::setPosition(unsigned short _x, unsigned short _y)
	{
		screen_x = _x;
		screen_y = _y;
	}
	
	void FakeWriter::setCursor(unsigned char x, unsigned char y)
	{
		cursor_x = x;
		cursor_y = y;
	}
	
	void FakeWriter::setForegroundColor(unsigned long set)
	{
		*reinterpret_cast<unsigned long*>(&fore_color) = set;
	}
	
	void FakeWriter::setBackgroundColor(unsigned long set)
	{
		*reinterpret_cast<unsigned long*>(&back_color) = set;
	}
	
	void FakeWriter::printCharacter(char c)
	{
		unsigned short sx = this->screen_x + (cursor_x << 3);
		unsigned short sy = this->screen_y + (cursor_y << 4);
		
		if (sx >= MAX_EFB_WIDTH) return;
		if (sy >= MAX_EFB_HEIGHT) return;
		
		unsigned char* cur_char = &console_font_8x16[c * FONT_HEIGHT];
		for (int i = 0; i < FONT_HEIGHT; i++)
		{
			for (int j = 0; j < FONT_WIDTH; j++)
			{
				unsigned short pixelX = sx + j;
				if (pixelX >= MAX_EFB_WIDTH) continue;
				
				unsigned short pixelY = sy + i;
				if (pixelY >= MAX_EFB_HEIGHT) continue;
				
				char bitmask = (128 >> j);
				
				if (cur_char[i] & bitmask) GXPokeARGB(pixelX, pixelY, fore_color);
				else GXPokeARGB(pixelX, pixelY, back_color);
			}
		}
	}
	
	void FakeWriter::printString(const char *string)
	{	
		unsigned long old_back, old_fore;
		old_back = *reinterpret_cast<unsigned long*>(&back_color);
		old_fore = *reinterpret_cast<unsigned long*>(&fore_color);
		int idx = 0;
		while (true)
		{
			if (string[idx] == 0) break;
			// OH BOY I LOVE POTENTIAL CRASHES
			switch (string[idx])
			{
				case 0x01:
				setForegroundColor(*reinterpret_cast<const unsigned long*>(&string[idx + 1]));
				idx += 4;
				break;
				
				case 0x02:
				setBackgroundColor(*reinterpret_cast<const unsigned long*>(&string[idx + 1]));
				idx += 4;
				break;
				
				case '\n':
				this->cursor_y += 1;
				this->cursor_x = 0;
				break;
				
				case 0x20:
				this->cursor_x += 1;
				break;
				
				default:
				printCharacter(string[idx]);
				this->cursor_x += 1;
				break;
			}

			idx++;
		}
		*reinterpret_cast<unsigned long*>(&fore_color) = old_fore;
		*reinterpret_cast<unsigned long*>(&back_color) = old_back;
		return;
	}
}