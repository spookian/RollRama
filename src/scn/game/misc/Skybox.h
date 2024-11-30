#pragma once
#include "g3d/Model.h"

namespace scn
{
	namespace roll
	{
		class Skybox
		{
			int timer;
		public:
			Skybox();
			~Skybox();
			
			void update();
			void draw();
		};
	}
}