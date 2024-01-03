#pragma once

#include "IScene.h"

namespace scn
{
	class SceneStart : IScene
	{
		~SceneStart();
		void updateMain();
		void updateUseGPU();
		void updateDebug();
		void draw(const DrawReqInfo& info);
		bool isSceneEnd() const;
	};
}