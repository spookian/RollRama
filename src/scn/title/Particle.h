#pragma once
#include "common/List.h"

#define MAX_AMOUNT_OF_PARTICLES 50

namespace scn
{
	namespace rolltitle
	{
		class Particle
		{
			hel::math::Vector2 position;
			float rotation;
			 // snowflakes
		public:
			void update();
			void draw();
		};
		
		class ParticleManager // creates and manages particles
		{
			hel::common::List<Particle> ptclList;
			
		public:
			void update(); // NOTE: linked list implementation is very much a possible memory leak. if stuff happens, IMMEDIATELY disable the title screen particles
			void draw();
		};
	}
}