#include "scn/game/misc/PauseScreen.h"



using namespace lyt;
namespace scn
{
	namespace roll
	{
		PauseScreen::PauseScreen() : layout( LayoutContext::quickContext("gcnstep/PauseScreen", "PauseScreen") )
		{
			evenTimer = 0;
			oddTimer = 0;
			option = 0;
			layout.adjustFor4b3();
		}
		
		void PauseScreen::update()
		{
			
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
	}
}