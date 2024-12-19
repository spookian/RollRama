#pragma once
namespace hel
{
	namespace math
	{
		struct Vector2
		{
			float x, y;
			Vector2();
			
			float length() const;
			float normalize();
			
			void operator=(const Vector2&);
			Vector2 operator+(const Vector2&) const;
			Vector2 operator-(const Vector2&) const;
			Vector2 operator-() const;
			Vector2 operator*(float) const;
			Vector2 operator/(float) const;
			void operator*=(float);
			
			static const hel::math::Vector2 ALL_ONE;
			static const hel::math::Vector2 BASIS_X;
			static const hel::math::Vector2 BASIS_Y;
			static const hel::math::Vector2 ZERO;
		};
	}
}