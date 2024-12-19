#pragma once
#include "g3d/Model.h"
#include "lyt/lyt.h"

namespace scn
{
	namespace roll
	{
		class Skybox
		{
			int timer;
			lyt::Layout sky;
			
		public:
			Skybox();
			
			void update();
			void draw();
		};
	}
}