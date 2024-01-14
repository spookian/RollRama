#pragma once

namespace hel::common
{
	template <int T>
	struct FixedString
	{
		char[T] string; 
		
		FixedString(const char *_str);
	};
}