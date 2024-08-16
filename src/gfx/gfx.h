#pragma once

#include "gfx/GXStructs.h"
#include "gfx/LightSet.h"
#include "gfx/Utility.h"
#include "gfx/VISetting.h"
#include "gfx/EasyRender3D.h"

extern "C"
{
	extern void GXSetBlendMode(unsigned char type, unsigned char src_factor, unsigned char dst_factor, unsigned char op);
}