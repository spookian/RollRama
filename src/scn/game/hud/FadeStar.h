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
		public:
			FadeStar();
			void updateAndDraw(g3d::Root&);
		};
	}
}