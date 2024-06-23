#pragma once
#include "scn/IScene.h"
#include "lyt/lyt.h"

namespace scn
{
	enum TitleStates
	{
		TITLE_NINTENDO,
		TITLE_NINTENDOFADE,
		TITLE_WARNING,
		TITLE_WARNINGFADE,
		TITLE_MENU,
		TITLE_MENUFADE
	};
	
	class SceneTitle : public IScene
	{
		int timer;
		int state;
		
		lyt::Layout warningScreen;
		lyt::Layout titleScreen;
		lyt::Layout nintendoDisclaimer;

		bool isEnd;
	public:
		void rtti();
		SceneTitle();
		~SceneTitle();
		void updateMain();
		void updateUseGPU();
		void updateDebug();
		void draw(const DrawReqInfo& info);
		bool isSceneEnd() const;
	};
}