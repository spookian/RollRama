#pragma once

namespace hel
{
	namespace common
	{
		template <typename T, int SIZE>
		class Array
		{
		private:
			T data[SIZE];

		public:
			T& operator[](int idx);
		};
	}
}