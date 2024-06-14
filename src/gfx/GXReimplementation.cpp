#include "gfx/GXStructs.h"
#include "gfx/GXReimplementation.h"

extern "C"
{
	// GXPokeARGB - This implementation was taken straight from Libogc's source code, but like always I have looked into the code and done some research to make sure I actually understand the code.
	void GXPokeARGB(unsigned short x, unsigned short y, _GXColor color)
	{
		unsigned long efb_loc; // oh. that's the embedded framebuffer. https://hitmen.c02.at/files/yagcd/yagcd/chap4.html
		
		//unsigned long fixed_col = (color.a << 24) | (color.r << 16) | (color.g << 8) | (color.b); // why is the source trying to mask an unsigned char to fit an unsigned char
		unsigned long fixed_col = *reinterpret_cast<unsigned long*>(&color);
		fixed_col = (fixed_col >> 8) | (color.a << 24);
		
		efb_loc = 0xc8000000 | _SHIFTL(x, 2, 10); // x * 4 because the efb is an array of 640x528 rgba pixels
		efb_loc = (efb_loc & ~0x3FF000) | (_SHIFTL(y, 12, 10)); // y * 4096; this one doesn't quite make sense 
		*(unsigned long*)efb_loc = fixed_col;
	}
	// seems like RTDL is expecting to be poked... in __GXInitGX, GXPokeBlendMode() is called with the arguments 0, 0, 1 and 15.
	// those correspond to the constants GX_BM_NONE, GX_BL_ZERO, GX_BL_ONE, and GX_LO_SET. that's the only time GXPokeBlendMode is called.
}