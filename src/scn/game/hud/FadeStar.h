#pragma once
#include "math/Vector3.h"
#include "g3d/Model.h"
#include "gfx/TexBuffer.h"

namespace scn
{
	namespace roll
	{
		class FadeStar
		{
			unsigned long timer;
			gfx::TexBuffer tex;
		public:
			FadeStar();
			void updateAndDraw(g3d::Root&);
		};
	}
}