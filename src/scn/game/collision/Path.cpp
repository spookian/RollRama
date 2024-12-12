#include "scn/game/collision/Path.h"
#include "math/math.h"

using namespace hel::math;

namespace
{
	Vector3 lerp(const Vector3 a, const Vector3 b, float t)
	{
		Vector3 c = b - a;
		return a + (c * t);
	}
}

namespace scn
{
	namespace roll
	{
		Path::Path()
		{
			enable = true;
			timer = 0;
			repeat = false;
			interpolateRotation = false;
			curIndex = 0;
		}
		
		void Path::update()
		{		
			if (enable)
			{
				const PathNode* currentNode = nodeList[curIndex];
				if (timer >= currentNode->time)
				{
					prevNode = currentNode;
					curIndex++;
					timer = 0;
				}
				
				if (curIndex == nodeList.getSize())
				{
					if (!repeat || nodeList.getSize() == 0)
					{
						enable = false;
						return;
					}
					
					curIndex = 0;
					currentRotation = Matrix34::CreateRotXYZRad( nodeList[curIndex]->rotation );
					timer = 0;
				}
				
				currentNode = nodeList[curIndex];
				
				float multiplier = 1.0;
				if (currentNode->time) multiplier -= ( static_cast<float>(nodeList[curIndex]->time - timer) / nodeList[curIndex]->time );
				
				currentOffset = lerp(prevNode->offset, nodeList[curIndex]->offset, multiplier);
				currentRotation = Matrix34::CreateRotXYZRad( nodeList[curIndex]->rotation );
				
				timer++;
			}
			return;
		}
		
		void Path::append(const PathNode *node)
		{
			if (nodeList.getSize() == 0) prevNode = node;
			nodeList.append(node);
		}
	}
}