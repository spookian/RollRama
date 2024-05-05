#pragma once
#include "math/Matrix34.h"

extern "C"
{
	struct Quaternion
	{
		float x, y, z, w;
	};

	void PSQUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* result);
	void PSMTXQuat(Mtx m, const Quaternion* quat);
	void C_QUATMtx(Quaternion* q, const Mtx m);
} // stole these from the mkwii decompilation