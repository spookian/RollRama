#pragma once
#include "math/Vector3.h"
#include "common/Array.h"
#include "hid/hid.h"
#include "common/ExplicitSingleton.h"

namespace app
{
	class Application
	{
		hid::HIDManager* hidManager();
	};
}