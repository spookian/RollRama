#pragma once

#include "defines.h"

namespace snd
{
	class SERequestor
	{
		SET_OBJECT_SIZE(0x74);
	public:
		SERequestor();
		~SERequestor();
		
		void start(unsigned long idx); // the idx corresponds to a file's info index in the iuk.brsar
	};
}