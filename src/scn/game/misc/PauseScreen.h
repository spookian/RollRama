#pragma once
#include "lyt/lyt.h"

namespace scn
{
	namespace roll
	{
		class PauseScreen
		{
			int option;
			int evenTimer;
			
			bool fading;
			int fadeTimer;
			lyt::Layout layout;
			
			//static const float maxTimeToLoop = 5.0 * 60; // in 1/60 seconds
			// max time determines how fast the loop will be
		public:
			PauseScreen();
			
			void activate();
			void drawBackStars(lyt::PaneAccessor& pane);
			void update();
			void draw();
		};
	}
}