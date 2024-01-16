#pragma once

#include "scn/IScene.h"
#include "g3d/Model.h"
#include "math/Vector3.h"

namespace scn
{
	class SceneStart : public IScene
	{
		g3d::ResFileRepository fileRepo;
		
		g3d::Root *modelRoot;
		g3d::CharaModel *cube;
		
		hel::math::Vector3 cubePosition;
		
	public:
		void rtti();
		SceneStart();
		~SceneStart();
		void updateMain();
		void updateUseGPU();
		void updateDebug();
		void draw(const DrawReqInfo& info);
		bool isSceneEnd() const;
	};
}