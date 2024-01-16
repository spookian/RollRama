#pragma once

#include "defines.h"

namespace mem
{
	class IAllocator // welcome to the dark side of c++ reverse engineering, finding a fucking allocator.
	{
		SET_OBJECT_SIZE(4);
	};

	class Memory
	{
		SET_OBJECT_SIZE(4); // these are obviously fake class sizes but we're not making any objects here
		
	public:
		IAllocator& sceneHeap();
		
	};
}