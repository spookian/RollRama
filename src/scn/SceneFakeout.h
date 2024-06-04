#pragma once

#include "scn/IScene.h"
#include "gfx/FakeWriter.h"
#include "common/List.h"

namespace scn
{
	struct MessageNode
	{
		unsigned long time; // in frames
		const char *string;
	};
	
	class SceneFakeout : public IScene
	{
		gfx::FakeWriter console;
		hel::common::List<const char*> drawList;
		bool isEnd;
		
	public:
		void rtti();
		SceneFakeout();
		~SceneFakeout();
		void updateMain();
		void updateUseGPU();
		void updateDebug();
		void draw(const DrawReqInfo& info);
		bool isSceneEnd() const;
	};
}