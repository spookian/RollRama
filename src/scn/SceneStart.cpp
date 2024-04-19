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
		mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
		g3d::RootContext rootContext(*defAllocator, 32, 32, 8, 1);
		modelRoot = new g3d::Root(rootContext);
		
		g3d::CameraAccessor cam = modelRoot->currentCamera();
		demo = new Chowder(&cam);
		return;
	}
	
	SceneStart::~SceneStart()
	{
		return;
	}
	
	void SceneStart::updateMain()
	{
		modelRoot->sceneClear();
		demo->updateMain();
		demo->preDraw(*modelRoot);
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
		modelRoot->sceneCalcOnDraw();
		modelRoot->sceneDrawOpa();
		demo->drawDebug();
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}