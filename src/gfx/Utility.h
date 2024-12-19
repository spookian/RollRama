#pragma once
#include "gfx/TexBuffer.h"

namespace sfx
{
	class Utility
	{
	public:
		static void CaptureEFB(gfx::TexBuffer&, _GXTexFmt, bool);
		static void FullScreenPlateDraw(bool); // load texobj into gx first and automatically generate texcoords
		// from my understanding, GXTexCoordGen is used when you don't include manual uvs in your vertex format/desc
	};
}

namespace gfx
{
	class Utility
	{
	public:
		static unsigned long CurrentGameHeight();
		static unsigned long CurrentGameWidth();
		static bool IsWidescreen(); // tee hee where did this come from
		static void ClearZBuffer(float);
	};
}