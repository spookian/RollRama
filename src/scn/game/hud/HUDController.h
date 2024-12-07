#pragma once
#include "lyt/lyt.h"
#include "scn/game/hud/NumberDisplay.h"
#include "math/Vector2.h"
namespace scn
{
	namespace roll
	{
		class HUDController
		{
			lyt::Layout hudBase;
			lyt::Layout healthLayout;
			
			NumberDisplay num;
			
		public:
			HUDController();
		
			void draw();
			void drawHealth();
			template <int size> void drawNumbers(const hel::math::Vector2& startPosition, int number, bool ignoreZero);
		};
	}
}