#include "scn/game/Collision.h"

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
			Vector3 ray = other.GetPosition() - this->position;
			
			float length = ray.length();
			if (length <= radius + other.GetRadius())
			{
				return true;
			}
			
			return false;
		}
		
		hel::math::Vector3 SphereCollider::GetPosition()
		{
			return position;
		}
		
		float SphereCollider::GetRadius()
		{
			return radius;
		}
	}
}