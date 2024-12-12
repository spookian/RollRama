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
			hel::common::List<const PathNode*> nodeList;
			unsigned long curIndex;
			int timer;
			
		public:
			bool enable;
			bool repeat;
			bool interpolateRotation;
			
			Vector3 currentOffset;
			Matrix34 currentRotation;
			
			Path();
			void update();
			void append(const PathNode *node);
		};
		
	}
}