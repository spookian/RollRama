#include "gfx/TexBuffer.h"
#include "gfx/GXTexture.h"
#include "gfx/GXStructs.h"

namespace gfx
{
	GXTexObj TexBuffer::textureObj() const
	{
		GXTexObj result;
		mem::MemoryBlock data = block();
		GXInitTexObj(&result, data.ptr, w, h, (_GXTexFmt)fmt, GX_CLAMP, GX_CLAMP, false);
		return result;
	}
}
