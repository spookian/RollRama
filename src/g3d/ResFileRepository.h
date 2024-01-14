#pragma once

#include "defines.h"

namespace g3d
{
	class ResFileRepository
	{
	public:
		// get size
		ResFileRepository();
		ResFileAccessor get(const char *path, bool unk);
	};
	
	class ResFileAccessor
	{
		SET_OBJECT_SIZE(32);
	
	public:
		void bind(const ResFileAccessor& other, bool unk) const;
	};
}