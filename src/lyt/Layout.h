#pragma once
#include "mem/Memory.h"

namespace lyt
{
	class LayoutContext
	{
		LayoutContext(const char* unk, mem::IAllocator& allocator);
	};
	
	class Layout
	{
		void draw() const;
	};
}