#pragma once

#include "math/Vector3.h"

namespace hel
{
	namespace math
	{
		// wrapper for basic 3x4 matrix used by consoles and older computers to save on space and computations
		// the perspective matrix explicitly needs to be a 4x4 matrix, so don't even try using this for perspective
		struct Matrix34
		{
			float mtx[3][4];

			Matrix34();
			static Matrix34 CreateScale(const Vector3& scale);
			static Matrix34 CreateTrans(const Vector3& translation);

			// note: rotaxis methods probably need a normalized vector
			static Matrix34 CreateRotXYZRad(const Vector3& rotation);
			static Matrix34 CreateRotXYZDeg(const Vector3& rotation);
			static Matrix34 CreateRotAxisRad(const Vector3& axis, float rotation);
			static Matrix34 CreateRotAxisDeg(const Vector3& axis, float rotation);

			static Matrix34 CreateLookAt(const Vector3& cam_pos, const Vector3& up, const Vector3& target);

			Matrix34 operator=(const Matrix34& other);
			Matrix34 operator*(const Matrix34& other) const;
		}; // add operators later
	}
}