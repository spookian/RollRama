#include "allocate.h"
#include "scn/IScene.h"
#include "scn/SceneTitle.h"
#include "math/math.h"
#include "hid/hid.h"

#define WPAD_ACCEPT_BUTTONS (WPAD_BUTTON_A + WPAD_BUTTON_PLUS + WPAD_BUTTON_1 + WPAD_BUTTON_2 + WPAD_BUTTON_MINUS)

namespace scn
{
	void SceneTitle::rtti()
	{
		return;
	}
	
	SceneTitle::SceneTitle() : warningScreen(lyt::LayoutContext::quickContext("gcntitle/WarningScreen", "WS")), titleScreen(lyt::LayoutContext::quickContext("gcntitle/GCNTitle", "KirbyTitle")), nintendoDisclaimer(lyt::LayoutContext::quickContext("gcntitle/NintendoLogo", "NintendoScreen"))
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
	}
	
	SceneTitle::~SceneTitle()
	{

	}
	
	void SceneTitle::updateMain()
	{
		WPADStatus wpad_data;
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
				}
				warningScreen.rootPane().setAlpha(warningAlpha);
				break;
			}
			
			case TITLE_MENU:
			{
				if (wpad_data.buttons & WPAD_BUTTON_PLUS)
				{
					timer = -1;
					state = TITLE_MENUFADE;
				}
				
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
					isEnd = true;
				}
				
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
		warningScreen.draw();
		nintendoDisclaimer.draw();
	}
	
	bool SceneTitle::isSceneEnd() const
	{
		return isEnd;
	}
}