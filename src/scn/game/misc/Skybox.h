#pragma once
#include "g3d/Model.h"

namespace scn
{
	namespace roll
	{
		class Skybox
		{
		public:
			Skybox();
			~Skybox();
			
			void update();
			void draw();
		};
	}
}