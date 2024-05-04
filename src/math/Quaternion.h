#pragma once

#include "math/Vector3.h"
#include "math/Matrix34.h"

extern "C"
{
	struct RVLQuat
	{
		float x, y, z, w;
	};

	void PSQUATMultiply(const RVLQuat* a, const RVLQuat* b, RVLQuat* result);
	void PSMTXQuat(Mtx m, const RVLQuat* quat);
}

namespace hel
{
	namespace math
	{
		struct Quaternion : public RVLQuat
		{
			Quaternion(float _w, float _x, float _y, float _z)
			{
				w = _w;
				x = _x;
				y = _y;
				z = _z;
			}

			Quaternion()
			{
				w = 0;
				x = 0;
				y = 0;
				z = 0;
			}

			static Quaternion ConvertEulerRad(const Vector3& rotation)
			{
				Quaternion _x = Quaternion(Math::CosFIdx(rotation.x / 2), Math::SinFIdx(rotation.x / 2), 0.0f, 0.0f);
				Quaternion _y = Quaternion(Math::CosFIdx(rotation.y / 2), 0.0f, Math::SinFIdx(rotation.y / 2), 0.0f);
				Quaternion _z = Quaternion(Math::CosFIdx(rotation.z / 2), 0.0f, 0.0f, Math::SinFIdx(rotation.z / 2));
		
				return (_z * _y * _x);
			}

			Quaternion operator+(const Quaternion& other)
			{
				Quaternion result;
				result.w = w + other.w;
				result.x = x + other.x;
				result.y = y + other.y;
				result.z = z + other.z;
				return result;
			}

			Quaternion operator*(const Quaternion& other)
			{
				Quaternion result;
				PSQUATMultiply(this, &other, &result);
				return result;
			}

			Matrix34 ToMatrix34()
			{
				Matrix34 result;
				PSMTXQuat(result.mtx, this);
				return result;
			}
		};
	}
}