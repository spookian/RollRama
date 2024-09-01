#pragma once

#include "defines.h"
#include "mem/Memory.h"
#include "gfx/GX.h"

namespace gfx
{
	class TexBuffer : public mem::DataBlock
	{
		// this class either inherits from datablock or has datablock as the first member
		//SET_OBJECT_SIZE(20);
	public:
		short w;
		short h;
		unsigned long fmt;
		
		TexBuffer(mem::IAllocator&, unsigned short, unsigned short, _GXTexFmt); // width and height
		~TexBuffer();
		
		unsigned long height() const;
		GXTexObj textureObj() const;
	};
}