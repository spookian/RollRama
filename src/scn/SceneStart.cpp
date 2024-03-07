#include "allocate.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"

#include "g3d/ResFileRepository.h"
#include "nw4r/ResFile.h"
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
		// load cube file
		g3d::ResFileAccessor cubeFile(fileRepo.get("step/AmigaSphere", false)); // for some reason it's not the full path
		g3d::ResModelContext cubeResCtx(cubeFile, "TopL");
		
		g3d::ModelBufferOption cubeOptions = g3d::ModelContext::DefaultModelBufferOption();
		
		mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
		hel::common::FixedString<32> string("MdlAnm");
		
		g3d::CharaModelContext cubeContext(cubeResCtx, cubeOptions, 4, 2, 2, *defAllocator, true, 0x2000, string);
		
		cube = new g3d::CharaModel(cubeContext);
	
		// initialize root object
		g3d::RootContext rootContext(*defAllocator, 32, 32, 8, 1);
		modelRoot = new g3d::Root(rootContext);
		
		g3d::CameraAccessor cam = modelRoot->currentCamera();
		demo = new Chowder(&cam, cube);
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
		//demo->drawDebug();
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}