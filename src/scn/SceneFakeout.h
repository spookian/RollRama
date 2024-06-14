#pragma once

#include "scn/IScene.h"
#include "gfx/FakeWriter.h"
#include "common/List.h"

namespace scn
{
	struct MessageNode
	{
		char *string;
		int time; // in frames
	};
	
	class SceneFakeout : public IScene
	{
		gfx::FakeWriter console;
		hel::common::List<char*> drawList;
		
		int messageIdx;
		int timer;
		
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

extern const scn::MessageNode messageTable[];