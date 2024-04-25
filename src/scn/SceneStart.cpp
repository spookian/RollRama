#include "allocate.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"

#include "g3d/ResFileRepository.h"
#include "g3d/Model.h"
#include "mem/Memory.h"
#include "scn/Chowder.h"

namespace scn
{
	void SceneStart::rtti()
	{
		return;
	}
	
	SceneStart::SceneStart()
	{
		// initialize root object
		demo = new Chowder();
		return;
	}
	
	SceneStart::~SceneStart()
	{
		return;
	}
	
	void SceneStart::updateMain()
	{
		demo->updateMain();
		demo->preDraw();
		return;
	}
	
	void SceneStart::updateUseGPU()
	{
		return;
	}
	
	void SceneStart::updateDebug()
	{
		return;
	}
	
	void SceneStart::draw(const DrawReqInfo& info)
	{
		demo->draw();
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}