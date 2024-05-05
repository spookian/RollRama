#pragma once

#define PI (355.0f/113.0f)
#define HALFPI (PI / 2.0f)

extern "C"
{
	extern double pow(double num, double exp);
	extern double asin(double x);
}

namespace hel
{
	namespace math
	{
		class Math
		{
		public:
			static float AbsF32(float signedNumber);
			static float CosFIdx(float rad);
			static float SinFIdx(float rad);
		};
	}
}