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
			bool enable;
		public:
			FadeStar();
			void activate();
			void updateAndDraw(g3d::Root&);
		};
	}
}