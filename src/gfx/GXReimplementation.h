#include "gfx/GXStructs.h"
#define _SHIFTL(v, s, w) ((unsigned long) (((unsigned long)(v) & ((0x01 << (w)) - 1)) << (s)))
// this masks the first w bits of v before shifting by s, but i feel like this is a pretty screwed up way to just use the rlwinm instruction

extern "C"
{
	extern void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_fact, GXBlendFactor dst_fact, GXLogicOp op);
	extern void GXPokeARGB(unsigned short x, unsigned short y, _GXColor color);
	extern void GXSetCopyClear(GXColor clearColor, unsigned long clearZ); // apparently this is on a public patent by Nintendo https://patents.google.com/patent/US7071945B2/en
}