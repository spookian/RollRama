#pragma once
#include "gfx/TexBuffer.h"
#include "hid/hid.h"
#include "math/Random.h"

namespace app
{
	class Random
	{
	public:
		float RandF32(float, float);
		static Random& Obj();
	};
	
	class Application
	{
	public:
		hid::HIDManager* hidManager();
		gfx::TexBuffer& fullScreenTexBuffer();
		app::Random& random();
	};
}