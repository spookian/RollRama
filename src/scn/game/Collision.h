#pragma once

#include "math/math.h"

namespace scn
{
	namespace roll
	{
		class SphereCollider
		{
		protected:
			float radius;
			hel::math::Vector3 position;
		
		public:
			SphereCollider(float _radius);
			bool isCollide(SphereCollider& other);
			hel::math::Vector3 GetPosition();
			float GetRadius();
		};
	}
}