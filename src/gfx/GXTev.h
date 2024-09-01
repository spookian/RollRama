#pragma once
#include "gfx/GXStructs.h"

extern "C"
{
	extern void GXSetTevOp(long id, long mode);
	extern void GXSetTevColorIn(long stage, long a, long b, long c, long d);
	extern void GXSetTevAlphaIn(long stage, long a, long b, long c, long d);
	extern void GXSetTevColorOp(long stage, long op, long bias, long scale, bool clamp, long out_reg);
	extern void GXSetTevAlphaOp(long stage, long op, long bias, long scale, bool clamp, long out_reg);
	extern void GXSetTevColor(long id, GXColor color);
	extern void GXSetTevSwapMode(long stage, long ras_sel, long tex_sel);
	extern void GXSetTevSwapModeTable(long, long, long, long, long);
	extern void GXSetTevOrder(long stage, long coord, long map, long color);
	extern void GXSetNumTevStages(unsigned char nStages);
	extern void GXPixModeSync();
	extern void GXTexModeSync();
}