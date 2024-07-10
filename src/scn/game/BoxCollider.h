#pragma once
#include "math/math.h"
#include "scn/game/Collision.h"

const GlobalObject<const hel::math::Vector3, float> aabbMultipliers[8] = {
	{{-0.5, 0.5, -0.5}},
	{{0.5, 0.5, -0.5}},
	{{-0.5, 0.5, 0.5}},
	{{0.5, 0.5, 0.5}},
	
	{{-0.5, -0.5, -0.5}},
	{{0.5, -0.5, -0.5}},
	{{-0.5, -0.5, 0.5}},
	{{0.5, -0.5, 0.5}}
};

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		struct AABB
		{
			Vector3 position;
			Vector3 bounds; // should be used for cubes only in this case;
			
			bool Contains(hel::math::Vector3& otherPos)
			{
				float halfx = bounds.x / 2.0f;
				float halfy = bounds.y / 2.0f;
				float halfz = bounds.z / 2.0f;
				
				float lx = position.x - halfx;
				float hx = position.x + halfx;
				float ly = position.y - halfy;
				float hy = position.y + halfy;
				float lz = position.z - halfz;
				float hz = position.z + halfz;
				
				if (otherPos.x >= lx && otherPos.x < hx)
				{
					if (otherPos.y >= ly && otherPos.y < hy)
					{
						if (otherPos.z >= lz && otherPos.z < hz) return true;
					}
				}
				return false;
			}
			
			void getVertices(Vector3 arr[8]) // requires an array of 8
			{
				for (int i = 0; i < 8; i++)
				{
					Vector3 curMultiplier = aabbMultipliers[i];
					Vector3 add( curMultiplier.x * bounds.x, curMultiplier.y * bounds.y, curMultiplier.z * bounds.z );
					arr[i] = position + add;
				}
			}
		};
	}
}