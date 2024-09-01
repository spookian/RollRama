#include "scn/game/collision/Collision.h"

namespace scn
{
	namespace roll
	{
		SphereCollider::SphereCollider(float _radius)
		{
			radius = _radius;
		}
	
		bool SphereCollider::isCollide(SphereCollider& other)
		{
			using namespace hel::math;
			Vector3 ray = other.position - this->position;
			
			float length = ray.length();
			if (length <= radius + other.radius)
			{
				return true;
			}
			
			return false;
		}
	}
}