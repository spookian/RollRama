#pragma once
#include "gfx/GXStructs.h"

extern "C"
{
	extern void GXInitTexObj(GXTexObj*, void*, unsigned short, unsigned short, GXTexFmt, GXTexWrapMode, GXTexWrapMode, bool);
	extern void GXLoadTexObj(const GXTexObj*, GXTexMapID);
	
	extern void GXSetNumTexGens(unsigned long num);
	extern void GXSetTexCoordGen2(long, long, long, long, long, long); // i didn't bother
}