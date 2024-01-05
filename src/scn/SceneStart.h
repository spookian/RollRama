#pragma once

#include "scn/IScene.h"

namespace scn
{
	class SceneStart : public IScene
	{
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