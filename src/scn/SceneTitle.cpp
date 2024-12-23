#include "allocate.h"
#include "scn/SceneTitle.h"
#include "math/math.h"
#include "hid/hid.h"
#include "common/Color.h"
#include "gfx/GXStructs.h"
#include "snd/snd.h"
#include "common/ExplicitSingleton.h"

#define WPAD_ACCEPT_BUTTONS (WPAD_BUTTON_A + WPAD_BUTTON_PLUS + WPAD_BUTTON_1 + WPAD_BUTTON_2 + WPAD_BUTTON_MINUS)

extern "C"
{
	extern unsigned long __OSBusClock; // 0x800000F8
	extern unsigned long long __OSGetSystemTime(); // 80025d10
}
#define OSTicksToSeconds(ticks) ((ticks) / (__OSBusClock / 4))
#define OSTicksToHours(ticks) (OSTicksToSeconds(ticks) / 3600)

namespace scn
{
	const GXColor timeGradients[] = 
	{
		//day
		{0x68, 0xD2, 0xFF, 0xFF},
		{0xE0, 0xF7, 0xFF, 0xFF},
		
		//night 
		{0x10, 0x1C, 0x30, 0xFF},
		{0x32, 0x4B, 0x76, 0xFF}
	};
	
	void SceneTitle::rtti()
	{
		return;
	}
	
	void SceneTitle::adjustTitleForTime()
	{
		unsigned long long sysTime = __OSGetSystemTime();
		int currentHour = (OSTicksToHours(sysTime) % 24) + 1;
		bool p = (currentHour > 18 || currentHour < 7);
		int idx = (int)p << 1;
		
		lyt::PaneAccessor back = titleScreen.paneByName("BackGradient");
		back.setVertexColor( timeGradients[idx], 0 );
		back.setVertexColor( timeGradients[idx], 1 );
		back.setVertexColor( timeGradients[idx + 1], 2 );
		back.setVertexColor( timeGradients[idx + 1], 3 );
		
		if (p) titleScreen.paneByName("Logo").setAlpha(187);
	}
	
	SceneTitle::SceneTitle() : warningScreen(lyt::LayoutContext::quickContext("gcntitle/WarningScreen", "WS")), titleScreen(lyt::LayoutContext::quickContext("gcntitle/GCNTitle", "KirbyTitleD")), nintendoDisclaimer(lyt::LayoutContext::quickContext("gcntitle/NintendoLogo", "NintendoScreen"))
	{
		state = TITLE_BLACK;
		timer = 0;
		isEnd = false;
		
		titleScreen.adjustFor4b3();
		warningScreen.adjustFor4b3();
		nintendoDisclaimer.adjustFor4b3();
		titleScreen.paneByName("StartGroup").setAlpha(0);
		nintendoDisclaimer.paneByName("NintenGroup").setAlpha(0);
		nintendoDisclaimer.updateMatrix();
		
		//snd::SoundManager::load(); 
		// apparently the sound thread is loaded right before the main game loop starts, so don't go playing sounds/songs in constructors
		adjustTitleForTime();
	}
	
	SceneTitle::~SceneTitle()
	{
		snd::SoundManager::object()->bgm().setVolume(1.0f);
		snd::SoundManager::object()->bgm().stop();
		return;
	}
	
	void SceneTitle::updateTitle()
	{
		if (wpad_data.buttons & WPAD_BUTTON_PLUS)
		{
			timer = -1;
			state = TITLE_MENUFADE;
		}
		
		// have dedede float by?
		return;
	}
	
	void SceneTitle::updateMain()
	{
		WPADRead(0, (void*)&wpad_data);
		switch (state)
		{
			case TITLE_BLACK:
			if (timer > 120)
			{
				timer = -1;
				nintendoDisclaimer.paneByName("NintenGroup").setAlpha(255);
				sndReq.start(0x84);
				state = TITLE_NINTENDO;
			}
			break;
			
			case TITLE_NINTENDO:
			if (timer > 180)
			{
				timer = -1;
				state = TITLE_NINTENDOFADE;
			}
			break;
			
			case TITLE_NINTENDOFADE:
			{
				int nintenAlpha = 255 - (timer * 16); 
				if (nintenAlpha < 0) nintenAlpha = 0;
				
				int newTimer = timer - 120;
				if (newTimer < 0) newTimer = 0;
				int backAlpha = (255 - newTimer * 16);
				if (backAlpha < 0)
				{
					backAlpha = 0;
					timer = -1;
					state = TITLE_WARNING;
				}
				
				nintendoDisclaimer.paneByName("NintenGroup").setAlpha(nintenAlpha);
				nintendoDisclaimer.paneByName("Back").setAlpha(backAlpha);
				break;
			}
			
			case TITLE_WARNING:
			{
				if (wpad_data.buttons & WPAD_ACCEPT_BUTTONS)
				{
					state = TITLE_WARNINGFADE;
					timer = -1;
				}
				break;
			}
			
			case TITLE_WARNINGFADE:
			{ // apparently c++ thinks declaring variables is out of scope
				int warningAlpha = 255 - (timer * 4); 
				if (warningAlpha < 0)
				{
					warningAlpha = 0;
					timer = -1;
					state = TITLE_MENU;
					snd::SoundManager::object()->bgm().start(0x4);
				}
				warningScreen.rootPane().setAlpha(warningAlpha);
				break;
			}
			
			case TITLE_MENU:
			{
				updateTitle();
				
				float wiener = -hel::math::Math::CosFIdx((float)timer * PI / 60.0f) * 127.5 + 127.5;
				titleScreen.paneByName("StartGroup").setAlpha((unsigned char)wiener);
				break;
			}
			
			case TITLE_MENUFADE:
			{
				int blackScreen = (timer << 3);
				if (blackScreen > 255)
				{
					blackScreen = 255;
				}
				
				if (timer > 90) isEnd = true;
				snd::SoundManager::object()->bgm().setVolume( (255 - blackScreen) / 255.0f );
				
				nintendoDisclaimer.paneByName("Back").setAlpha(blackScreen);
				break;
			}
		}
		
		timer++;
		titleScreen.updateMatrix();
		warningScreen.updateMatrix();
		nintendoDisclaimer.updateMatrix();
	}
	
	void SceneTitle::updateUseGPU()
	{
		return;
	}
	
	void SceneTitle::updateDebug()
	{
		return;
	}
	
	void SceneTitle::draw(const DrawReqInfo& info)
	{
		lyt::Utility::SetupGX();
		titleScreen.draw();
		ptclManager.updateAndDraw();
		warningScreen.draw();
		nintendoDisclaimer.draw();
	}
	
	bool SceneTitle::isSceneEnd() const
	{
		return isEnd;
	}
}