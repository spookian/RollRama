#include "scn/game/hud/HUDController.h"
#include "lyt/lyt.h"
#include "math/Vector2.h"
#include "math/Vector3.h"
#include "scn/Chowder.h"
#include "common/Color.h"

typedef GlobalObject<const hel::math::Vector2, float> CVector2;

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		// Starting positions
		CVector2 scoreStart = {{ 179.306f, 186.367f }};
		CVector2 healthStart = {{ -70.885f, -177.48f }}; 
		CVector2 starStart = {{ -234.251f, -179.223f }};
		CVector2 timeStart = {{ 217.221f, -177.577f }};
		
		// Number sizes
		CVector2 smallNumberSize = {{ 18.0f, 24.0f }};
		CVector2 scoreNumberSize = {{ 18.0f, 34.0f }};
		
		// Offsets
		const float healthOffset = 18.892f;
		const float numberOffset = 15.0f;
		
		const _GXColor starTop = { 0xff, 0xfe, 0xa0, 0xff };
		const _GXColor starBottom = { 0xff, 0xaa, 0x00, 0xff };
		
		// this algorithm separates a number into digits and stores them starting with greatest to least
		void separateNumberDigits(unsigned char *array, int numDigits, int number)
		{
			int newNumber;
			*array = 0;
			
			for (int i = 0; i < numDigits; i++)
			{
				newNumber = (number / 10); // truncation
				array[numDigits - (i + 1)] = (unsigned char)(number - (newNumber * 10)); 
				number = newNumber;
			}
			return;
		}
		
		HUDController::HUDController() : hudBase( lyt::LayoutContext::quickContext("gcnstep/GCNHud", "HUDBase") ), healthLayout( lyt::LayoutContext::quickContext("gcnstep/GCNHud", "HUDHealth") )
		{
			hudBase.adjustFor4b3();
			healthLayout.adjustFor4b3();
		}
		
		void HUDController::draw()
		{
			lyt::Utility::SetupGX();
			
			hudBase.updateMatrix();
			hudBase.draw();
			
			drawHealth();
			
			num.scale = scoreNumberSize;
			num.setTopColor(hel::common::Color::WHITE);
			num.setBottomColor(hel::common::Color::WHITE);
			drawNumbers<6>(scoreStart, engineSingleton->score, true);
			
			num.scale = smallNumberSize;
			num.setTopColor(starTop);
			num.setBottomColor(starBottom);
			drawNumbers<2>(starStart, engineSingleton->stars, false);
			
			num.setTopColor(hel::common::Color::WHITE);
			num.setBottomColor(hel::common::Color::WHITE);
			drawNumbers<3>(timeStart, engineSingleton->time, false);
		}
		
		template<int size> 
		void HUDController::drawNumbers(const Vector2& startPosition, int number, bool ignoreZero)
		{
			// setup
			unsigned char array[size];		
			Vector2 newPos = startPosition;
			separateNumberDigits(array, size, number);
			
			//loop
			bool canDraw = !ignoreZero;
			for (int i = 0; i < size; i++)
			{
				if (ignoreZero)
				{
					if (array[i]) canDraw = true;
					else if (i == (size - 1)) canDraw = true;
				}
				
				if (canDraw) num.draw(array[i], newPos);
				// end
				newPos.x += numberOffset;
			}
		}
		
		void HUDController::drawHealth()
		{
			Vector3 newPos( ((Vector2)healthStart).x, ((Vector2)healthStart).y, 0.0f);
			lyt::PaneAccessor healthPellet = healthLayout.paneByName("HealthF");
			lyt::PaneAccessor emptyOrb = healthLayout.paneByName("HealthE");
			
			healthPellet.show();
			emptyOrb.hide();
			for (int i = 0; i < engineSingleton->health; i++)
			{
				healthPellet.setTrans(newPos);
				healthLayout.updateMatrix();
				healthLayout.draw();
				newPos.x += healthOffset;
			}
			
			healthPellet.hide();
			emptyOrb.show();
			for (int j = 0; j < 6 - engineSingleton->health; j++)
			{
				emptyOrb.setTrans(newPos);
				healthLayout.updateMatrix();
				healthLayout.draw();
				newPos.x += healthOffset;
			}
		}
	}
}