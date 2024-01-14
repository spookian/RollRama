#include "scn/IScene.h"
#include "scn/SceneStart.h"

#include "g3d/ResFileRepository.h"
#include "g3d/Model.h"
#include "mem/Memory.h"

namespace scn
{
	void SceneStart::rtti()
	{
		return;
	}
	
	SceneStart::SceneStart()
	{
		// load cube file
		g3d::ResFileAccessor cubeFile = fileRepo.get("step/DebugCube", false); // for some reason it's not the full path
		g3d::ResModelContext cubeResCtx(cubeFile, "TopL");
		g3d::ModelBufferOption cubeOptions = g3d::ModelContext::DefaultModelBufferOption();
		
		mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
		hel::common::FixedString<16> string("???");
		// note: i have no idea what this does yet
		
		g3d::CharaModelContext cubeContext(cubeResCtx, cubeOptions, 0, 0, 0, *defAllocator, false, 0, 0, string);
		
		cube = new g3d::CharaModel(cubeContext);
		
		// initialize root object
		g3d::RootContext rootContext(defAllocator, 32, 32, 8, 1);
		root = new g3d::Root(rootContext);
		
		return;
	}
	
	SceneStart::~SceneStart()
	{
		return;
	}
	
	void SceneStart::updateMain()
	{
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
		// 
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}