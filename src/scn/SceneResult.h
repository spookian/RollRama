#pragma once
#include "scn/IScene.h"
#include "lyt/lyt.h"
namespace scn
{
	class SceneResult : public IScene
	{
		lyt::Layout resuScreen;
		int timer;
		
	public:
		void rtti();
		SceneResult();
		~SceneResult();
		void updateMain();
		void updateUseGPU();
		void updateDebug();
		void draw(const DrawReqInfo& info);
		bool isSceneEnd() const;
	};
}