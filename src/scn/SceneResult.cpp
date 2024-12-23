#include "scn/SceneResult.h"
#include "snd/snd.h"
#include "gfx/gfx.h"
#include "gfx/GX.h"
#include "common/Color.h"
#include "math/Math.h"

const unsigned long maxResultTime = 300;
const GlobalObject<const hel::math::Vector3, float> rectangle[4] = {
				{{-1.0, 1.0, 0.0}},
				{{-1.0, -1.0, 0.0}},
				{{1.0, -1.0, 0.0}},
				{{1.0, 1.0, 0.0}}
			};

namespace scn
{
	void SceneResult::rtti()
	{
	}
	
	SceneResult::SceneResult() : resuScreen( lyt::LayoutContext::quickContext("gcnstep/ResultScreen", "Results") )
	{
		timer = 0;
		resuScreen.adjustFor4b3();
	}
	
	SceneResult::~SceneResult()
	{
	}
	
	void SceneResult::updateMain()
	{
		if (timer > maxResultTime)
		{
			unsigned char nAlpha = (255 - (unsigned char)((timer - maxResultTime) * 255.0f / maxResultTime ));
			resuScreen.paneByName("Cover").setAlpha(nAlpha);
			resuScreen.updateMatrix();
		}
		else
		{
			if (timer == maxResultTime) snd::SoundManager::object()->bgm().start(0x616);
		}
		
		if (timer < maxResultTime * 2) timer++;
	}
	
	void SceneResult::updateUseGPU()
	{
	}
	
	void SceneResult::updateDebug()
	{
	}
	
	void SceneResult::draw(const DrawReqInfo& info)
	{
		lyt::Utility::SetupGX();
		resuScreen.draw();
	}
	
	bool SceneResult::isSceneEnd() const
	{
		return false;
	}
	
}