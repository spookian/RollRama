#pragma once

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/MathSingleton.h"

extern "C"
{
	struct RVLQuat
	{
		float x, y, z, w;
	};

	void PSQUATMultiply(const RVLQuat* a, const RVLQuat* b, RVLQuat* result);
	void PSMTXQuat(Mtx m, const RVLQuat* quat);
	void C_QUATMtx(RVLQuat* q, const Mtx m);
} // stole these from the mkwii decompilation