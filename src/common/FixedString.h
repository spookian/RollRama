#pragma once

namespace hel
{
	namespace common
	{
		template <int T>
		struct FixedString
		{
			char strData[T]; 
			
			FixedString(const char *_str);
		};
	}
}