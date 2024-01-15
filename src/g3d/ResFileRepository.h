#pragma once

#include "defines.h"

namespace g3d
{
	class ResFileAccessor
	{
	private:
		SET_OBJECT_SIZE(32);
		
	public:
		void bind(const ResFileAccessor& other, bool unk) const;
	};
	
	class ResFileRepository
	{
	private:
		SET_OBJECT_SIZE(0x204);
		
	public:
		ResFileRepository();
		ResFileAccessor get(const char *path, bool unk);
	};
}