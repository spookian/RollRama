#pragma once

#include "app/app.h"

namespace hel
{
	namespace common
	{
		template <typename T>
		class ExplicitSingleton
		{
			T* ptr;
		public:
			inline T* operator->()
			{
				return ptr;
			}
		};
		
		ExplicitSingleton<app::Application> object;
	}
}