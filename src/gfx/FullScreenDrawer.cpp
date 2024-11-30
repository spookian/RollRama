#include "gfx/gfx.h"
#include "math/math.h"
#include "common/ExplicitSingleton.h"
#include "app/app.h"

using namespace hel::math;
namespace gfx
{
	void FullScreenDrawer::Capture()
	{
		gfx::TexBuffer& tex = hel::common::ExplicitSingleton<app::Application>::object->fullScreenTexBuffer();
		sfx::Utility::CaptureEFB(tex, (_GXTexFmt)tex.fmt, true);
		GXPixModeSync();
		GXTexModeSync();
		return;
	}
	
	void setupGXTextured(GXTexObj& tex)
	{
		GXSetZMode(0, 1, 0);
		GXSetCullMode(0);
		
		GXLoadTexObj(&tex, GX_TEXMAP0);
				
		GXSetNumTexGens(1);
		GXSetNumTevStages(1);
		
		GXSetTevOrder(0, 0, 0, 255);
		GXSetTevOp(0, 3);
		GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
		GXSetTevSwapMode(0, 0, 0);
		GXSetTevSwapModeTable(0, 0, 1, 2, 3);
		GXSetNumChans(0);
	}
	
	void FullScreenDrawer::Draw()
	{
		gfx::TexBuffer& tex = hel::common::ExplicitSingleton<app::Application>::object->fullScreenTexBuffer();
		GXTexObj efbCopy = tex.textureObj();
		
		setupGXTextured(efbCopy);
		sfx::Utility::FullScreenPlateDraw(true);
	}
}