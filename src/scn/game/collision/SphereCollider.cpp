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
			Vector3 ray = other.getPosition() - this->position;
			
			float length = ray.length();
			if (length <= radius + other.getRadius())
			{
				return true;
			}
			
			return false;
		}
		
		hel::math::Vector3 SphereCollider::getPosition()
		{
			return position;
		}
		
		float SphereCollider::getRadius()
		{
			return radius;
		}
	}
}