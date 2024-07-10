#pragma once
#include "math/math.h"
#include "g3d/Model.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		struct PathNode
		{
			Vector3 offset;
			Vector3 rotation; // euler
			int time;
		};
		
		class Enemy : public SphereCollider
		{
		protected:
			Matrix34 rotation;
			Vector3 initialPosition; // position that is added to path offset
			Vector3 prevNodeOffset;
			
			const hel::common::List<PathNode>* path;
			bool usesPath;
			
			int currentIdx;
			int timer;
			
		public:		
			void updatePath()
			{
				if (currentIdx == path.size())
				{
					currentIdx = 0;
					rotation = Matrix34::CreateRotXYZRad( path[currentIdx].rotation );
					p
					timer = 0;
				}
				
				if (timer == path[currentIdx].time)
				{
					prevNodeOffset = path[currentIdx].offset;
					currentIdx++;
					rotation = Matrix34::CreateRotXYZRad( path[currentIdx].rotation );
					timer = 0;
				}
				
				float multiplier = (float)(path[currentIdx].time - timer) / path[currentIdx].time;
				position = initialPosition + ( (path[currentIdx] - prevNodeOffset) * multiplier) + prevNodeOffset;
				
				timer++;
			}
			
			virtual void Update()
			{
				return;
			}
			
			virtual void UpdateModel()
			{
				return;
			}
		};
		
		class Gordo : public Enemy
		{
		
		};
		
		class Dee : public Enemy
		{
			
		};
	}
}