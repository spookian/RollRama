#pragma once

#include "defines.h"
#include "nw4r/ResFile.h"

namespace g3d
{
	class ResFileAccessor
	{
	private:
		nw4r::g3d::ResFile* data;
		
	public:
		ResFileAccessor(nw4r::g3d::ResFile* file)
		{
			data = file;
		}
		
		void bind(const ResFileAccessor& other, bool unk) const;
	};
	
	class ResFileRepository
	{
	private:
		SET_OBJECT_SIZE(0x204);
		
	public:
		ResFileRepository();
		nw4r::g3d::ResFile* get(const char *path, bool unk);
	};
}