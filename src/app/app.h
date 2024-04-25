#pragma once
#include "math/Vector3.h"
#include "hid/hid.h"

namespace app
{
	class Application
	{
	public:
		hid::HIDManager* hidManager();
	};
}