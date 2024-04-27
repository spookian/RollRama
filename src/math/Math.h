#pragma once

#include "math/Vector3.h"
#include "math/Vector2.h"
#include "math/Matrix44.h"
#include "math/Matrix34.h"

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
		};
	}
}