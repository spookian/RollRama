#include "scn/game/misc/PauseScreen.h"
#include "gfx/FullScreenDrawer.h"
#include "scn/Chowder.h"
#include "hid/hid.h"

using namespace lyt;
namespace scn
{
	namespace roll
	{
		PauseScreen::PauseScreen() : layout( LayoutContext::quickContext("gcnstep/PauseScreen", "PauseScreen") )
		{
			evenTimer = 0;
			fadeTimer = 0;
			fading = false;
			option = 0;
			layout.adjustFor4b3();
		}
		
		void PauseScreen::update()
		{
			if ( (!engineSingleton->held_start) && (engineSingleton->input.buttons & WPAD_BUTTON_PLUS) )
			{
				engineSingleton->paused = false;
				engineSingleton->held_start = true;
			}
			// do option selection n stuff
		}
		
		inline void drawNormal(Layout& layout, PaneAccessor& pane)
		{
			pane.show();
			layout.updateMatrix();
			layout.draw();
			pane.hide();
		}
		
		void PauseScreen::drawBackStars(PaneAccessor& pane)
		{
			evenTimer++;
			if (evenTimer >= 174) evenTimer -= 174;
			
			pane.show();
			hel::math::Vector3 originStarPos(-380.0, 130.0, 0.0);
			float starXOffset = 126.0 + 48.0;
			float starYOffset = 48.0 + 27.0;
			float columnOffset = starXOffset / 2;
			
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					hel::math::Vector3 curStarPos = originStarPos;
					curStarPos.x += starXOffset * j;
					curStarPos.y -= starYOffset * i;
					if (i & 1) 
					{
						curStarPos.x -= columnOffset;
						curStarPos.x += evenTimer;
					}
					else curStarPos.x -= evenTimer;

					pane.setTrans(curStarPos);
					layout.updateMatrix();
					layout.draw();
				}
			}
			pane.hide();
		}
		
		void PauseScreen::draw()
		{
			PaneAccessor background = layout.paneByName("Back");
			background.hide();
			PaneAccessor backStar = layout.paneByName("BackStar");
			backStar.hide();
			PaneAccessor foreGroup = layout.paneByName("FixedGroup");
			foreGroup.hide();
			
			Utility::SetupGX();
			drawNormal(layout, background);
			drawBackStars(backStar);
			drawNormal(layout, foreGroup);
			//drawSelectStars();
			return;
		}
		
		void PauseScreen::activate()
		{
			evenTimer = 0;
			fadeTimer = 0;
			fading = true;
			gfx::FullScreenDrawer::Capture();
			
			engineSingleton->held_start = true;
			return;
		}
	}
}