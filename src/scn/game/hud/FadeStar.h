#pragma once
#include "g3d/Model.h"
#include "gfx/gfx.h"

namespace scn
{
	namespace roll
	{
		class FadeStar
		{
			unsigned long timer;
			unsigned long maxTime;
			float startSize;
			float endSize;
			
			bool enable;
			
		public:
			bool finished;
			
			FadeStar();
			void activate(float startSize, float endSize, unsigned long maxTime);
			void updateAndDraw(g3d::Root&);
			void drawFadeMesh();
		};
	}
}