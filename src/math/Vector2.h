#pragma once
namespace hel
{
	namespace math
	{
		struct Vector2
		{
			float x, y;
			Vector2();
			
			static const hel::math::Vector2 ALL_ONE;
			static const hel::math::Vector2 BASIS_X;
			static const hel::math::Vector2 BASIS_Y;
			static const hel::math::Vector2 ZERO;
		};
	}
}