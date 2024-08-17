#pragma once
#include "math/math.h"
#include "common/List.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		struct PathNode
		{
			GlobalObject<const Vector3, float> offset;
			GlobalObject<const Vector3, float> rotation; // euler
			int time;
		};
		
		// class obscures and abstracts the details of path following
		class Path
		{
			const PathNode *prevNode;
			hel::common::List<PathNode*> nodeList;
			unsigned long curIndex;
			int timer;
			
		public:
			bool repeat;
			bool interpolateRotation;
			
			Vector3 currentOffset;
			Matrix34 currentRotation;
			
			Path()
			{
				timer = 0;
				repeat = false;
				interpolateRotation = false;
				curIndex = 0;
			}
			
			void Update()
			{
				if (curIndex == nodeList.getSize())
				{
					if (!repeat || nodeList.getSize() == 0) return;
					curIndex = 0;
					currentRotation = Matrix34::CreateRotXYZRad( nodeList[curIndex]->rotation );
					timer = 0;
					return;
				}
				
				if (timer == nodeList[curIndex]->time)
				{
					prevNode = nodeList[curIndex];
					curIndex++;
					timer = 0;
					return;
				}
				
				float multiplier = 1.0 - ( static_cast<float>(nodeList[curIndex]->time - timer) / nodeList[curIndex]->time );
				currentOffset = lerp(prevNode->offset, nodeList[curIndex]->offset, multiplier);
				currentRotation = Matrix34::CreateRotXYZRad( nodeList[curIndex]->rotation );
				
				timer++;
				return;
			}
			
			static Vector3 lerp(const Vector3 a, const Vector3 b, float t)
			{
				Vector3 c = b - a;
				return a + (c * t);
			}
			
			void Append(PathNode *node)
			{
				if (nodeList.getSize() == 0) prevNode = node;
				nodeList.append(node);
			}
		};
		
	}
}