#pragma once

namespace hel
{
	namespace math
	{
		struct Matrix44
		{
			float mtx[4][4];
			
			Matrix44();
			
			static Matrix44 CreatePerspective(float fov, float aspect, float near, float far);
			static Matrix44 CreateOrtho(float top, float bottom, float left, float right, float near, float far);
		};
	}
}