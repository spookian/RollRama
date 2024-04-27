#pragma once

namespace hel
{
	namespace math
	{
		struct Vector3
		{
			Vector3();
			Vector3(float _x, float _y, float _z); //0x800bdad0 - nw4r::math::VEC3 constructor

			float x, y, z;

			float dot(const Vector3& other) const;
			float cos(const Vector3& other) const;
			float length() const;
			Vector3 cross(const Vector3& other) const;
			void normalize();

			void operator=(const Vector3& other);
			void operator+=(const Vector3& other);
			Vector3 operator+(const Vector3& other) const;
			Vector3 operator-(const Vector3& other) const;
			Vector3 operator-() const;
			Vector3 operator*(float scalar) const;
			Vector3 operator/(float scalar) const;
			
			static const Vector3 ZERO;
			static const Vector3 BASIS_X;
			static const Vector3 BASIS_Y;
			static const Vector3 BASIS_Z;
		}; // include functions later
	}
}