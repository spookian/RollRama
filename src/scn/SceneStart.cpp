#include "allocate.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"

#include "g3d/ResFileRepository.h"
#include "nw4r/ResFile.h"
#include "g3d/Model.h"
#include "mem/Memory.h"
#include "math/Matrix34.h"
#include "math/Vector3.h"

namespace scn
{
	void SceneStart::rtti()
	{
		return;
	}
	
	SceneStart::SceneStart()
	{
		// load cube file
		g3d::ResFileAccessor cubeFile(fileRepo.get("step/gimmick/WarpStar", false)); // for some reason it's not the full path
		g3d::ResModelContext cubeResCtx(cubeFile, "TopL");
		
		g3d::ModelBufferOption cubeOptions = g3d::ModelContext::DefaultModelBufferOption();
		
		mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
		hel::common::FixedString<32> string("MdlAnm");
		
		g3d::CharaModelContext cubeContext(cubeResCtx, cubeOptions, 4, 2, 2, *defAllocator, true, 0x2000, string);
		
		cube = new g3d::CharaModel(cubeContext);
		// setup cube
		hel::math::Vector3 cubeScale(1.0f, 1.0f, 1.0f);
		hel::math::Vector3 cubePos(0.0f, 0.0f, 0.0f);
		hel::math::Matrix34 cubeTransMtx = hel::math::Matrix34::CreateTrans(cubePos);
		
		cube->setModelScale(cubeScale);
		cube->setModelRTMtx(cubeTransMtx);
		
		// initialize root object
		g3d::RootContext rootContext(*defAllocator, 32, 32, 8, 1);
		modelRoot = new g3d::Root(rootContext);
		
		return;
	}
	
	SceneStart::~SceneStart()
	{
		return;
	}
	
	void SceneStart::updateMain()
	{
		hel::math::Vector3 dx(0.05f, 0.0f, 0.0f);
		cubePosition += dx;
		
		cube->setModelRTMtx( hel::math::Matrix34::CreateTrans(cubePosition) );
		cube->updateWorldMtx();
		modelRoot->sceneClear();
		cube->registerToRoot(*modelRoot);
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
		return;
	}
	
	bool SceneStart::isSceneEnd() const
	{
		return false;
	}
}