#pragma once

#include "math/math.h"

namespace scn
{
	namespace roll
	{
		struct SphereCollider
		{
			float radius;
			hel::math::Vector3 position;
			
			SphereCollider(float _radius);
			bool isCollide(SphereCollider& other);
		};
	}
}