#include "gfx/GXReimplementation.h"
#include "gfx/FakeWriter.h"

namespace gfx
{
	void FakeWriter::setPosition(unsigned short _x, unsigned short _y)
	{
		x = _x;
		y = _y;
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
	
	void FakeWriter::printString(const char *string)
	{
		short old_x = x;
		short old_y = y;
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
				this->y += FONT_HEIGHT;
				this->x = old_x;
				break;
				
				default:
				printCharacter(string[idx]);
				this->x += FONT_WIDTH;
				break;
			}

			idx++;
		}
		x = old_x;
		y = old_y;
		*reinterpret_cast<unsigned long*>(&fore_color) = old_fore;
		*reinterpret_cast<unsigned long*>(&back_color) = old_back;
		return;
	}
}