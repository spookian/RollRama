#include "gfx/gfx.h"
#include "common/ExplicitSingleton.h"

bool gfx::Utility::IsWidescreen()
{
	const _GXRenderModeObj *rmode = &hel::common::ExplicitSingleton<gfx::VISetting>::object->rmode;
	if (rmode->fbWidth == 608) return false;
	return true;
}