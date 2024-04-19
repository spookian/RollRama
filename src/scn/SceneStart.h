#pragma once

#include "scn/IScene.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"

namespace scn
{
	class SceneStart : public IScene
	{
		g3d::Root *modelRoot;
		g3d::CharaModel *cube;
		
		Chowder *demo;
		
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