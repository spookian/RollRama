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
		Chowder *p = new Chowder(); // don't worry it'll place itself into a global pointer
		return;
	}
	
	SceneStart::~SceneStart()
	{
		delete engineSingleton;
		return;
	}
	
	void SceneStart::updateMain()
	{
		engineSingleton->updateMain();
		engineSingleton->preDraw();
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
		engineSingleton->draw();
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}